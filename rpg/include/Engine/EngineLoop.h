#pragma once
#include "Platform.h"
#include "GameEngine.h"
//#include "GenericApplication.h"

extern GameEngine* GEngine;
//extern GenericApplication* GApplication;

class EngineLoop
{
public:
	EngineLoop();
	~EngineLoop();

	int32 Init();

	void Tick();

	void Exit();

private:

};
