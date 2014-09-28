/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
** edited by kvakvs@yandex.ru, see https://github.com/kvakvs/hge
**
** Core functions implementation: graphics
*/


#include "hge_impl.h"
// GAPI dependent includes and defines (DX8/DX9 switch) by kvakvs@yandex.ru
#include "hge_gapi.h"
#include "WICTextureLoader.h"
#include <vector>

#include "D3DX10math.h"

struct CB_VS_PER_OBJECT
{
	D3DXMATRIX m_WorldViewProj;
	D3DXMATRIX m_World;
};

struct CB_PS_PER_OBJECT
{
	D3DXVECTOR4 m_vObjectColor;
};

struct CB_PS_PER_FRAME
{
	D3DXVECTOR4 m_vLightDirAmbient;
};

static const char vsSource[] =
{
	"void main( in float3 inPosition : POSITION0, in float4 inColor : COLOR0, out float4 outPosition : SV_POSITION, out float4 outColor : TEXCOORD0 ) {\n"
	"	outPosition = float4(inPosition, 1.0f);\n"
	"	outColor = float4(inColor);\n"
	"}\n"
};

static const char psSource[] =
{
	"void main(  in float4 inPosition : SV_POSITION, in float4 inColor : TEXCOORD0, out float4 Out : SV_TARGET ) {\n"
	"	Out = inColor;\n"
	"}\n"
};

static const char vsTexturedSource[] =
{
	"void main( in float3 inPosition : POSITION0, in float4 inColor : COLOR0, in float2 inTexcoord : TEXCOORD0, out float4 outPosition : SV_POSITION, out float4 outColor : TEXCOORD0, out float2 outTexcoord : TEXCOORD1 ) {\n"
	"	outPosition = float4(inPosition, 1.0f);\n"
	"	outColor = inColor;\n"
	"	outTexcoord = inTexcoord;\n"
	"}\n"
};

static const char psTexturedSource[] =
{
	"void main( uniform Texture2D<float4> sampleTexture : register(t0), uniform SamplerState sampleSampler : register(s0), in float4 inPosition : SV_POSITION, in float4 inColor : TEXCOORD0, in float2 inTexcoord : TEXCOORD1, out float4 Out : SV_TARGET ) {\n"
	"	Out = sampleTexture.SampleLevel(sampleSampler, inTexcoord, 0).rgba * inColor;\n"
	"}\n"
};

static const D3D11_INPUT_ELEMENT_DESC vertexLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

#define V_RETURN(x)    { hr = (x); if( FAILED(hr) ) { _PostError("V_RETURN FAILED.");/* return DXUTTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true );*/ } }
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

//--------------------------------------------------------------------------------------
// Find and compile the specified shader
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(TCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;
	size_t _size;
	void* data;

	data = pHGE->Resource_Load((char*)szFileName, &_size);
	if (!data) return NULL;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromMemory(
		(LPCSTR)data,
		_size,
		NULL,
		NULL,
		NULL,
		szEntryPoint,
		szShaderModel,
		dwShaderFlags,
		0,
		NULL,
		ppBlobOut,
		&pErrorBlob,
		NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		SAFE_RELEASE(pErrorBlob);
		return hr;
	}
	SAFE_RELEASE(pErrorBlob);

	return S_OK;
}

void HGE_CALL HGE_Impl::Gfx_Clear(hgeU32 color)
{
	float c[4] = {
		(float)GETA(color) / 256,
		(float)GETR(color) / 256,
		(float)GETG(color) / 256,
		(float)GETB(color) / 256 };
	m_pD3DDeviceContext->ClearRenderTargetView(pRTView, c);
	//m_pD3DDeviceContext->ClearDepthStencilView(pDSView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void HGE_CALL HGE_Impl::Gfx_SetClipping(int x, int y, int w, int h)
{
	// Set the viewport
	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));

	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = nScreenWidth;
	vp.Height = nScreenHeight;


	int scr_width, scr_height;

	if (!pCurTarget)
	{
		scr_width = pHGE->System_GetStateInt(HGE_SCREENWIDTH);
		scr_height = pHGE->System_GetStateInt(HGE_SCREENHEIGHT);
	}
	else
	{
		scr_width = Texture_GetWidth((HTEXTURE)pCurTarget->pTex);
		scr_height = Texture_GetHeight((HTEXTURE)pCurTarget->pTex);
	}

	if (!w)
	{
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width = scr_width;
		vp.Height = scr_height;
	}
	else
	{
		if (x<0) { w += x; x = 0; }
		if (y<0) { h += y; y = 0; }

		if (x + w > scr_width) w = scr_width - x;
		if (y + h > scr_height) h = scr_height - y;

		vp.TopLeftX = x;
		vp.TopLeftY = y;
		vp.Width = w;
		vp.Height = h;
	}

	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	_render_batch();
	m_pD3DDeviceContext->RSSetViewports(1, &vp);

	//Adjust scaling and orthogonal arguments accordingly.
	// 	D3DXMATRIX tmp;
	// 	D3DXMatrixScaling(&matProj, 1.0f, -1.0f, 1.0f);
	// 	D3DXMatrixTranslation(&tmp, -0.5f, +0.5f, 0.0f);
	// 	D3DXMatrixMultiply(&matProj, &matProj, &tmp);
	// 	D3DXMatrixOrthoOffCenterLH(&tmp, (float)vp.TopLeftX, (float)(vp.TopLeftX + vp.Width), -((float)(vp.TopLeftY + vp.Height)), -((float)vp.TopLeftY), vp.MinDepth, vp.MaxDepth);
	// 	D3DXMatrixMultiply(&matProj, &matProj, &tmp);
	//pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
//deprecated
void HGE_CALL HGE_Impl::Gfx_SetTransform(float x, float y, float dx, float dy, float rot, float hscale, float vscale)
{
	// 	D3DXMATRIX tmp;
	// 
	// 	if (vscale == 0.0f) D3DXMatrixIdentity(&matView);
	// 	else
	// 	{
	// 		D3DXMatrixTranslation(&matView, -x, -y, 0.0f);
	// 		D3DXMatrixScaling(&tmp, hscale, vscale, 1.0f);
	// 		D3DXMatrixMultiply(&matView, &matView, &tmp);
	// 		D3DXMatrixRotationZ(&tmp, -rot);
	// 		D3DXMatrixMultiply(&matView, &matView, &tmp);
	// 		D3DXMatrixTranslation(&tmp, x + dx, y + dy, 0.0f);
	// 		D3DXMatrixMultiply(&matView, &matView, &tmp);
	// 	}

	_render_batch();
	//pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
}

bool HGE_CALL HGE_Impl::Gfx_BeginScene(HTARGET targ)
{
	HRESULT hr;
	ID3D11Texture2D* pNewBackBuffer = m_pBackBuffer;
	ID3D11Texture2D* pNewDepthBuffer = m_pDepthBuffer;
	ID3D11RenderTargetView* pRTView;

	//Set new render target
	CRenderTargetList* target = (CRenderTargetList*)targ;
	// get the address of the back buffer
	//pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (target)
	{
		if (target != pCurTarget)
		{
			pNewBackBuffer = target->pTex;
			pNewDepthBuffer = target->pDepth;

			//Discard previous render target view
			SAFE_RELEASE(pRTView);
			//Create render target view with new back buffer
			if (FAILED(m_pD3DDevice->CreateRenderTargetView(pNewBackBuffer, NULL, &pRTView)))
			{
				if (target) pNewBackBuffer->Release();
				_PostError("Gfx_BeginScene: Can't create render target");
				return false;
			}

			SAFE_RELEASE(pDSView);
			if (FAILED(m_pD3DDevice->CreateDepthStencilView(pNewDepthBuffer, NULL, &pDSView)))
			{
				if (target) pNewDepthBuffer->Release();
				_PostError("Gfx_BeginScene: Can't create render target");
				return false;
			}

			m_pD3DDeviceContext->OMSetRenderTargets(1, &pRTView, pDSView);
		}
		pCurTarget = target;
	}
	else
	{
		//if (bZBuffer) pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		//else pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		_SetProjectionMatrix(nScreenWidth, nScreenHeight);
	}

	//pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	//D3DXMatrixIdentity(&matView);
	//pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	m_pD3DDeviceContext->OMSetBlendState(m_pBlendState, 0, 0xffffffff);
	m_pD3DDeviceContext->RSSetState(m_pRasterizerState);
	m_pD3DDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 0);

	//pD3DDevice->BeginScene();
	D3D11_MAPPED_SUBRESOURCE map;
	memset(&map, 0, sizeof(map));
	V_RETURN(m_pD3DDeviceContext->Map(m_pVertexBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &map));
	m_vertices = (hgeVertex*)map.pData;
	//pVB->Lock( 0, 0, (VOID**)&VertArray, D3DLOCK_DISCARD );
	return true;

}

void HGE_CALL HGE_Impl::Gfx_EndScene()
{
	_render_batch(true);
	m_pSwapChain->Present(0, 0);
	// 	pD3DDevice->EndScene();
	// 	if (!pCurTarget) pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void HGE_CALL HGE_Impl::Gfx_RenderLine(float x1, float y1, float x2, float y2, hgeU32 color, float z)
{
	if (m_vertices)
	{
		//Currently batching lines?
		if (m_cur_prim_type != HGEPRIM_LINES ||
			//Will the buffer have enough space?
			m_prim_count >= VERTEX_BUFFER_SIZE / HGEPRIM_LINES ||
			//Is there any texture related rendering?
			m_cur_texture ||
			//Currently lines only render in default mode
			m_cur_blend_mode != BLEND_DEFAULT)
		{
			//Must render the batch now
			_render_batch();

			//start a new batch
			m_cur_prim_type = HGEPRIM_LINES;
			if (m_cur_blend_mode != BLEND_DEFAULT)
			{
				_SetBlendMode(BLEND_DEFAULT);
			}
			if (m_cur_texture)
			{
				m_pD3DDeviceContext->PSSetShaderResources(0, 1, NULL);
				m_cur_texture = NULL;
			}
		}

		int i = m_prim_count * HGEPRIM_LINES;
		m_vertices[i] = { x1, y1, z, color, .0f, .0f };
		m_vertices[i + 1] = { x2, y2, z, color, .0f, .0f };
		m_prim_count++;
	}
}

void HGE_CALL HGE_Impl::Gfx_RenderTriple(const hgeTriple *triple)
{
	if (m_vertices)
	{
		//Currently batching tri'es?
		if (m_cur_prim_type != HGEPRIM_TRIPLES ||
			//Will the buffer have enough space?
			m_prim_count >= VERTEX_BUFFER_SIZE / HGEPRIM_TRIPLES ||
			//Is there any texture related rendering?
			(m_cur_texture != triple->tex) ||
			//Currently lines only render in default mode
			m_cur_blend_mode != triple->blend)
		{
			//Must render the batch now
			_render_batch();

			//start a new batch
			m_cur_prim_type = HGEPRIM_TRIPLES;
			if (m_cur_blend_mode != triple->blend)
			{
				_SetBlendMode(triple->blend);
			}
			if (m_cur_texture != triple->tex)
			{
				m_pD3DDeviceContext->PSSetShaderResources(0, 1, NULL);
				m_cur_texture = NULL;
			}
		}

		memcpy(&m_vertices[m_prim_count*HGEPRIM_TRIPLES], triple->v, sizeof(hgeVertex)*HGEPRIM_TRIPLES);
		m_prim_count++;
	}
}

void HGE_CALL HGE_Impl::Gfx_RenderQuad(const hgeQuad *quad)
{
	if (m_vertices)
	{
		//Currently batching quads?
		if (m_cur_prim_type != HGEPRIM_QUADS ||
			//Will the buffer have enough space?
			m_prim_count >= VERTEX_BUFFER_SIZE / HGEPRIM_QUADS ||
			//Is there any texture related rendering?
			(m_cur_texture != quad->tex) ||
			//Currently lines only render in default mode
			m_cur_blend_mode != quad->blend)
		{
			//Must render the batch now
			_render_batch();

			//start a new batch
			m_cur_prim_type = HGEPRIM_QUADS;
			if (m_cur_blend_mode != quad->blend)
			{
				//_SetBlendMode(quad->blend);
			}
			if (m_cur_texture != quad->tex)
			{
				auto* pTex = (CTextureList*)quad->tex;
				m_pD3DDeviceContext->PSSetShaderResources(0, 1, &(pTex->m_pSRV));
				m_cur_texture = quad->tex;
			}
		}

		//First triangle: 0 1 2
		memcpy(
			&m_vertices[m_prim_count*HGEPRIM_QUADS],
			&(quad->v[0]),
			sizeof(hgeVertex)*HGEPRIM_QUADS / 2);
		//Second triangle 1 2 3
		memcpy(
			&m_vertices[m_prim_count*HGEPRIM_QUADS + HGEPRIM_QUADS / 2],
			&(quad->v[1]),
			sizeof(hgeVertex)*HGEPRIM_QUADS / 2);
		m_prim_count++;
	}
}

hgeVertex* HGE_CALL HGE_Impl::Gfx_StartBatch(int prim_type, HTEXTURE tex, int blend, int *max_prim)
{
	if (m_vertices)
	{

		//Must render the batch now
		_render_batch();

		//start a new batch
		m_cur_prim_type = prim_type;

		if (m_cur_blend_mode != blend)
		{
			_SetBlendMode(blend);
		}

		if (m_cur_texture != tex)
		{
			m_pD3DDeviceContext->PSSetShaderResources(0, 1, NULL);
			m_cur_texture = tex;
		}

		*max_prim = VERTEX_BUFFER_SIZE / prim_type;
		return m_vertices;
	}
	else
	{
		return 0;
	}

}

void HGE_CALL HGE_Impl::Gfx_FinishBatch(int nprim)
{
	m_prim_count = nprim;
}

HTARGET HGE_CALL HGE_Impl::Target_Create(int width, int height, bool zbuffer)
{
	CRenderTargetList *pTarget;
	D3D11_TEXTURE2D_DESC TDesc;
	HRESULT hr;

	pTarget = new CRenderTargetList;
	pTarget->pTex = 0;
	pTarget->pDepth = 0;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	ID3D11Device *pd3dDevice; // Don't forget to initialize this
	hr = pd3dDevice->CreateTexture2D(&desc, NULL, &pTarget->pTex);
	//TODO: error checking

	pTarget->pTex->GetDesc(&TDesc);
	//TODO: check if it's necessary
	pTarget->width = TDesc.Width;
	pTarget->height = TDesc.Height;

	if (zbuffer)
	{
		D3D11_TEXTURE2D_DESC descDepth;
		descDepth.Width = pTarget->width;
		descDepth.Height = pTarget->height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_B8G8R8A8_TYPELESS;//pDeviceSettings->d3d11.AutoDepthStencilFormat;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		hr = pd3dDevice->CreateTexture2D(&descDepth, NULL, &pTarget->pDepth);
	}

	pTarget->next = pTargets;
	pTargets = pTarget;

	return (HTARGET)pTarget;
}

void HGE_CALL HGE_Impl::Target_Free(HTARGET target)
{
	CRenderTargetList *pTarget = pTargets, *pPrevTarget = NULL;

	while (pTarget)
	{
		if ((CRenderTargetList *)target == pTarget)
		{
			if (pPrevTarget)
				pPrevTarget->next = pTarget->next;
			else
				pTargets = pTarget->next;

			if (pTarget->pTex) pTarget->pTex->Release();
			if (pTarget->pDepth) pTarget->pDepth->Release();

			delete pTarget;
			return;
		}

		pPrevTarget = pTarget;
		pTarget = pTarget->next;
	}
}

HTEXTURE HGE_CALL HGE_Impl::Target_GetTexture(HTARGET target)
{
	auto targ = reinterpret_cast<CRenderTargetList*>(target);
	if (target)
	{
		return (HTEXTURE)(targ->pTex);
	}
	else
	{
		return 0;
	}
}

HTEXTURE HGE_CALL HGE_Impl::Texture_Create(int width, int height)
{
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	ID3D11Device *pd3dDevice; // Don't forget to initialize this
	ID3D11Texture2D *pTexture = NULL;
	pd3dDevice->CreateTexture2D(&desc, NULL, &pTexture);

	return (HTEXTURE)pTexture;
}

//Testing
void HGE_CALL HGE_Impl::Gfx_Test()
{
	_GfxInit();
	//265 x 199
	HTEXTURE mouse = Texture_Load("resources/tile4.bmp");
}
//

HTEXTURE HGE_CALL HGE_Impl::Texture_Load(const char *filename, hgeU32 size, bool bMipmap)
{
	HRESULT hr;

	void *data;
	hgeU32 _size;
	ID3D11Resource* pRes;
	ID3D11Resource* pStagingRes;
	ID3D11Texture2D* pTex;
	ID3D11ShaderResourceView* pSRV;
	//D3DXIMAGE_INFO info;
	CTextureList *texItem;

	//load file to buffer
	if (size)
	{
		//If argument is already the buffer
		data = (void *)filename; _size = size;
	}
	else
	{
		data = pHGE->Resource_Load(filename, &_size);
		if (!data) return NULL;
	}

	//Get image info
	D3DX11_IMAGE_INFO imgInfo;
	hr = D3DX11GetImageInfoFromMemory(
		(LPCSTR)data,
		_size,
		NULL,
		&imgInfo,
		NULL);
	if (hr)
	{
		_PostError("Cannot get image info.\n");
		if (!size) Resource_Free(data);
		return NULL;
	}

	D3DX11_IMAGE_LOAD_INFO loadImgInfo;
	loadImgInfo.MipLevels = bMipmap ? 0 : 1;
	loadImgInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	loadImgInfo.Usage = D3D11_USAGE_STAGING;
	loadImgInfo.BindFlags = 0;// (autogen) ? (D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET) : (D3D11_BIND_SHADER_RESOURCE);
	loadImgInfo.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	loadImgInfo.MiscFlags = 0;

	//Create Staging texture first
	hr = D3DX11CreateTextureFromMemory(
		m_pD3DDevice,
		(LPCVOID)data,
		_size,
		&loadImgInfo,
		NULL,
		&pStagingRes,
		0);
	if (hr)
	{
		_PostError("Can't create texture");
		if (!size) Resource_Free(data);
		return NULL;
	}

	//shouldn't access the file buffer anymore
	if (!size) Resource_Free(data);

	//Convert 0xFF00FFFF to transparent color
	D3D11_TEXTURE2D_DESC TDesc;
	((ID3D11Texture2D*)pStagingRes)->GetDesc(&TDesc);
	if (bUseTransparentColor)
	{
		DWORD* pLockPtr = (DWORD*)Texture_Lock((HTEXTURE)pStagingRes, false);

		int end = TDesc.Width * TDesc.Height;
		for (int i = 0; i < end; i++)
		{
			DWORD& currentPixel = pLockPtr[i];

			if (GETR(currentPixel) == 0xFF &&
				GETG(currentPixel) == 0x00 &&
				GETB(currentPixel) == 0xFF)
			{
				currentPixel = ARGB(0x00, 0x00, 0x00, 0x00);
			}

		}
		//Create default texture with data
		//from the staging texture
		TDesc.Usage = D3D11_USAGE_DEFAULT;
		TDesc.CPUAccessFlags = 0;
		TDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		TDesc.MipLevels = bMipmap ? 0 : 1;

		D3D11_SUBRESOURCE_DATA sr;
		sr.pSysMem = pLockPtr;
		sr.SysMemPitch = TDesc.Width * 4;
		sr.SysMemSlicePitch = TDesc.Width * TDesc.Height * 4;

		hr = m_pD3DDevice->CreateTexture2D(&TDesc, &sr, &pTex);
		if (hr)
		{
			_PostError("Can't create texture");
			if (!size) Resource_Free(data);
			pStagingRes->Release();
			return NULL;
		}
		Texture_Unlock((HTEXTURE)pStagingRes);
		SAFE_RELEASE(pStagingRes);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	memset(&SRVDesc, 0, sizeof(SRVDesc));
	SRVDesc.Format = TDesc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = bMipmap ? 0 : 1;

	hr = m_pD3DDevice->CreateShaderResourceView(pTex, &SRVDesc, &pSRV);
	if (hr)
	{
		_PostError("Can't create texture");
		if (!size) Resource_Free(data);
		return NULL;
	}

	pSRV->GetResource(&pRes);

	// 	hr = CreateWICTextureFromMemory(
	// 		pd3dDevice,
	// 		pd3dImmediateContext,
	// 		(uint8_t*)data,
	// 		_size,
	// 		&pRes,
	// 		&pSRV,
	// 		0);

	texItem = new CTextureList;
	texItem->tex = (HTEXTURE)pTex;
	texItem->m_pSRV = pSRV;
	texItem->width = TDesc.Width;
	texItem->height = TDesc.Height;
	texItem->next = textures;
	textures = texItem;
	return (HTEXTURE)texItem;
}

void HGE_CALL HGE_Impl::Texture_Free(HTEXTURE tex)
{
	auto * pTex = (ID3D11Texture2D *)tex;
	CTextureList *texItem = textures, *texPrev = 0;

	while (texItem)
	{
		if (texItem->tex == tex)
		{
			if (texPrev) texPrev->next = texItem->next;
			else textures = texItem->next;
			delete texItem;
			break;
		}
		texPrev = texItem;
		texItem = texItem->next;
	}
	if (pTex != NULL) pTex->Release();
}

int HGE_CALL HGE_Impl::Texture_GetWidth(HTEXTURE tex, bool bOriginal)
{
	auto * pTex = (ID3D11Texture2D *)tex;
	D3D11_TEXTURE2D_DESC TDesc;
	pTex->GetDesc(&TDesc);

	CTextureList *texItem = textures;

	if (bOriginal)
	{
		while (texItem)
		{
			if (texItem->tex == tex) return texItem->width;
			texItem = texItem->next;
		}
		return 0;
	}
	else
	{
		return TDesc.Width;
	}
}

int HGE_CALL HGE_Impl::Texture_GetHeight(HTEXTURE tex, bool bOriginal)
{
	auto * pTex = (ID3D11Texture2D *)tex;
	D3D11_TEXTURE2D_DESC TDesc;
	pTex->GetDesc(&TDesc);

	CTextureList *texItem = textures;

	if (bOriginal)
	{
		while (texItem)
		{
			if (texItem->tex == tex) return texItem->height;
			texItem = texItem->next;
		}
		return 0;
	}
	else
	{
		return TDesc.Height;
	}
}

void HGE_CALL HGE_Impl::Texture_Write(HTEXTURE tex, void* pData)
{
	// 	auto * pTex = (ID3D11Texture2D *)tex;
	// 	D3D11_TEXTURE2D_DESC TDesc;
	// 	pTex->GetDesc(&TDesc);
	// 
	// 	D3D11_BOX destRegion;
	// 	destRegion.left = 0;
	// 	destRegion.right = 200; //width
	// 	destRegion.top = 0;
	// 	destRegion.bottom = 120; //height
	// 	destRegion.front = 0;
	// 	destRegion.back = 1;
	// 
	// 	pd3dImmediateContext->UpdateSubresource(
	// 		(ID3D11Texture2D *)tex,
	// 		0,
	// 		&destRegion,
	// 		pData,
	// 		TDesc.Width * 16,
	// 		0);
}

hgeU32 * HGE_CALL HGE_Impl::Texture_Lock(HTEXTURE tex, bool bReadOnly, int left, int top, int width, int height)
{
	auto * pTex = (ID3D11Texture2D *)tex;
	D3D11_MAP mapType = bReadOnly ? D3D11_MAP_READ : D3D11_MAP_READ_WRITE;
	D3D11_MAPPED_SUBRESOURCE msr;
	HRESULT hr = m_pD3DDeviceContext->Map(pTex, NULL, mapType, NULL, &msr);
	if (hr)
	{
		_PostError("Can't map texture");
		return NULL;
	}
	return (hgeU32*)(msr.pData);
}

void HGE_CALL HGE_Impl::Texture_Unlock(HTEXTURE tex)
{
	m_pD3DDeviceContext->Unmap((ID3D11Texture2D*)tex, 0);
}

//////// Implementation ////////

void HGE_Impl::_render_batch(bool bEndScene)
{
	HRESULT hr;

	///*
	if (m_vertices)
	{
		UINT stride = sizeof(hgeVertex);
		UINT offset = 0;

		m_pD3DDeviceContext->Unmap(m_pVertexBuf, 0);

		if (m_prim_count)
		{
			switch (m_cur_prim_type)
			{
			case HGEPRIM_QUADS:
				m_pD3DDeviceContext->PSSetShader(m_pPS1, 0, 0);
				m_pD3DDeviceContext->VSSetShader(m_pVS1, 0, 0);

				m_pD3DDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
				m_pD3DDeviceContext->PSSetShaderResources(0, 1, &((CTextureList*)m_cur_texture)->m_pSRV);

				m_pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				m_pD3DDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuf, &stride, &offset);
				m_pD3DDeviceContext->IASetInputLayout(m_pInputLayout1);
				m_pD3DDeviceContext->Draw(m_prim_count * HGEPRIM_QUADS, 0);
				break;
			case HGEPRIM_TRIPLES:
				m_pD3DDeviceContext->PSSetShader(m_pPS1, 0, 0);
				m_pD3DDeviceContext->VSSetShader(m_pVS1, 0, 0);
				m_pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				m_pD3DDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuf, &stride, &offset);
				m_pD3DDeviceContext->IASetInputLayout(m_pInputLayout0);
				m_pD3DDeviceContext->Draw(m_prim_count, 0);
				break;
				break;
			case HGEPRIM_LINES:
				m_pD3DDeviceContext->PSSetShader(m_pPS1, 0, 0);
				m_pD3DDeviceContext->VSSetShader(m_pVS1, 0, 0);
				m_pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				m_pD3DDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuf, &stride, &offset);
				m_pD3DDeviceContext->IASetInputLayout(m_pInputLayout0);
				m_pD3DDeviceContext->Draw(m_prim_count, 0);
				break;
				break;
			}

			m_prim_count = 0;
		}

		if (bEndScene)
		{
			m_vertices = 0;
		}

		else
		{
			D3D11_MAPPED_SUBRESOURCE map;
			memset(&map, 0, sizeof(map));
			V_RETURN(m_pD3DDeviceContext->Map(m_pVertexBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &map));
			m_vertices = (hgeVertex*)map.pData;
		}
	}
	//*/
}

void HGE_Impl::_SetBlendMode(int blend)
{
	//Create new blend state
	D3D11_BLEND_DESC transDesc;
	transDesc.AlphaToCoverageEnable = false;
	transDesc.IndependentBlendEnable = false;
	//Only need 1 render target
	transDesc.RenderTarget[0].BlendEnable = true;
	//RGB channel blend settings
	transDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	transDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	transDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//A channel blend settings
	transDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	transDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	transDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	m_pD3DDevice->CreateBlendState(&transDesc, &m_pBlendState);

	float factor[4] = { 1.f, 1.f, 1.f, 1.f };
	m_pD3DDeviceContext->OMSetBlendState(m_pBlendState, factor, 0xffffffff);

	//todo:fix argument based blending mode creation
	// 	if ((blend & BLEND_ALPHABLEND) != (CurBlendMode & BLEND_ALPHABLEND))
	// 	{
	// 		if (blend & BLEND_ALPHABLEND) pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	// 		else pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// 	}

	//todo: test what this does
	// 	if ((blend & BLEND_ZWRITE) != (CurBlendMode & BLEND_ZWRITE))
	// 	{
	// 		if (blend & BLEND_ZWRITE) pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// 		else pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// 	}

	// 	if ((blend & BLEND_COLORADD) != (CurBlendMode & BLEND_COLORADD))
	// 	{
	// 		if (blend & BLEND_COLORADD) pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
	// 		else pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	// 	}

	m_cur_blend_mode = blend;
	SAFE_RELEASE(m_pBlendState);
}

void HGE_Impl::_SetProjectionMatrix(int width, int height)
{
	// 	D3DXMATRIX tmp;
	// 	D3DXMatrixScaling(&matProj, 1.0f, -1.0f, 1.0f);
	// 	D3DXMatrixTranslation(&tmp, -0.5f, height + 0.5f, 0.0f);
	// 	D3DXMatrixMultiply(&matProj, &matProj, &tmp);
	// 	D3DXMatrixOrthoOffCenterLH(&tmp, 0, (float)width, 0, (float)height, 0.0f, 1.0f);
	// 	D3DXMatrixMultiply(&matProj, &matProj, &tmp);
}

/*
std::vector <IDXGIAdapter*> EnumerateAdapters(void)
{
IDXGIAdapter * pAdapter;
std::vector <IDXGIAdapter*> vAdapters;
IDXGIFactory* pFactory = NULL;


// Create a DXGIFactory object.
if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory)))
{
return vAdapters;
}


for (UINT i = 0;
pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND;
++i)
{
vAdapters.push_back(pAdapter);
}


if (pFactory)
{
pFactory->Release();
}

return vAdapters;

}
*/

bool HGE_Impl::_GfxInit()
{
	HRESULT hr = S_OK;

#pragma region
	const D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1 };

	UINT               numFeatureLevels = 7;
	D3D_FEATURE_LEVEL  selectedFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	// create swap chain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;                                   // one back buffer
	swapChainDesc.BufferDesc.Width = nScreenWidth;                   // set the back buffer width
	swapChainDesc.BufferDesc.Height = nScreenHeight;                 // set the back buffer height
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
	swapChainDesc.OutputWindow = hwnd;                               // the window to be used
	swapChainDesc.SampleDesc.Count = 1;                              // how many multisamples
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = bWindowed;                              // windowed/full-screen mode
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

	//Setup debuf flag
#ifdef _DEBUG
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT createDeviceFlags = 0;
#endif
	//create device and swapchain
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		createDeviceFlags,
		featureLevels,
		numFeatureLevels,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_pSwapChain,
		&m_pD3DDevice,
		&selectedFeatureLevel,
		&m_pD3DDeviceContext);
	if (hr != S_OK)
	{
		_PostError("Can't initialize d3d11.");
		return false;
	}
#pragma endregion init swap chain

#pragma region 
	// Setup render target
	V_RETURN(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer));
	V_RETURN(m_pD3DDevice->CreateRenderTargetView(m_pBackBuffer, NULL, &pRTView));
	//m_pBackBuffer->Release();

	m_pD3DDeviceContext->OMSetRenderTargets(1, &pRTView, NULL);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)nScreenWidth;
	vp.Height = (FLOAT)nScreenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pD3DDeviceContext->RSSetViewports(1, &vp);

	/*
	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = nScreenWidth;
	descDepth.Height = nScreenHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthBuffer);
	if (FAILED(hr))
	return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_pDevice->CreateDepthStencilView(m_pDepthBuffer, &descDSV, &pDSView);
	if (FAILED(hr))
	return hr;
	*/
	//m_pDeviceContext->OMSetRenderTargets(1, &pRTView, pDSView);
#pragma endregion setup render targets & viewport

#pragma region
	std::string vertexProfile, pixelProfile;
	if (m_pD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_11_0)
	{
		vertexProfile = "vs_5_0";
		pixelProfile = "ps_5_0";
	}
	else if (m_pD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_10_1)
	{
		vertexProfile = "vs_4_1";
		pixelProfile = "ps_4_1";
	}
	else if (m_pD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_10_0)
	{
		vertexProfile = "vs_4_0";
		pixelProfile = "ps_4_0";
	}
	else if (m_pD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_9_3)
	{
		vertexProfile = "vs_4_0_level_9_3";
		pixelProfile = "ps_4_0_level_9_3";
	}
	else if (m_pD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_9_2)
	{
		vertexProfile = "vs_4_0_level_9_1";
		pixelProfile = "ps_4_0_level_9_1";
	}
	else if (m_pD3DDevice->GetFeatureLevel() == D3D_FEATURE_LEVEL_9_1)
	{
		vertexProfile = "vs_4_0_level_9_1";
		pixelProfile = "ps_4_0_level_9_1";
	}

	//D3DCOMPILE_OPTIMIZATION_LEVEL3 &
	//D3DCOMPILE_ENABLE_STRICTNESS
	UINT flags = (1 << 11) | (1 << 15);


	// Build Flat Vertex Shader
	ID3DBlob* binarycode = 0, *errors = 0, *signature0 = 0, *signature1 = 0;
	V_RETURN(D3DCompile(vsSource, strlen(vsSource), "VertexShader0", 0, 0, "main", vertexProfile.c_str(), flags, 0, &binarycode, &errors));

	V_RETURN(D3DGetInputSignatureBlob(binarycode->GetBufferPointer(), binarycode->GetBufferSize(), &signature0));


	V_RETURN(m_pD3DDevice->CreateVertexShader(binarycode->GetBufferPointer(), binarycode->GetBufferSize(), 0, &m_pVS0));

	if (binarycode) binarycode->Release();
	if (errors) errors->Release();

	// Build Textured Vertex Shader
	binarycode = 0;
	errors = 0;
	V_RETURN(D3DCompile(vsTexturedSource, strlen(vsTexturedSource), "VertexShader1", 0, 0, "main", vertexProfile.c_str(), flags, 0, &binarycode, &errors));

	V_RETURN(D3DGetInputSignatureBlob(binarycode->GetBufferPointer(), binarycode->GetBufferSize(), &signature1));

	V_RETURN(m_pD3DDevice->CreateVertexShader(binarycode->GetBufferPointer(), binarycode->GetBufferSize(), 0, &m_pVS1));

	if (binarycode) binarycode->Release();
	if (errors) errors->Release();

	// Build Flat Pixel Shader
	binarycode = 0;
	errors = 0;
	V_RETURN(D3DCompile(psSource, strlen(psSource), "PixelShader0", 0, 0, "main", pixelProfile.c_str(), flags, 0, &binarycode, &errors));

	V_RETURN(m_pD3DDevice->CreatePixelShader(binarycode->GetBufferPointer(), binarycode->GetBufferSize(), 0, &m_pPS0));

	if (binarycode) binarycode->Release();
	if (errors) errors->Release();

	// Build Textured Pixel Shader
	binarycode = 0;
	errors = 0;
	V_RETURN(D3DCompile(psTexturedSource, strlen(psTexturedSource), "PixelShader1", 0, 0, "main", pixelProfile.c_str(), flags, 0, &binarycode, &errors));

	V_RETURN(m_pD3DDevice->CreatePixelShader(binarycode->GetBufferPointer(), binarycode->GetBufferSize(), 0, &m_pPS1));

	if (binarycode) binarycode->Release();
	if (errors) errors->Release();


	// Compile the shaders using the lowest possible profile for broadest feature level support
	// 	ID3DBlob* pVertexShaderBuffer = NULL;
	// 	V_RETURN(CompileShaderFromFile(TEXT("BasicHLSL11_VS.hlsl"), "VSMain", vertexProfile.c_str(), &pVertexShaderBuffer));
	// 
	// 	ID3DBlob* pPixelShaderBuffer = NULL;
	// 	V_RETURN(CompileShaderFromFile(TEXT("BasicHLSL11_PS.hlsl"), "PSMain", pixelProfile.c_str(), &pPixelShaderBuffer));
	// 
	// 	// Create the shaders
	// 	V_RETURN(m_pD3DDevice->CreateVertexShader(pVertexShaderBuffer->GetBufferPointer(),
	// 		pVertexShaderBuffer->GetBufferSize(), NULL, &pVS0));
	// 	V_RETURN(m_pD3DDevice->CreatePixelShader(pPixelShaderBuffer->GetBufferPointer(),
	// 		pPixelShaderBuffer->GetBufferSize(), NULL, &pPS0));

	// Create Input Layout
	V_RETURN(m_pD3DDevice->CreateInputLayout(vertexLayout, 3, signature0->GetBufferPointer(), signature0->GetBufferSize(), &m_pInputLayout0));
	signature0->Release();

	// Create Input Layout
	V_RETURN(m_pD3DDevice->CreateInputLayout(vertexLayout, 3, signature1->GetBufferPointer(), signature1->GetBufferSize(), &m_pInputLayout1));
	signature1->Release();

#pragma endregion create shaders and input layout

#pragma region
	// Setup constant buffers
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.ByteWidth = sizeof(hgeVertex)* (VERTEX_BUFFER_SIZE);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	V_RETURN(m_pD3DDevice->CreateBuffer(&desc, NULL, &m_pVertexBuf));

	// 	D3D11_BUFFER_DESC desc;
	// 	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// 	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// 	desc.MiscFlags = 0;
	// 	desc.StructureByteStride = 0;
	// 	desc.ByteWidth = 6 * (VERTEX_BUFFER_SIZE/4) * sizeof(uint16_t);
	// 	desc.Usage = D3D11_USAGE_DYNAMIC;
	// 	V_RETURN(m_pD3DDevice->CreateBuffer(&desc, NULL, &m_pIndexBuf));
	// 
	// 	for (int i = 0; i < VERTEX_BUFFER_SIZE / 4; i++)
	// 	{
	// 		*pIndices++ = n;
	// 		*pIndices++ = n + 1;
	// 		*pIndices++ = n + 2;
	// 		*pIndices++ = n + 2;
	// 		*pIndices++ = n + 3;
	// 		*pIndices++ = n;
	// 		n += 4;
	// 	}
	// 
	// 	m_pD3DDeviceContext->IASetIndexBuffer(m_pIndexBuf, DXGI_FORMAT_R16_UINT, 0);
	D3D11_BUFFER_DESC Desc;
	Desc.Usage = D3D11_USAGE_DYNAMIC;
	Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Desc.MiscFlags = 0;
	Desc.ByteWidth = sizeof(CB_VS_PER_OBJECT);
	V_RETURN(m_pD3DDevice->CreateBuffer(&Desc, NULL, &g_pcbVSPerObject));
	Desc.ByteWidth = sizeof(CB_PS_PER_OBJECT);
	V_RETURN(m_pD3DDevice->CreateBuffer(&Desc, NULL, &g_pcbPSPerObject));
	Desc.ByteWidth = sizeof(CB_PS_PER_FRAME);
	V_RETURN(m_pD3DDevice->CreateBuffer(&Desc, NULL, &g_pcbPSPerFrame));
#pragma endregion setup constant buffers

	// Create Sampler State
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.BorderColor[0] = samplerDesc.BorderColor[1] = samplerDesc.BorderColor[2] = samplerDesc.BorderColor[3] = 0.0f;
	samplerDesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)0;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxAnisotropy = 1.0f;
	samplerDesc.MaxLOD = 0; //D3D11_FLOAT32_MAX
	samplerDesc.MinLOD = 0;
	samplerDesc.MipLODBias = 0.0f;
	V_RETURN(m_pD3DDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState));

	// Create Blend State
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	V_RETURN(m_pD3DDevice->CreateBlendState(&blendDesc, &m_pBlendState));

	// Create Depth Stencil State
	D3D11_DEPTH_STENCIL_DESC depthDesc;
	depthDesc.DepthEnable = false;
	depthDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthDesc.StencilEnable = false;
	depthDesc.StencilReadMask = depthDesc.StencilWriteMask = 0;
	depthDesc.BackFace.StencilDepthFailOp = depthDesc.BackFace.StencilFailOp = depthDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDesc.FrontFace = depthDesc.BackFace;
	V_RETURN(m_pD3DDevice->CreateDepthStencilState(&depthDesc, &m_pDepthStencilState));

	// Create Rasterizer State
	D3D11_RASTERIZER_DESC rastDesc;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FrontCounterClockwise = FALSE;
	rastDesc.DepthBias = 0;
	rastDesc.DepthBiasClamp = 0;
	rastDesc.SlopeScaledDepthBias = 0;
	rastDesc.ScissorEnable = FALSE;
	rastDesc.MultisampleEnable = FALSE;
	rastDesc.AntialiasedLineEnable = FALSE;
	hr = m_pD3DDevice->CreateRasterizerState(&rastDesc, &m_pRasterizerState);

	// 	mUpdate = false;
	// 
	// 	mIsInitialise = true;

	// Setup the camera's view parameters
	// 	D3DXVECTOR3 vecEye(0.0f, 0.0f, -100.0f);
	// 	D3DXVECTOR3 vecAt(0.0f, 0.0f, -0.0f);
	// 	g_Camera.SetViewParams(&vecEye, &vecAt);
	// 	g_Camera.SetRadius(fObjectRadius * 3.0f, fObjectRadius * 0.5f, fObjectRadius * 10.0f);

	//return S_OK;

	// Get adapter info
	// 	auto adapterList = EnumerateAdapters();
	// 	for (auto it = adapterList.begin(); it != adapterList.end(); it++)
	// 	{
	// 		System_Log("D3D Driver: %s", "123123123123123");
	// 		DXGI_ADAPTER_DESC desc;
	// 		(*it)->GetDesc(&desc);
	// 		System_Log("Description: %s", desc.Description);
	// 
	// 	}

	m_prim_count = 0;
	m_cur_prim_type = HGEPRIM_QUADS;
	m_cur_blend_mode = BLEND_DEFAULT;

	//todo: test those functions
	_AdjustWindow();

	System_Log("Screen Resolution: %d x %d\n", nScreenWidth, nScreenHeight);

	_SetProjectionMatrix(nScreenWidth, nScreenHeight);

	if (!_init_lost()) return false;

	Gfx_Clear(0);

	return true;
}

void HGE_Impl::_AdjustWindow()
{
	RECT *rc;
	LONG style;

	if (bWindowed) { rc = &rectW; style = styleW; }
	else { rc = &rectFS; style = styleFS; }
	SetWindowLong(hwnd, GWL_STYLE, style);

	style = GetWindowLong(hwnd, GWL_EXSTYLE);
	if (bWindowed)
	{
		SetWindowLong(hwnd, GWL_EXSTYLE, style & (~WS_EX_TOPMOST));
		SetWindowPos(hwnd, HWND_NOTOPMOST, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, SWP_FRAMECHANGED);
	}
	else
	{
		SetWindowLong(hwnd, GWL_EXSTYLE, style | WS_EX_TOPMOST);
		SetWindowPos(hwnd, HWND_TOPMOST, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, SWP_FRAMECHANGED);
	}
}

void HGE_Impl::_Resize(int width, int height)
{
	if (hwndParent)
	{
		//if(procFocusLostFunc) procFocusLostFunc();

		//d3dppW.BufferDesc.Width = width;
		//d3dppW.BufferDesc.Height = height;
		nScreenWidth = width;
		nScreenHeight = height;

		_SetProjectionMatrix(nScreenWidth, nScreenHeight);
		_GfxRestore();

		//if(procFocusGainFunc) procFocusGainFunc();
	}
}

void HGE_Impl::_GfxDone()
{
	CRenderTargetList *target = pTargets, *next_target;

	while (textures) Texture_Free(textures->tex);

	while (target)
	{
		if (target->pTex) target->pTex->Release();
		if (target->pDepth) target->pDepth->Release();
		next_target = target->next;
		delete target;
		target = next_target;
	}
	pTargets = 0;

	if (m_pSwapChain)
	{
		// Release all outstanding references to the swap chain's buffers.
		if (pRTView) pRTView->Release();
		if (m_pDepthStencilState) m_pDepthStencilState->Release();
		if (m_pVertexBuf) m_pVertexBuf->Release();
		if (m_pIndexBuf) m_pIndexBuf->Release();
		if (m_pInputLayout0) m_pInputLayout0->Release();
		if (m_pInputLayout1) m_pInputLayout1->Release();

		if (m_pSwapChain) m_pSwapChain->Release();
		if (m_pD3DDevice) m_pD3DDevice->Release();
		if (m_pD3DDeviceContext) m_pD3DDeviceContext->Release();
	}

}

bool HGE_Impl::_GfxRestore()
{
	//    CRenderTargetList *target=pTargets;

	//if(!pD3DDevice) return false;
	//if(pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICELOST) return;
	if (m_pSwapChain)
	{
		m_pD3DDeviceContext->OMSetRenderTargets(0, 0, 0);

		// Release all outstanding references to the swap chain's buffers.
		if (pRTView) pRTView->Release();
		if (m_pDepthStencilState) m_pDepthStencilState->Release();

		HRESULT hr;
		// Preserve the existing buffer count and format.
		// Automatically choose the width and height to match the client rect for HWNDs.
		hr = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

		// Perform error handling here!

		// Get buffer and create a render-target-view.
		ID3D11Texture2D* pBuffer;
		hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
			(void**)&pBuffer);
		// Perform error handling here!

		hr = m_pD3DDevice->CreateRenderTargetView(pBuffer, NULL,
			&pRTView);
		// Perform error handling here!
		pBuffer->Release();

		m_pD3DDeviceContext->OMSetRenderTargets(1, &pRTView, NULL);

		// Set up the viewport.
		D3D11_VIEWPORT vp;
		vp.Width = nScreenWidth;
		vp.Height = nScreenHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_pD3DDeviceContext->RSSetViewports(1, &vp);
	}




	//     while(target)
	//     {
	//         if(target->pTex) target->pTex->Release();
	//         if(target->pDepth) target->pDepth->Release();
	//         target=target->next;
	//     }
	// 
	//     if(pIB)
	//     {
	// #if HGE_DIRECTX_VER == 8
	//         pD3DDevice->SetIndices(NULL,0);
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//         pD3DDevice->SetIndices(NULL);
	// #endif
	//         pIB->Release();
	//     }
	//     if(pVB)
	//     {
	// #if HGE_DIRECTX_VER == 8
	//         pD3DDevice->SetStreamSource( 0, NULL, sizeof(hgeVertex) );
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//         pD3DDevice->SetStreamSource( 0, NULL,0, sizeof(hgeVertex) );
	// #endif
	//         pVB->Release();
	//     }
	// 
	//     pD3DDevice->Reset(d3dpp);
	// 
	//     if(!_init_lost()) return false;
	// 
	//     if(procGfxRestoreFunc) return procGfxRestoreFunc();

	return true;
}

bool HGE_Impl::_init_lost()
{
	// {
	//     CRenderTargetList *target=pTargets;
	// 
	// // Store render target
	// 
	//     pScreenSurf=0;
	//     pScreenDepth=0;
	// 
	// #if HGE_DIRECTX_VER == 8
	//     pD3DDevice->GetRenderTarget(&pScreenSurf);
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//     pD3DDevice->GetRenderTarget(0, &pScreenSurf);
	// #endif
	//     pD3DDevice->GetDepthStencilSurface(&pScreenDepth);
	//     
	//     while(target)
	//     {
	//         if(target->pTex)
	//             D3DXCreateTexture(pD3DDevice, target->width, target->height, 1, D3DUSAGE_RENDERTARGET,
	//                               d3dpp->BackBufferFormat, D3DPOOL_DEFAULT, &target->pTex);
	//         if(target->pDepth)
	// #if HGE_DIRECTX_VER == 8
	//             pD3DDevice->CreateDepthStencilSurface(target->width, target->height,
	//                 D3DFMT_D16, D3DMULTISAMPLE_NONE, &target->pDepth);
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//             pD3DDevice->CreateDepthStencilSurface(target->width, target->height,
	//                 D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, false, &target->pDepth, NULL);
	// #endif
	//         target=target->next;
	//     }
	// 
	// // Create Vertex buffer
	// #if HGE_DIRECTX_VER == 8
	//     if( FAILED (pD3DDevice->CreateVertexBuffer(VERTEX_BUFFER_SIZE*sizeof(hgeVertex),
	//                                               D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
	//                                               D3DFVF_HGEVERTEX,
	//                                               D3DPOOL_DEFAULT, &pVB )))
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//     if( FAILED (pD3DDevice->CreateVertexBuffer(VERTEX_BUFFER_SIZE*sizeof(hgeVertex),
	//                                                 D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
	//                                                 D3DFVF_HGEVERTEX,
	//                                                 D3DPOOL_DEFAULT, 
	//                                                 &pVB, 
	//                                                 NULL)))
	// #endif
	//     {
	//         _PostError("Can't create D3D vertex buffer");
	//         return false;
	//     }
	// 
	// #if HGE_DIRECTX_VER == 8
	//     pD3DDevice->SetVertexShader( D3DFVF_HGEVERTEX );
	//     pD3DDevice->SetStreamSource( 0, pVB, sizeof(hgeVertex) );
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//     pD3DDevice->SetVertexShader( NULL );
	//     pD3DDevice->SetFVF( D3DFVF_HGEVERTEX );
	//     pD3DDevice->SetStreamSource( 0, pVB, 0, sizeof(hgeVertex) );
	// #endif
	// 
	// // Create and setup Index buffer
	// 
	// #if HGE_DIRECTX_VER == 8
	//     if( FAILED( pD3DDevice->CreateIndexBuffer(VERTEX_BUFFER_SIZE*6/4*sizeof(hgeU16),
	//                                               D3DUSAGE_WRITEONLY,
	//                                               D3DFMT_INDEX16,
	//                                               D3DPOOL_DEFAULT, &pIB ) ) )
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//     if( FAILED( pD3DDevice->CreateIndexBuffer(VERTEX_BUFFER_SIZE*6/4*sizeof(hgeU16),
	//                                                 D3DUSAGE_WRITEONLY,
	//                                                 D3DFMT_INDEX16,
	//                                                 D3DPOOL_DEFAULT, 
	//                                                 &pIB,
	//                                                 NULL) ) )
	// #endif
	//     {
	//         _PostError("Can't create D3D index buffer");
	//         return false;
	//     }
	// 
	//     hgeU16 *pIndices, n=0;
	// #if HGE_DIRECTX_VER == 8
	//     if( FAILED( pIB->Lock( 0, 0, (hgeU8**)&pIndices, 0 ) ) )
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//     if( FAILED( pIB->Lock( 0, 0, (VOID**)&pIndices, 0 ) ) )
	// #endif
	//     {
	//         _PostError("Can't lock D3D index buffer");
	//         return false;
	//     }
	// 
	//     for(int i=0; i<VERTEX_BUFFER_SIZE/4; i++) {
	//         *pIndices++=n;
	//         *pIndices++=n+1;
	//         *pIndices++=n+2;
	//         *pIndices++=n+2;
	//         *pIndices++=n+3;
	//         *pIndices++=n;
	//         n+=4;
	//     }
	// 
	//     pIB->Unlock();
	// #if HGE_DIRECTX_VER == 8
	//     pD3DDevice->SetIndices(pIB,0);
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//     pD3DDevice->SetIndices(pIB);
	// #endif
	// 
	// // Set common render states
	// 
	//     //pD3DDevice->SetRenderState( D3DRS_LASTPIXEL, FALSE );
	//     pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	//     pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//     
	//     pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
	//     pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	//     pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// 
	//     pD3DDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
	//     pD3DDevice->SetRenderState( D3DRS_ALPHAREF,        0x01 );
	//     pD3DDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
	// 
	//     pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	//     pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	//     pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	// 
	//     pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
	//     pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	//     pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	// 
	// #if HGE_DIRECTX_VER == 8
	//     pD3DDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_POINT);
	//     if(bTextureFilter) {
	//         pD3DDevice->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	//         pD3DDevice->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
	//     } else {
	//         pD3DDevice->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTEXF_POINT);
	//         pD3DDevice->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTEXF_POINT);
	//     }
	// #endif
	// #if HGE_DIRECTX_VER == 9
	//     pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	//     if(bTextureFilter) {
	//         pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//         pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//     } else {
	//         pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//         pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	//     }
	// #endif
	//     nPrim=0;
	// 	CurPrimType = HGEPRIM_QUADS;
	// 
	//     CurBlendMode = BLEND_DEFAULT;
	// 	// Reset default DirectX Zbuffer write to false
	// 	if (false == bZBuffer) {
	// 		pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// 	}
	// 
	// 	CurTexture = NULL;
	// #if HGE_DIRECTX_VER >= 9
	// 	CurShader = NULL;
	// #endif
	// 
	//     pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	//     pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	return true;
}


HSHADER HGE_CALL HGE_Impl::Shader_Create(const char *filename)
{
	// 	LPD3DXBUFFER					code			= NULL;
	// 	LPDIRECT3DPIXELSHADER9          pixelShader    = NULL;
	// 	HRESULT result = D3DXCompileShaderFromFile( filename,   //filepath
	// 												NULL,          //macro's            
	// 												NULL,          //includes           
	// 												"ps_main",     //main function      
	// 												"ps_2_0",      //shader profile     
	// 												0,             //flags              
	// 												&code,         //compiled operations
	// 												NULL,          //errors
	// 												NULL);         //constants
	// 	if(FAILED(result)) {
	// 		_PostError("Can't create shader");
	// 		return NULL;
	// 	}
	// 
	// 	pD3DDevice->CreatePixelShader((DWORD *)code->GetBufferPointer(), &pixelShader);
	// 	code->Release();
	//	return (HSHADER)pixelShader;
	return NULL;
}

void HGE_CALL HGE_Impl::Gfx_SetShader(HSHADER shader)
{
	// 	if (CurShader != shader) {
	// 		_render_batch();
	// 		CurShader = shader;
	// 		pD3DDevice->SetPixelShader((LPDIRECT3DPIXELSHADER9)shader);
	// 	}
}

void HGE_CALL HGE_Impl::Shader_Free(HSHADER shader)
{
	//((LPDIRECT3DPIXELSHADER9)shader)->Release();
}
