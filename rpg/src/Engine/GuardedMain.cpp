#include <windows.h>
#include "EngineLoop.h"
#include "Core.h"


/** The global EngineLoop instance */
EngineLoop	GEngineLoop;

int32 EngineInit(const TCHAR* SplashName)
{
	return GEngineLoop.Init();
}

void EngineTick(void)
{
	//if (GViewProvider->IsVisible() == true)
	GEngineLoop.Tick();
}

void EngineExit(void)
{
	// Make sure this is set
	GIsRequestingExit = true;
	GEngineLoop.Exit();
}

int32 GuardedMain(const TCHAR* CmdLine, HINSTANCE hInInstance, HINSTANCE hPrevInstance, int32 nCmdShow)
{
	// make sure GEngineLoop::Exit() is always called.
	struct EngineLoopCleanupGuard
	{
		~EngineLoopCleanupGuard()
		{
			EngineExit();
		}
	} CleanupGuard;

	// Game without wxWindows.
	int32 ErrorLevel = EngineInit(TEXT("PC/Splash.bmp"));
	while (!GIsRequestingExit)
	{
		EngineTick();
	}

	return ErrorLevel;
}