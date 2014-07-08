#pragma once
#include "Actor.h"

class Controller : public Actor {
	public:
	virtual ~Controller();

	virtual void TickActor();
	private:

};