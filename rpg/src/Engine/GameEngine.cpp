#include <cassert>
#include "Core.h"
#include "GameEngine.h"
#include "GenericWindow.h"
#include "GenericWindowDefinition.h"
#include "GenericApplication.h"
#include "hge.h"
#include "settings.h"

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

void GameEngine::Init(EngineLoop* _pEngineLoop)
{
	// Call base.
	//BaseEngine::Init(InEngineLoop);

	// Load and apply user game settings
	GetGameUserSettings()->LoadSettings();
	GetGameUserSettings()->ApplySettings();

	//GApplication = FPlatformMisc::CreateApplication();

	//CreateGameWindow();
	
	
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

	auto Definition = new GenericWindowDefinition();

	Definition->WidthDesiredOnScreen = 100;// GSettings.ResX;
	Definition->HeightDesiredOnScreen = 100;// GSettings.ResY;
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



	Definition->HasOSWindowBorder = false;
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
	GApplication->InitializeWindow(*NewWindow, *Definition, /* parent window */NULL, bShowImmediately);
	//FSlateApplication::Get().AddWindow(Window, bShowImmediately);

	// Do not set fullscreen mode here, since it doesn't take 
	// HMDDevice into account. The window mode will be set properly later
	// from SwitchGameWindowToUseGameViewport() method (see ResizeWindow call).

	NewWindow->SetWindowMode(EWindowModeType::Windowed);

	NewWindow->Show();

	//GApplication->Tick();
	// Tick now to force a redraw of the window and ensure correct fullscreen application

	return NewWindow;

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
}
