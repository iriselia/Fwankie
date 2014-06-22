/*!
	@file
	@author		Albert Semenov
	@date		05/2009
*/


#include "Precompiled.h"
#include <d3dx9.h>
#include "BaseManager.h"
#include <MyGUI_HGEPlatform.h>
#include "hgesprite.h"

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
#	include <windows.h>
#	include <winuser.h>
#endif

// имя класса окна
const char* WND_CLASS_NAME = "MyGUI_Demo_window";
//FIX THIS HACK
base::BaseManager* basemanager = nullptr;

LRESULT CALLBACK DXWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)((LPCREATESTRUCT)lParam)->lpCreateParams);
		break;
	}

	case WM_SIZE:
	{
		if (wParam != SIZE_MINIMIZED)
		{
			base::BaseManager* baseManager = (base::BaseManager*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (baseManager)
				baseManager->_windowResized();
		}
		break;
	}

	case WM_CLOSE:
	{
		base::BaseManager* baseManager = (base::BaseManager*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (baseManager)
			baseManager->quit();
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	default:
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	}
	return 0;
}

//FIX THIS HACK
bool frame()
{
	if (basemanager)
	{
		return basemanager->HgeFrameFunc();
	}
	return false;
}

namespace base
{

	D3DPRESENT_PARAMETERS mD3dpp;

#pragma region Initialization

	void BaseManager::registerWindow(HWND _hWnd, HGE* _mpHGE, bool _isWindowed) {
		hWnd = _hWnd;
		mpHGE = _mpHGE;

#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32

		char buf[MAX_PATH];
		::GetModuleFileNameA(0, (LPCH)&buf, MAX_PATH);

		HINSTANCE instance = ::GetModuleHandleA(buf);

		HICON hIcon = ::LoadIcon(instance, MAKEINTRESOURCE(1001));
		if (hIcon)
		{
			::SendMessageA((HWND)hWnd, WM_SETICON, 1, (LPARAM)hIcon);
			::SendMessageA((HWND)hWnd, WM_SETICON, 0, (LPARAM)hIcon);
		}
#endif

		hInstance = instance;

		RECT rect = { 0, 0, 0, 0 };
		GetClientRect(hWnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		windowAdjustSettings(hWnd, width, height, !_isWindowed);

		//createRender(width, height, _isWindowed);

		createGui();

		createInput((size_t)hWnd);

		createPointerManager((size_t)hWnd);

		createScene();

		_windowResized();
	}

	void BaseManager::shutdown() {
		destroyScene();

		destroyPointerManager();

		destroyInput();

		destroyGui();

		//destroyRender();
	}

	void BaseManager::createGui()
	{
		mPlatform = new MyGUI::HGEPlatform();
		mPlatform->initialise(mpHGE);

		setupResources();

		mGUI = new MyGUI::Gui();
		mGUI->initialise(mResourceFileName);

		mInfo = new diagnostic::StatisticInfo();
		mFocusInfo = new diagnostic::InputFocusInfo();
	}

	void BaseManager::destroyGui()
	{
		if (mGUI)
		{
			if (mInfo)
			{
				delete mInfo;
				mInfo = nullptr;
			}

			if (mFocusInfo)
			{
				delete mFocusInfo;
				mFocusInfo = nullptr;
			}

			mGUI->shutdown();
			delete mGUI;
			mGUI = nullptr;
		}

		if (mPlatform)
		{
			mPlatform->shutdown();
			delete mPlatform;
			mPlatform = nullptr;
		}
	}

	/*
	@Steps to activate gui:
	@1 construct basemanager.
	@2 registerWindow.
	*/
	BaseManager::BaseManager() :
		mGUI(nullptr),
		mPlatform(nullptr),
		mInfo(nullptr),
		mFocusInfo(nullptr),
		hWnd(0),
		/*
		mD3d(nullptr),
		mDevice(nullptr),
		*/
		mpHGE(nullptr),
		hInstance(nullptr),
		mExit(false),
		mResourceFileName("MyGUI_Core.xml"),
		mIsDeviceLost(false)
	{
		basemanager = this;
	}

	BaseManager::~BaseManager()
	{
	}
#pragma endregion Initialization

#pragma region main loop funcs
	//Does nothing at the moment.
	void BaseManager::prepare()
	{
	}
	
	bool BaseManager::create()
	{
		const unsigned int width = 1024;
		const unsigned int height = 768;
		bool windowed = true;

		mpHGE = hgeCreate(HGE_VERSION);
		if (!mpHGE)
			return false;

		mpHGE->System_SetState(HGE_WINDOWED, windowed);
		mpHGE->System_SetState(HGE_SCREENWIDTH, width);
		mpHGE->System_SetState(HGE_SCREENHEIGHT, height);
		mpHGE->System_SetState(HGE_USESOUND, false);
		mpHGE->System_SetState(HGE_HIDEMOUSE, false);
		mpHGE->System_SetState(HGE_SHOWSPLASH, true);
		mpHGE->System_SetState(HGE_FPS, 100);
		mpHGE->System_SetState(HGE_LOGFILE, "hge.log");
		mpHGE->System_SetState(HGE_FRAMEFUNC, frame);

		if (!mpHGE->System_Initiate())
			return false;
		
		hWnd = mpHGE->System_GetState(HGE_HWND);
		//hgeSprite			*portalSprite;
		//HTEXTURE hPortal = mpHGE->Texture_Load("resources/gems.png");
		//portalSprite = new hgeSprite(hPortal, 0, 31, 32, 32);
		//portalSprite->Render(0, 0);
		/*
		
		WNDCLASS wc =
		{
			0, (WNDPROC)DXWndProc, 0, 0, GetModuleHandle(NULL), LoadIcon(NULL, MAKEINTRESOURCE(1001)),
			LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), NULL, TEXT(WND_CLASS_NAME),
		};
		RegisterClass(&wc);


		hWnd = CreateWindow(wc.lpszClassName, TEXT("Direct3D9 Render Window"), WS_POPUP,
			0, 0, 0, 0, GetDesktopWindow(), NULL, wc.hInstance, this);
		if (!hWnd)
		{
			//OutException("fatal error!", "failed create window");
			return false;
		}
		*/
	#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32

		char buf[MAX_PATH];
		::GetModuleFileNameA(0, (LPCH)&buf, MAX_PATH);

		HINSTANCE instance = ::GetModuleHandleA(buf);

		HICON hIcon = ::LoadIcon(instance, MAKEINTRESOURCE(1001));
		if (hIcon)
		{
			::SendMessageA((HWND)hWnd, WM_SETICON, 1, (LPARAM)hIcon);
			::SendMessageA((HWND)hWnd, WM_SETICON, 0, (LPARAM)hIcon);
		}
	#endif

		hInstance = instance;

		windowAdjustSettings(hWnd, width, height, !windowed);

		createRender(width, height, windowed);

		createGui();

		createInput((size_t)hWnd);

		createPointerManager((size_t)hWnd);

		createScene();

		_windowResized();

		return true;
	}

	#pragma region frame funcs
	void BaseManager::updateFPS()
	{
		if (mInfo)
		{
			// calculate FPS
			static MyGUI::Timer timer;
			const unsigned long interval = 1000;
			static int count_frames = 0;
			int accumulate = timer.getMilliseconds();
			if (accumulate > interval)
			{
				mInfo->change("FPS", (int)((unsigned long)count_frames * 1000 / accumulate));
				mInfo->update();

				count_frames = 0;
				timer.reset();
			}
			count_frames++;
		}
	}

	void BaseManager::drawOneFrame()
	{


		/*
		hgeSprite			*portalSprite;
		HTEXTURE hPortal = mpHGE->Texture_Load("resources/gems.png");
		portalSprite = new hgeSprite(hPortal, 0, 31, 32, 32);
		hgeTriple* triple;

		hgeQuad quad;
		quad.blend = BLEND_ALPHABLEND | BLEND_COLORMUL | BLEND_NOZWRITE;

		for (int i = 0; i < 4; i++)
		{
		// Set up z-coordinate of vertices
		quad.v[i].z = 0.5f;
		// Set up color. The format of DWORD col is 0xAARRGGBB
		quad.v[i].col = 0xFFFFFFFF;
		}

		quad.v[0].x = 0; quad.v[0].y = 0;
		quad.v[1].x = 800; quad.v[1].y = 0;
		quad.v[2].x = 800; quad.v[2].y = 600;
		quad.v[3].x = 0; quad.v[3].y = 600;

		quad.tex = mpHGE->Texture_Load("resources/bg.png");

		float dt = mpHGE->Timer_GetDelta();
		static float t = 0.0f;
		float tx, ty;

		t += dt;
		tx = 50 * cosf(t / 60);
		ty = 50 * sinf(t / 60);

		quad.v[0].tx = tx;        quad.v[0].ty = ty;
		quad.v[1].tx = tx + 800 / 64; quad.v[1].ty = ty;
		quad.v[2].tx = tx + 800 / 64; quad.v[2].ty = ty + 600 / 64;
		quad.v[3].tx = tx;        quad.v[3].ty = ty + 600 / 64;
		*/
		mpHGE->Gfx_BeginScene();
		//mpHGE->Gfx_Clear(0);
		mPlatform->getRenderManagerPtr()->drawOneFrame();
		//portalSprite->Render(500, 500);
		//mpHGE->Gfx_RenderQuad(&quad);
		mpHGE->Gfx_EndScene();

		/*
		if (mIsDeviceLost == true)
		{
		Sleep( 100 );

		HRESULT hr;
		if (FAILED(hr = mDevice->TestCooperativeLevel()))
		{
		if (hr == D3DERR_DEVICELOST)
		return;

		if (hr == D3DERR_DEVICENOTRESET)
		{
		if (mPlatform != nullptr)
		mPlatform->getRenderManagerPtr()->deviceLost();

		hr = mDevice->Reset( &mD3dpp );

		if (FAILED(hr))
		return;

		if (mPlatform != nullptr)
		mPlatform->getRenderManagerPtr()->deviceRestore();
		}

		return;
		}

		mIsDeviceLost = false;
		}

		if (SUCCEEDED(mDevice->BeginScene()))
		{
		mDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		mPlatform->getRenderManagerPtr()->drawOneFrame();
		mDevice->EndScene();
		}

		if (mDevice->Present(NULL, NULL, 0, NULL) == D3DERR_DEVICELOST)
		mIsDeviceLost = true;
		*/
	}

	bool BaseManager::HgeFrameFunc()
	{
		captureInput();
		updateFPS();
		drawOneFrame();
		return false;
	}
	#pragma endregion frame funcs

	void BaseManager::run()
	{
		mpHGE->System_Start();
		/*
		MSG msg;
		while (true)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (mExit)
				break;
			else if (msg.message == WM_QUIT)
				break;

			captureInput();
			updateFPS();
			drawOneFrame();

			if (GetActiveWindow() != hWnd)
				::Sleep(50);
		}
		*/
	}

	void BaseManager::destroy()
	{
		destroyScene();

		destroyPointerManager();

		destroyInput();

		destroyGui();

		destroyRender();

		if (mpHGE)
		{
			mpHGE->System_Shutdown();
			mpHGE->Release();
		}
		/*
		if (hWnd)
		{
			DestroyWindow(hWnd);
			hWnd = 0;
		}

		UnregisterClass(WND_CLASS_NAME, hInstance);
		*/
	}

#pragma endregion main loop funcs

#pragma region window manipulation
	//Do not call this. Go through HGE.
	void BaseManager::windowAdjustSettings(HWND hWnd, int width, int height, bool fullScreen)
	{

		HWND hwndAfter = 0;
		unsigned long style = 0;
		unsigned long style_ex = 0;

		RECT rc = { 0, 0, width, height };

		if (fullScreen)
		{
			style = WS_POPUP | WS_VISIBLE;
			style_ex = GetWindowLong(hWnd, GWL_EXSTYLE) | (WS_EX_TOPMOST);
			hwndAfter = HWND_TOPMOST;
		}
		else
		{
			style = WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME;
			style_ex = GetWindowLong(hWnd, GWL_EXSTYLE) & (~WS_EX_TOPMOST);
			hwndAfter = HWND_NOTOPMOST;
			AdjustWindowRect(&rc, style, false);
		}

		SetWindowLong(hWnd, GWL_STYLE, style);
		SetWindowLong(hWnd, GWL_EXSTYLE, style_ex);

		int desk_width = GetSystemMetrics(SM_CXSCREEN);
		int desk_height = GetSystemMetrics(SM_CYSCREEN);

		int w = rc.right - rc.left;
		int h = rc.bottom - rc.top;
		int x = fullScreen ? 0 : (desk_width - w) / 2;
		int y = fullScreen ? 0 : (desk_height - h) / 2;

		SetWindowPos(hWnd, hwndAfter, x, y, w, h, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	}

	void BaseManager::setWindowCaption(const std::wstring& _text)
	{
		SetWindowTextW(hWnd, _text.c_str());
	}

	/*
	call this function when your windows is resized. Mygui needs to know
	to fix sizing issues and input injection.
	*/
	void BaseManager::_windowResized()
	{
		RECT rect = { 0, 0, 0, 0 };
		GetClientRect(hWnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		resizeRender(width, height);

		if (mPlatform)
			mPlatform->getRenderManagerPtr()->setViewSize(width, height);

		setInputViewSize(width, height);
	}
#pragma endregion window manipulation

#pragma region resource init funcs
	/*
	Attempt to read resources.xml to set up paths to other resources.
	*/
	void BaseManager::setupResources()
	{
		MyGUI::xml::Document doc;

		if (!doc.open(std::string("resources.xml")))
			doc.getLastError();

		MyGUI::xml::ElementPtr root = doc.getRoot();
		if (root == nullptr || root->getName() != "Paths")
			return;

		MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
		while (node.next())
		{
			if (node->getName() == "Path")
			{
				bool root = false;
				if (node->findAttribute("root") != "")
				{
					root = MyGUI::utility::parseBool(node->findAttribute("root"));
					if (root) mRootMedia = node->getContent();
				}
				addResourceLocation(node->getContent(), false);
			}
		}

		addResourceLocation(getRootMedia() + "/Common/Base");
	}

	/*
	Returns the path to root media. Does not perform any kind of data initialization.
	*/
	const std::string& BaseManager::getRootMedia()
	{
		return mRootMedia;
	}

	void BaseManager::setResourceFilename(const std::string& _flename)
	{
		mResourceFileName = _flename;
	}

	void BaseManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		mPlatform->getDataManagerPtr()->addResourceLocation(_name, _recursive);
	}
#pragma endregion resource init funcs

#pragma region inject input

	void BaseManager::injectMouseMove(int _absx, int _absy, int _absz)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectMouseMove(_absx, _absy, _absz);
	}

	void BaseManager::injectMousePress(int _absx, int _absy, MyGUI::MouseButton _id)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectMousePress(_absx, _absy, _id);
	}

	void BaseManager::injectMouseRelease(int _absx, int _absy, MyGUI::MouseButton _id)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectMouseRelease(_absx, _absy, _id);
	}

	void BaseManager::injectKeyPress(MyGUI::KeyCode _key, MyGUI::Char _text)
	{
		if (!mGUI)
			return;

		if (_key == MyGUI::KeyCode::Escape)
		{
			mExit = true;
			return;
		}
		else if (_key == MyGUI::KeyCode::F12)
		{
			bool visible = mFocusInfo->getFocusVisible();
			mFocusInfo->setFocusVisible(!visible);
		}

		MyGUI::InputManager::getInstance().injectKeyPress(_key, _text);
	}

	void BaseManager::injectKeyRelease(MyGUI::KeyCode _key)
	{
		if (!mGUI)
			return;

		MyGUI::InputManager::getInstance().injectKeyRelease(_key);
	}
#pragma endregion inject input

#pragma region useless
	//Currently does nothing
	void BaseManager::resizeRender(int _width, int _height)
	{
		/*
		if (mDevice != nullptr)
		{
			if (mPlatform != nullptr)
				mPlatform->getRenderManagerPtr()->deviceLost();

			mD3dpp.BackBufferWidth = _width;
			mD3dpp.BackBufferHeight = _height;
			HRESULT hr = mDevice->Reset(&mD3dpp);

			if (hr == D3DERR_INVALIDCALL)
			{
				MessageBox( NULL, "Call to Reset() failed with D3DERR_INVALIDCALL! ",
					"ERROR", MB_OK | MB_ICONEXCLAMATION );
			}

			if (mPlatform != nullptr)
				mPlatform->getRenderManagerPtr()->deviceRestore();
		}
		*/
	}

	//Currently only returns true
	bool BaseManager::createRender(int _width, int _height, bool _windowed)
	{
		/*

		mD3d = Direct3DCreate9(D3D_SDK_VERSION);

		D3DDISPLAYMODE d3ddm;
		mD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		memset(&mD3dpp, 0, sizeof(mD3dpp));
		mD3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		mD3dpp.EnableAutoDepthStencil = TRUE;
		mD3dpp.BackBufferCount  = 1;
		mD3dpp.BackBufferFormat = d3ddm.Format;
		mD3dpp.BackBufferWidth  = _width;
		mD3dpp.BackBufferHeight = _height;
		mD3dpp.hDeviceWindow = hWnd;
		mD3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
		mD3dpp.Windowed = _windowed;

		if (FAILED(mD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &mD3dpp, &mDevice)))
		{
			//OutException("fatal error!", "failed create d3d9 mDevice");
			return false;
		}
		*/
		return true;
	}

	bool mIsDeviceLost = false;

	//Does not do anything.
	void BaseManager::destroyRender()
	{
		/*
		if (mDevice)
		{
			mDevice->Release();
			mDevice = 0;
		}
		if (mD3d)
		{
			mD3d->Release();
			mD3d = 0;
		}
		*/
	}

	//Do not use MyGUI quit func, let HGE quit instead
	void BaseManager::quit()
	{
		mExit = true;
	}
#pragma endregion useless

	diagnostic::StatisticInfo* BaseManager::getStatisticInfo()
	{
		return mInfo;
	}

	diagnostic::InputFocusInfo* BaseManager::getFocusInput()
	{
		return mFocusInfo;
	}

} // namespace base
