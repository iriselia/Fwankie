#pragma once
#include "Actor.h"

class Pawn : public IActor {
public:
	Pawn();

	//collision
	virtual bool CollideWith(Pawn* _otherPawn);

	virtual Pawn* Collide();

	//Mouse Touching
	virtual bool isMouseTouchingMe();

	//enable/disable control
	virtual void enableControl(class Controller* _controller);

	virtual void disableControl(Controller* _controller);


private:

    struct PawnAttributes* m_attributes;

	//statusType

	//Controlling logic
	IActor* controller;
};