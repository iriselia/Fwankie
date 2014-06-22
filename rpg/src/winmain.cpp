#include <stdlib.h>
#include <cassert>

#ifdef _DEBUG
#include <vld.h> 
#endif

#include "windows.h"
#include "MyGUI_Exception.h"
//#include "guichan.hpp"
#include "RPG.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Create out debug console window
	// and redirect the iostreams
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
//#define _DEBUGGAME
#ifdef _DEBUGGAME
		RPG::Debug_Init();
		RPG::Debug_Run();
		RPG::Debug_Halt();
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

	// Catch all Guichan exceptions.
	/*
	catch (gcn::Exception e)
	{
		MessageBox(NULL,
			e.getMessage().c_str(),
			"Guichan exception",
			MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return 1;
	}

	// Catch all Std exceptions.
	catch (std::exception e)
	{
		MessageBox(NULL,
			e.what(),
			"Std exception",
			MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return 1;
	}
	*/
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//assert(!_CrtDumpMemoryLeaks());
	return 0;
}
