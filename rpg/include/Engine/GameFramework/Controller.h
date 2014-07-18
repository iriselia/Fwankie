#pragma once
#include "Actor.h"

class Pawn;

class Character;

class Controller : public AActor {
public:
	Controller();

	virtual ~Controller();

	virtual void TickActor();

	void possess(Pawn* _newTarget);

	void unpossess();

	bool isControllingCharacter();

	bool movetoTransform(float x, float y);

	bool abortMovement();

	bool stopCasting();

protected:
	Pawn* m_controlTarget = nullptr;
};