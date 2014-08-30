#pragma once
#include "Core.h"
#include "GameUserSettings.h"
//#include "GameViewportClient.h"

class EngineLoop;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	GameUserSettings* GetGameUserSettings();
	std::shared_ptr<class GenericWindow> CreateGameWindow();

	void Init(EngineLoop* _pEngineLoop);

private:
	//GameViewportClient* GameViewport;
	//GameViewportWindow;
	bool m_bIsInitialized;
};

