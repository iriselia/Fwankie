#include <cassert>
#include "Core.h"
#include "GameEngine.h"
#include "GenericWindow.h"
#include "GenericWindowDefinition.h"
#include "GenericApplication.h"
#include "hge.h"
#include "settings.h"

#include "WindowsApplication.h"

GameEngine* GEngine = NULL;
GenericApplication* GApplication = NULL;

GameEngine::~GameEngine()
{

}

GameEngine::GameEngine()
{

}

GameUserSettings* GameEngine::GetGameUserSettings()
{
	return NULL;
}

#include <d3dx9.h>

#if HGE_DIRECTX_VER == 9
typedef IDirect3D9              hgeGAPI;
typedef IDirect3DDevice9        hgeGAPIDevice;
typedef IDirect3DVertexBuffer9  hgeGAPIVertexBuffer;
typedef IDirect3DIndexBuffer9   hgeGAPIIndexBuffer;
typedef IDirect3DTexture9       hgeGAPITexture;
typedef IDirect3DSurface9       hgeGAPISurface;
typedef D3DVIEWPORT9            hgeGAPIViewport;
typedef D3DADAPTER_IDENTIFIER9  hgeGAPIAdapterIdentifier;
typedef D3DCAPS9				hgeGAPICaps;
#endif

hgeGAPI * pD3D;
D3DPRESENT_PARAMETERS   d3dppW;

void GameEngine::Init(EngineLoop* _pEngineLoop)
{
	// Call base.
	//BaseEngine::Init(InEngineLoop);

	// Load and apply user game settings
	GetGameUserSettings()->LoadSettings();
	GetGameUserSettings()->ApplySettings();

	GApplication = FPlatformMisc::CreateApplication();

	auto window = CreateGameWindow();
	
	static const char *szFormats[] = { "UNKNOWN", "R5G6B5", "X1R5G5B5", "A1R5G5B5", "X8R8G8B8", "A8R8G8B8" };
	hgeGAPIAdapterIdentifier AdID;
	D3DDISPLAYMODE Mode;
	D3DFORMAT Format = D3DFMT_UNKNOWN;
	UINT nModes, i;
// 
// 	// Init D3D
// #if HGE_DIRECTX_VER == 9
// 	pD3D = Direct3DCreate9(D3D_SDK_VERSION); // D3D_SDK_VERSION
// #endif
// 	if (pD3D == NULL)
// 	{
// 		//_PostError("Can't create D3D interface");
// 		//return false;
// 		//error code!!!!!!!!!!!!!!!!
// 	}
// 
// 	// Get adapter info
// 
// #if HGE_DIRECTX_VER == 9
// 	pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &AdID);
// #endif
// 	printf("D3D Driver: %s", AdID.Driver);
// 	printf("Description: %s", AdID.Description);
// 	printf("Version: %d.%d.%d.%d",
// 		HIWORD(AdID.DriverVersion.HighPart),
// 		LOWORD(AdID.DriverVersion.HighPart),
// 		HIWORD(AdID.DriverVersion.LowPart),
// 		LOWORD(AdID.DriverVersion.LowPart));
// 
// 	// Set up Windowed presentation parameters
// 
// 	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Mode)) || Mode.Format == D3DFMT_UNKNOWN)
// 	{
// 		printf("Can't determine desktop video mode");
// 		//if (bWindowed) return false; //todo: why do we return false only on windowed mode?
// 	}
// 
// 	ZeroMemory(&d3dppW, sizeof(d3dppW));
// 
// 	d3dppW.BackBufferWidth = 800; //Gsettings...
// 	d3dppW.BackBufferHeight = 600;
// 	d3dppW.BackBufferFormat = Mode.Format;
// 	d3dppW.BackBufferCount = 1;
// 	d3dppW.MultiSampleType = D3DMULTISAMPLE_NONE;
// 	d3dppW.hDeviceWindow = reinterpret_cast<HWND>(window->GetOSWindowHandle());
// 	d3dppW.Windowed = TRUE;
// 
// 
// #if HGE_DIRECTX_VER == 9
// 	if (nHGEFPS == HGEFPS_VSYNC) {
// 		d3dppW.SwapEffect = D3DSWAPEFFECT_COPY;
// 		d3dppW.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
// 	}
// 	else {
// 		d3dppW.SwapEffect = D3DSWAPEFFECT_COPY;
// 		d3dppW.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
// 	}
// #endif
// 
// 	if (bZBuffer)
// 	{
// 		d3dppW.EnableAutoDepthStencil = TRUE;
// 		d3dppW.AutoDepthStencilFormat = D3DFMT_D16;
// 	}
// 
// 	// Set up Full Screen presentation parameters
// 
// #if HGE_DIRECTX_VER == 9
// 	nModes = pD3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, Mode.Format);
// #endif
// 
// 	for (i = 0; i<nModes; i++)
// 	{
// 
// #if HGE_DIRECTX_VER == 9
// 		pD3D->EnumAdapterModes(D3DADAPTER_DEFAULT, Mode.Format, i, &Mode);
// #endif
// 
// 		if (Mode.Width != (UINT)nScreenWidth || Mode.Height != (UINT)nScreenHeight) continue;
// 		if (nScreenBPP == 16 && (_format_id(Mode.Format) > _format_id(D3DFMT_A1R5G5B5))) continue;
// 		if (_format_id(Mode.Format) > _format_id(Format)) Format = Mode.Format;
// 	}
// 
// 	if (Format == D3DFMT_UNKNOWN)
// 	{
// 		_PostError("Can't find appropriate full screen video mode");
// 		if (!bWindowed) return false;
// 	}
// 
// 	ZeroMemory(&d3dppFS, sizeof(d3dppFS));
// 
// 	d3dppFS.BackBufferWidth = nScreenWidth;
// 	d3dppFS.BackBufferHeight = nScreenHeight;
// 	d3dppFS.BackBufferFormat = Format;
// 	d3dppFS.BackBufferCount = 1;
// 	d3dppFS.MultiSampleType = D3DMULTISAMPLE_NONE;
// 	d3dppFS.hDeviceWindow = hwnd;
// 	d3dppFS.Windowed = FALSE;
// 
// 	d3dppFS.SwapEffect = D3DSWAPEFFECT_FLIP;
// 	d3dppFS.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
// 
// #if HGE_DIRECTX_VER == 9
// 	if (nHGEFPS == HGEFPS_VSYNC) d3dppFS.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
// 	else                      d3dppFS.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
// #endif
// 	if (bZBuffer)
// 	{
// 		d3dppFS.EnableAutoDepthStencil = TRUE;
// 		d3dppFS.AutoDepthStencilFormat = D3DFMT_D16;
// 	}
// 
// 	d3dpp = bWindowed ? &d3dppW : &d3dppFS;
// 
// 	if (_format_id(d3dpp->BackBufferFormat) < 4) nScreenBPP = 16;
// 	else nScreenBPP = 32;
// 
// 	// Create D3D Device
// 	// #if HGE_DIRECTX_VER == 8
// 	//     if( FAILED( pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
// 	//                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
// 	//                                   d3dpp, &pD3DDevice ) ) )
// 	//     {
// 	//         _PostError("Can't create D3D8 device");
// 	//         return false;
// 	//     }
// 	// #endif
// 	// #if HGE_DIRECTX_VER == 9
// 	hgeGAPICaps caps;
// 	pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
// 	hgeU32   vp;
// 	if ((caps.VertexShaderVersion < D3DVS_VERSION(1, 1)) || !(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT))
// 	{
// 		System_Log("Software Vertex-processing device selected");
// 		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
// 	}
// 	else
// 	{
// 		System_Log("Hardware Vertex-processing device selected");
// 		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
// 	}
// 	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, vp, d3dpp, &pD3DDevice)))
// 	{
// 		_PostError("Can't create D3D device");
// 		return false;
// 	}
// 	// #endif
// 
// 	_AdjustWindow();
// 
// 	System_Log("Mode: %d x %d x %s\n", nScreenWidth, nScreenHeight, szFormats[_format_id(Format)]);
// 
// 	// Create vertex batch buffer
// 
// 	VertArray = 0;
// 	textures = 0;
// 
// 	// Init all stuff that can be lost
// 
// 	_SetProjectionMatrix(nScreenWidth, nScreenHeight);
// 	D3DXMatrixIdentity(&matView);
// 
// 	if (!_init_lost()) return false;
// 
// 	Gfx_Clear(0);
// 
// 	return true;

	getchar();
	// Creates the initial world context. For GameEngine, this should be the only WorldContext that ever gets created.
	//FWorldContext &InitialWorldContext = CreateNewWorldContext(EWorldType::Game);

	// Initialize the viewport client.
	//GameViewportClient* ViewportClient = NULL;
	//ViewportClient = new GameViewportClient();
	//ViewportClient->SetReferenceToWorldContext(InitialWorldContext);
	//GameViewport = ViewportClient; 
	// 			InitialWorldContext.GameViewport = ViewportClient;


	// Attach the viewport client to a new viewport.
	//if (ViewportClient)
	{
		// This must be created before any gameplay code adds widgets
		// 			bool bWindowAlreadyExists = GameViewportWindow.IsValid();
		// 			if (!bWindowAlreadyExists)
		// 			{
		// 				GameViewportWindow = CreateGameWindow();
		// 			}
		// 
		// 			CreateGameViewport(ViewportClient);
	}

	// Create default URL.
	// @note:  if we change how we determine the valid start up map update LaunchEngineLoop's GetStartupMap()
	// 		FURL DefaultURL;
	// 		DefaultURL.LoadURLConfig(TEXT("DefaultPlayer"), GGameIni);

	// Enter initial world.
	// 		EBrowseReturnVal::Type BrowseRet = EBrowseReturnVal::Failure;
	// 		FString Error;
	// 		TCHAR Parm[4096] = TEXT("");
	// 		const TCHAR* Tmp = FCommandLine::Get();
	// 
	// 		const UGameMapsSettings* GameMapsSettings = GetDefault<UGameMapsSettings>();
	// 		const FString& DefaultMap = GameMapsSettings->GetGameDefaultMap();
	// 		if (!FParse::Token(Tmp, Parm, ARRAY_COUNT(Parm), 0) || Parm[0] == '-')
	// 		{
	// 			FCString::Strcpy(Parm, *(DefaultMap + GameMapsSettings->LocalMapOptions));
	// 		}
	// 		FURL URL(&DefaultURL, Parm, TRAVEL_Partial);
	// 		if (URL.Valid)
	// 		{
	// 			BrowseRet = Browse(InitialWorldContext, URL, Error);
	// 		}

	// If waiting for a network connection, go into the starting level.
	// 		if (BrowseRet != EBrowseReturnVal::Success && FCString::Stricmp(Parm, *DefaultMap) != 0)
	// 		{
	// 			const FText Message = FText::Format(NSLOCTEXT("Engine", "MapNotFound", "The map specified on the commandline '{0}' could not be found. Would you like to load the default map instead?"), FText::FromString(URL.Map));
	// 
	// 			// the map specified on the command-line couldn't be loaded.  ask the user if we should load the default map instead
	// 			if (FCString::Stricmp(*URL.Map, *DefaultMap) != 0 &&
	// 				FMessageDialog::Open(EAppMsgType::OkCancel, Message) != EAppReturnType::Ok)
	// 			{
	// 				// user canceled (maybe a typo while attempting to run a commandlet)
	// 				FPlatformMisc::RequestExit(false);
	// 				return;
	// 			}
	// 			else
	// 			{
	// 				BrowseRet = Browse(InitialWorldContext, FURL(&DefaultURL, *(DefaultMap + GameMapsSettings->LocalMapOptions), TRAVEL_Partial), Error);
	// 			}
	// 		}

	// Handle failure.
	// 		if (BrowseRet != EBrowseReturnVal::Success)
	// 		{
	// 			UE_LOG(LogLoad, Fatal, TEXT("%s"), *FString::Printf(TEXT("Failed to enter %s: %s. Please check the log for errors."), Parm, *Error));
	// 		}
	// 		UE_LOG(LogInit, Display, TEXT("Game Engine Initialized."));

	// for IsInitialized()
	m_bIsInitialized = true;
}

std::shared_ptr<GenericWindow> GameEngine::CreateGameWindow()
{
// 	int32 ResX = GSystemResolution.ResX;
// 	int32 ResY = GSystemResolution.ResY;
// 	EWindowMode::Type WindowMode = GSystemResolution.WindowMode;
// 	ConditionallyOverrideSettings(ResX, ResY, WindowMode);
// 
// 	// If the current settings have been overridden, apply them back into the system
// 	if (ResX != GSystemResolution.ResX || ResY != GSystemResolution.ResY || WindowMode != GSystemResolution.WindowMode)
// 	{
// 		FSystemResolution::RequestResolutionChange(ResX, ResY, WindowMode);
// 		GSystemResolution.ResX = ResX;
// 		GSystemResolution.ResY = ResY;
// 		GSystemResolution.WindowMode = WindowMode;
// 	}
// 
// #if PLATFORM_64BITS
// 	//These are invariant strings so they don't need to be localized
// 	const FText PlatformBits = FText::FromString(TEXT("64"));
// #else	//PLATFORM_64BITS
// 	const FText PlatformBits = FText::FromString(TEXT("32"));
// #endif	//PLATFORM_64BITS
// 
// 	FFormatNamedArguments Args;
// 	Args.Add(TEXT("GameName"), FText::FromString(FApp::GetGameName()));
// 	Args.Add(TEXT("PlatformArchitecture"), PlatformBits);
// 	Args.Add(TEXT("RHIName"), FText::FromName(LegacyShaderPlatformToShaderFormat(GRHIShaderPlatform)));
// 
// 	const FText AppName = FText::Format(NSLOCTEXT("UnrealEd", "GameWindowTitle", "{GameName} ({PlatformArchitecture}-bit, {RHIName})"), Args);
// 
// 	// Allow optional winX/winY parameters to set initial window position
// 	EAutoCenter::Type AutoCenterType = EAutoCenter::PrimaryWorkArea;
// 	int32 WinX = 0;
// 	int32 WinY = 0;
// 	if (FParse::Value(FCommandLine::Get(), TEXT("WinX="), WinX) && FParse::Value(FCommandLine::Get(), TEXT("WinY="), WinY))
// 	{
// 		AutoCenterType = EAutoCenter::None;
// 	}

// 	HGE* hge = hgeCreate(HGE_VERSION);
// 
// 	Settings::load(TEXT("config.txt"));
// 	bool b_windowed = true;
// 
// 	hge->System_SetState(HGE_LOGFILE, "resources/game.log");
// 	//hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
// 	//hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
// 	hge->System_SetState(HGE_TITLE, "Project 3: basic animation and map loading");
// 	hge->System_SetState(HGE_WINDOWED, b_windowed);
// 	hge->System_SetState(HGE_SCREENBPP, 32);
// 	hge->System_SetState(HGE_FPS, 60);
// 	hge->System_SetState(HGE_USETRANSPARENTCOLOR, true);
// 
// 	assert(hge->System_Initiate());

	auto Definition = std::shared_ptr< GenericWindowDefinition > (new GenericWindowDefinition());

	Definition->WidthDesiredOnScreen = 800;// GSettings.ResX;
	Definition->HeightDesiredOnScreen = 600;// GSettings.ResY;
	Definition->XDesiredPositionOnScreen = 100;// GSettings.PosX;
	Definition->YDesiredPositionOnScreen = 100;// GSettings.PosY;

	//AUTO CENTER RALTED CODE
	// Allow optional winX/winY parameters to set initial window position
// 	EAutoCenterType AutoCenterType = EAutoCenter::PrimaryWorkArea;
// 	int32 WinX = 0;
// 	int32 WinY = 0;
// 	if (FParse::Value(FCommandLine::Get(), TEXT("WinX="), WinX) && FParse::Value(FCommandLine::Get(), TEXT("WinY="), WinY))
// 	{
// 		AutoCenterType = EAutoCenter::None;
// 	}



	Definition->HasOSWindowBorder = true;
	Definition->SupportsTransparency = false;
	//Definition->AppearsInTaskbar = InSlateWindow->AppearsInTaskbar();
	//Definition->IsTopmostWindow = InSlateWindow->IsTopmostWindow();
	Definition->AcceptsInput = true; //InSlateWindow->AcceptsInput();
	Definition->ActivateWhenFirstShown = true;
	
	Definition->SupportsMinimize = true;
	Definition->SupportsMaximize = true;
	//Definition->IsRegularWindow = InSlateWindow->IsRegularWindow();
	//Definition->HasSizingFrame = InSlateWindow->HasSizingFrame();
	//Definition->SizeWillChangeOften = InSlateWindow->SizeWillChangeOften();
	//Definition->ExpectedMaxWidth = InSlateWindow->GetExpectedMaxWidth();
	//Definition->ExpectedMaxHeight = InSlateWindow->GetExpectedMaxHeight();

#if PLATFORM_64BITS
	//These are invariant strings so they don't need to be localized
	const TCHAR PlatformBits[] = TEXT("64");
#else	//PLATFORM_64BITS
	const TCHAR PlatformBits[] = TEXT("32");
#endif	//PLATFORM_64BITS
	TCHAR AppName[32] = TEXT("");
	_tsprintf(AppName, 32, TEXT("%s (%s-bit, %s)"), TEXT("A"), PlatformBits, TEXT("B"));

	Definition->Title = AppName; //Already set up
	Definition->Opacity = 1.0;
	//Definition->CornerRadius = InSlateWindow->GetCornerRadius();

	const bool bShowImmediately = false;

	auto NewWindow = GApplication->MakeWindow();
	GApplication->InitializeWindow(NewWindow, Definition, /* parent window */NULL, bShowImmediately);
	//FSlateApplication::Get().AddWindow(Window, bShowImmediately);

	// Do not set fullscreen mode here, since it doesn't take 
	// HMDDevice into account. The window mode will be set properly later
	// from SwitchGameWindowToUseGameViewport() method (see ResizeWindow call).

	NewWindow->SetWindowMode(EWindowModeType::Windowed);

	NewWindow->Show();

	//GApplication->Tick();
	// Tick now to force a redraw of the window and ensure correct fullscreen application

	return NewWindow;
}
