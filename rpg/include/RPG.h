

//#include <guichan.hpp>
//#include <guichan/hge.hpp>
#include <string>

namespace RPG {

	bool FrameFunc();
	bool RenderFunc();
	void init();
	void run();
	void halt();

	/*
	Debug Mode.
	*/
	bool Debug_FrameFunc();
	bool Debug_RenderFunc();
	void Debug_Init();
	void Debug_Run();
	void Debug_Halt();

	/*
	Miscellaneous
	*/
	bool MenuFrameFunc();
	bool MenuRenderFunc();
}