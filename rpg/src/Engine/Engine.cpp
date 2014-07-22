#include "Core.h"
#include "Engine.h"

Engine* GEngine = NULL;

Engine::~Engine()
{

}

Engine::Engine()
{

}

GameUserSettings* Engine::GetGameUserSettings()
{
	return NULL;
}

void Engine::Init(EngineLoop* _pEngineLoop)
{
	// Call base.
	//BaseEngine::Init(InEngineLoop);

	// Load and apply user game settings
	GetGameUserSettings()->LoadSettings();
	GetGameUserSettings()->ApplySettings();

	// Creates the initial world context. For GameEngine, this should be the only WorldContext that ever gets created.
	//FWorldContext &InitialWorldContext = CreateNewWorldContext(EWorldType::Game);

	// Initialize the viewport client.
	GameViewportClient* ViewportClient = NULL;
	ViewportClient = new GameViewportClient();
	//ViewportClient->SetReferenceToWorldContext(InitialWorldContext);
	GameViewport = ViewportClient;
	// 			InitialWorldContext.GameViewport = ViewportClient;


	// Attach the viewport client to a new viewport.
	if (ViewportClient)
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
