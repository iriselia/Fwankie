#pragma once
#include "EngineLoop.h"
#include "GameEngine.h"

int32 EngineLoop::Init()
{
	//TODO: Add Reflection to engine creation.

	// Figure out which UEngine variant to use.
	//UClass* EngineClass = NULL;

	// We're the game.
	GEngine = new GameEngine;
	
	//check(GEngine);

	//GEngine->ParseCommandline();

	//InitTime();

	GEngine->Init(this);

	//GIsRunning = true;

	return 0;
}

void EngineLoop::Tick()
{

}

void EngineLoop::Exit()
{
	delete GEngine;
}

EngineLoop::~EngineLoop()
{

}

EngineLoop::EngineLoop()
{

}
