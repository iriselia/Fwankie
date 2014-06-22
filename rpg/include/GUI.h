#ifndef GUI_h__
#define GUI_h__

#include "BaseManager.h"

class GUI :
		public base::BaseManager
	{
	public:
		virtual void createScene();
		virtual void destroyScene();

	private:
		virtual void setupResources();
	};

#endif // GUI_h__
