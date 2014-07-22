
#ifdef _DEBUG
#include <vld.h> 
#endif

#include <windows.h>
#include "EngineLoop.h"
#include "RPG.h"
#include "RPG_Debug.h"
#include "MyGUI_Exception.h"

#define USE_HGE_MAIN

extern int32 GuardedMain(const TCHAR* CmdLine, HINSTANCE hInInstance, HINSTANCE hPrevInstance, int32 nCmdShow);

// http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
// The following line is to favor the high performance NVIDIA GPU if there are multiple GPUs
// Has to be .exe module to be correctly detected.
extern "C" { _declspec(dllexport) uint32 NvOptimusEnablement = 0x00000001; }

/**
* Maintain a named mutex to detect whether we are the first instance of this game
*/
HANDLE GNamedMutex = NULL;
bool GIsFirstInstance = true;

/** Whether we should pause before exiting. used by UCC */
bool		GShouldPauseBeforeExit;


void ReleaseNamedMutex(void)
{
	if (GNamedMutex)
	{
		ReleaseMutex(GNamedMutex);
		GNamedMutex = NULL;
	}
}

bool MakeNamedMutex(const TCHAR* CmdLine)
{
	bool bIsFirstInstance = false;

	TCHAR MutexName[MAX_SPRINTF] = TEXT("RPG");

	GNamedMutex = CreateMutex(NULL, true, MutexName);

	if (GNamedMutex	&& GetLastError() != ERROR_ALREADY_EXISTS)
	{
		// We're the first instance!
		bIsFirstInstance = true;
	}
	else
	{
		// Still need to release it in this case, because it gave us a valid copy
		ReleaseNamedMutex();
		// There is already another instance of the game running.
		bIsFirstInstance = false;
	}

	return(bIsFirstInstance);
}

/**
* Setup the common debug settings
*/
void SetupWindowsDebugConsole(void)
{
#ifdef _DEBUG
	// Create our debug console window
	// redirect the iostreams
	// and enable mouse scrolling
	AllocConsole();
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode & ~ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

#endif
}

#ifdef USE_HGE_MAIN

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// Create our debug console window
	// redirect the iostreams
	// and enable mouse scrolling
	AllocConsole();
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode & ~ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

#define _DEBUGGAME

	try
	{
#ifdef _DEBUGGAME
		RPG_Debug::init();
		RPG_Debug::run();
		RPG_Debug::halt();
#else
		RPG::init();
		RPG::run();
		RPG::halt();
#endif


	}
	catch (MyGUI::Exception& _e)
	{
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
		MessageBoxA(NULL, _e.getFullDescription().c_str(), "An exception has occurred", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occurred" << " : " << _e.getFullDescription().c_str();
#endif
		//throw;
	}

	//Use vld instead
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//assert(!_CrtDumpMemoryLeaks());
	return 0;
}

#endif

#ifndef USE_HGE_MAIN

int32 WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// Setup Windows debug settings
	SetupWindowsDebugConsole();

	int32 ErrorLevel = 0;
	// TODO: Figure out why they kept a global handle
	//hInstance = hInInstance;
	const TCHAR* CmdLine = GetCommandLine();

	GIsFirstInstance = MakeNamedMutex(CmdLine);

	// Run the guarded code.
	ErrorLevel = GuardedMain(CmdLine, hInInstance, hPrevInstance, nCmdShow);

	// Final shut down.
	//EngineLoop::AppExit();

	ReleaseNamedMutex();

	// pause if we should
	if (GShouldPauseBeforeExit)
	{
		Sleep(INFINITE);
	}

	return ErrorLevel;
}
#endif