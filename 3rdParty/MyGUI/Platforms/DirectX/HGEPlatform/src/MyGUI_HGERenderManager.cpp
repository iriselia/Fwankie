/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#include <d3dx9.h>
#include "MyGUI_HGERenderManager.h"
#include "MyGUI_HGETexture.h"
#include "MyGUI_HGEVertexBuffer.h"
#include "MyGUI_HGEDiagnostic.h"
#include "MyGUI_Gui.h"
#include "MyGUI_Timer.h"

namespace MyGUI
{

	HGERenderManager::HGERenderManager() :
		mIsInitialise(false),
		mpHGE(nullptr),
		mUpdate(false)
	{
	}

	void HGERenderManager::initialise(HGE* _hge)
	{
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());
		MYGUI_PLATFORM_ASSERT(_hge, getClassTypeName() << " HGE pointer is null");
		
		if(!_hge) return;
		mpHGE = _hge;
		setViewSize(_hge->System_GetState(HGE_SCREENWIDTH),
					_hge->System_GetState(HGE_SCREENHEIGHT));
		mVertexFormat = VertexColourType::ColourARGB;

		memset(&mInfo, 0, sizeof(mInfo));
		/*

		if (mpD3DDevice != nullptr)
		{
			D3DVIEWPORT9 vp;
			mpD3DDevice->GetViewport(&vp);
			setViewSize(vp.Width, vp.Height);
		}

		mUpdate = false;

		if (mpD3DDevice != nullptr)
		{
		D3DCAPS9 caps;
		mpD3DDevice->GetDeviceCaps(&caps);
		if (caps.TextureCaps & D3DPTEXTURECAPS_SQUAREONLY)
		{
		MYGUI_PLATFORM_LOG(Warning, "Non-squared textures not supported.");
		}
		}
		*/
		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
	}

	void HGERenderManager::shutdown()
	{
		MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

		destroyAllResources();
		//mpD3DDevice = nullptr;

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
		mIsInitialise = false;
	}

	IVertexBuffer* HGERenderManager::createVertexBuffer()
	{
		return new HGEVertexBuffer(mpHGE, this);
	}

	void HGERenderManager::destroyVertexBuffer(IVertexBuffer* _buffer)
	{
		delete _buffer;
	}

	void HGERenderManager::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		HGETexture* dxTex = static_cast<HGETexture*>(_texture);
		HGEVertexBuffer* dxVB = static_cast<HGEVertexBuffer*>(_buffer);
		//mpD3DDevice->SetTexture(0, dxTex->getHGETexture());
		MyGUI::Vertex* pVertex = dxVB->lock();
		hgeTriple triple;
		triple.tex = dxTex->getHGETexture();
		triple.blend = BLEND_DEFAULT;
		for (size_t t = 0; t < _count; t += 3) {
			memcpy(triple.v, pVertex + t, 3 * sizeof(Vertex));
			mpHGE->Gfx_RenderTriple(&triple);
		}
		/*
		dxVB->setToStream(0);
		// count in vertexes, triangle_list = vertexes / 3
		mpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _count / 3);
		*/
	}

	void HGERenderManager::drawOneFrame()
	{
		Gui* gui = Gui::getInstancePtr();
		if (gui == nullptr)
			return;

		static Timer timer;
		static unsigned long last_time = timer.getMilliseconds();
		unsigned long now_time = timer.getMilliseconds();
		unsigned long time = now_time - last_time;

		onFrameEvent((float)((double)(time) / (double)1000));

		last_time = now_time;

		begin();
		onRenderToTarget(this, mUpdate);
		end();

		mUpdate = false;
	}

	void HGERenderManager::begin()
	{
		/*
		mpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		mpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		mpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_DIFFUSE);
		mpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		mpD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG0, D3DTA_DIFFUSE);
		mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		mpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		mpD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		mpD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		mpD3DDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

		mpD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		mpD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

		mpD3DDevice->SetRenderState(D3DRS_SRCBLEND,   D3DBLEND_SRCALPHA);
		mpD3DDevice->SetRenderState(D3DRS_DESTBLEND,  D3DBLEND_INVSRCALPHA);

		mpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		mpD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		mpD3DDevice->SetRenderState(D3DRS_LIGHTING, 0);
		mpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		mpD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		mpD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);

		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		mpD3DDevice->SetTransform(D3DTS_WORLD, &m);
		mpD3DDevice->SetTransform(D3DTS_VIEW, &m);
		mpD3DDevice->SetTransform(D3DTS_PROJECTION, &m);
		*/
	}

	void HGERenderManager::end()
	{
	}

	ITexture* HGERenderManager::createTexture(const std::string& _name)
	{
		MapTexture::const_iterator item = mTextures.find(_name);
		MYGUI_PLATFORM_ASSERT(item == mTextures.end(), "Texture '" << _name << "' already exist");

		HGETexture* texture = new HGETexture(_name, mpHGE);
		mTextures[_name] = texture;
		return texture;
	}

	void HGERenderManager::destroyTexture(ITexture* _texture)
	{
		if (_texture == nullptr)
			return;

		MapTexture::iterator item = mTextures.find(_texture->getName());
		MYGUI_PLATFORM_ASSERT(item != mTextures.end(), "Texture '" << _texture->getName() << "' not found");

		mTextures.erase(item);
		delete _texture;
	}

	ITexture* HGERenderManager::getTexture(const std::string& _name)
	{
		MapTexture::const_iterator item = mTextures.find(_name);
		if (item == mTextures.end())
			return nullptr;
		return item->second;
	}

	bool HGERenderManager::isFormatSupported(PixelFormat _format, TextureUsage _usage)
	{
		// 此处返回false会使freetype font 创建的时候使用A8R8G8B8颜色格式
		// 其他可能用到的地方需要自己调整
		/*
		D3DFORMAT internalFormat = D3DFMT_UNKNOWN;
		unsigned long internalUsage = 0;
		D3DPOOL internalPool = D3DPOOL_MANAGED;

		if (_usage == TextureUsage::RenderTarget)
		{
			internalUsage |= D3DUSAGE_RENDERTARGET;
			internalPool = D3DPOOL_MANAGED;
		}
		else if (_usage == TextureUsage::Dynamic)
			internalUsage |= D3DUSAGE_DYNAMIC;
		else if (_usage == TextureUsage::Stream)
			internalUsage |= D3DUSAGE_DYNAMIC;

		if (_format == PixelFormat::R8G8B8A8)
		{
			internalFormat = D3DFMT_A8R8G8B8;
		}
		else if (_format == PixelFormat::R8G8B8)
		{
			internalFormat = D3DFMT_R8G8B8;
		}
		else if (_format == PixelFormat::L8A8)
		{
			internalFormat = D3DFMT_A8L8;
		}
		else if (_format == PixelFormat::L8)
		{
			internalFormat = D3DFMT_L8;
		}

		D3DFORMAT requestedlFormat = internalFormat;
		D3DXCheckTextureRequirements(mpD3DDevice, NULL, NULL, NULL, internalUsage, &internalFormat, internalPool);

		bool result = requestedlFormat == internalFormat;
		if (!result)
			MYGUI_PLATFORM_LOG(Warning, "Texture format '" << requestedlFormat << "'is not supported.");
		return result;
		*/
		return false;
	}

	void HGERenderManager::destroyAllResources()
	{
		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			delete item->second;
		}
		mTextures.clear();
	}

	void HGERenderManager::setViewSize(int _width, int _height)
	{
		if (_height == 0)
			_height = 1;
		if (_width == 0)
			_width = 1;

		mViewSize.set(_width, _height);

		mInfo.maximumDepth = 0.5f; //0.0f
		mInfo.hOffset = -0.5f;// / float(mViewSize.width);
		mInfo.vOffset = -0.5f;// / float(mViewSize.height);
		mInfo.aspectCoef = float(mViewSize.height) / float(mViewSize.width);
		mInfo.pixScaleX = 0.5f;//0.5f / float(mViewSize.width);
		mInfo.pixScaleY = -0.5f;//-0.5f / float(mViewSize.height);

		onResizeView(mViewSize);

		mUpdate = true;
	}

	void HGERenderManager::deviceLost()
	{
		MYGUI_PLATFORM_LOG(Info, "device D3D lost");

		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			static_cast<HGETexture*>(item->second)->deviceLost();
		}
	}

	void HGERenderManager::deviceRestore()
	{
		MYGUI_PLATFORM_LOG(Info, "device D3D restore");

		for (MapTexture::const_iterator item = mTextures.begin(); item != mTextures.end(); ++item)
		{
			static_cast<HGETexture*>(item->second)->deviceRestore();
		}

		mUpdate = true;
	}

} // namespace MyGUI
