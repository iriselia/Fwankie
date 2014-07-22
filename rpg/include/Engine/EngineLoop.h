#pragma once
#include "Platform.h"
#include "Engine.h"

extern Engine* GEngine;

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
