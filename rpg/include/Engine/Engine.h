#pragma once
#include "GameUserSettings.h"
#include "GameViewportClient.h"

class EngineLoop;

class Engine
{
public:
	Engine();
	~Engine();

	GameUserSettings* GetGameUserSettings();
	void CreateGameWindow();

	void Init(EngineLoop* _pEngineLoop);

private:
	GameViewportClient* GameViewport;
	//GameViewportWindow;
	bool m_bIsInitialized;
};