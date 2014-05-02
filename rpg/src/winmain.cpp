#include "windows.h"
//#include "guichan.hpp"
#include "RPG.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Create out debug console window
	// and redirect the iostreams
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	try
	{
		RPG::init();
		RPG::run();
		RPG::halt();
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
	*/
	// Catch all Std exceptions.
	catch (std::exception e)
	{
		MessageBox(NULL,
			e.what(),
			"Std exception",
			MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return 1;
	}
	return 0;
}
