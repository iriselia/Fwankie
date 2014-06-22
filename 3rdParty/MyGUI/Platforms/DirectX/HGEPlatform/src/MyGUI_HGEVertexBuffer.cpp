/*!
	@file
	@author		Losev Vasiliy aka bool
	@date		06/2009
*/

#include <d3dx9.h>
#include "MyGUI_HGEVertexBuffer.h"
#include "MyGUI_VertexData.h"
#include "MyGUI_HGEDiagnostic.h"

namespace MyGUI
{

	const size_t VERTEX_IN_QUAD = 6;
	const size_t RENDER_ITEM_STEEP_REALLOCK = 5 * VERTEX_IN_QUAD;

	HGEVertexBuffer::HGEVertexBuffer(HGE* _hge, HGERenderManager* _pRenderManager) :
		mNeedVertexCount(0),
		mVertexCount(RENDER_ITEM_STEEP_REALLOCK),
		mpHGE(_hge),
		//mpD3DDevice(_device),
		pRenderManager(_pRenderManager),
		mpBuffer(NULL)
	{
	}

	HGEVertexBuffer::~HGEVertexBuffer()
	{
		destroy();
	}

	void HGEVertexBuffer::setVertexCount(size_t _count)
	{
		if (_count != mNeedVertexCount)
		{
			mNeedVertexCount = _count;
			resize();
		}
	}

	size_t HGEVertexBuffer::getVertexCount()
	{
		return mNeedVertexCount;
	}

	Vertex* HGEVertexBuffer::lock()
	{
		return mpBuffer;
		/*
		void* lockPtr = nullptr;
		HRESULT result = mpBuffer->Lock(0, 0, (void**)&lockPtr, 0);
		if (FAILED(result))
		{
			MYGUI_PLATFORM_EXCEPT("Failed to lock vertex buffer (error code " << result << ").");
		}
		return (Vertex*)lockPtr;
		*/
	}

	void HGEVertexBuffer::unlock()
	{
		/*
		HRESULT result = mpBuffer->Unlock();
		if (FAILED(result))
		{
			MYGUI_PLATFORM_EXCEPT("Failed to unlock vertex buffer (error code " << result << ").");
		}
		*/
	}

	bool HGEVertexBuffer::setToStream(size_t stream)
	{
		/*
		if (SUCCEEDED(mpD3DDevice->SetStreamSource(stream, mpBuffer, 0, sizeof(MyGUI::Vertex))))
			return true;
		*/
		return false;
	}

	bool HGEVertexBuffer::create()
	{
		mpBuffer = new Vertex[mNeedVertexCount];
		memset(mpBuffer, 0, mNeedVertexCount*sizeof(Vertex));
		if (mpBuffer) return true;
		return false;
		/*
		DWORD length = mNeedVertexCount * sizeof(MyGUI::Vertex);
		if (SUCCEEDED(mpD3DDevice->CreateVertexBuffer(length, 0, 0, D3DPOOL_MANAGED, &mpBuffer, nullptr)))
			return false;
		return false;
		*/
	}

	void HGEVertexBuffer::destroy()
	{
		if (mpBuffer)
		{
			delete mpBuffer;
			mpBuffer = nullptr;
		}
	}

	void HGEVertexBuffer::resize()
	{
		if (mpBuffer)
			destroy();

		create();
		/*
		if (mpD3DDevice)
		{
			destroy();
			create();
		}
		*/
	}

} // namespace MyGUI
