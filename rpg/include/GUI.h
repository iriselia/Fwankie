#pragma once
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
