#include <stdlib.h>
#include <cassert>

#ifdef _DEBUG
#include <vld.h> 
#endif

#include "windows.h"
#include "MyGUI_Exception.h"
#include "RPG.h"
#include "RPG_Debug.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
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

	try
	{
#define _DEBUGGAME
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
