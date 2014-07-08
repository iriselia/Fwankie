#pragma once
#include "Actor.h"

class Controller : public IActor {
	public:
	virtual ~Controller();

	virtual void TickActor();
	private:

};