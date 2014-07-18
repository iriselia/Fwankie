#pragma once
#include "Object.h"
#include "hge.h"

class InputComponent;

enum PawnAction {
	//game related
	INPUT_MOVE_UP,
	INPUT_MOVE_DOWN,
	INPUT_MOVE_LEFT,
	INPUT_MOVE_RIGHT,
	INPUT_CAST_SPELL,
	INPUT_INTERACTE_WITH,
	//gui related
	INPUT_OPEN_MAP,
	INPUT_OPEN_BAG,
	INPUT_OPEN_OPTIONS,
	INPUT_OPEN_CHARACTER_MENU
};

class InputUnit : public Object {
public:
	InputUnit();

	virtual ~InputUnit();

	virtual void translateInput(HGE* _gameSession);

	virtual void dispatchMessage();

	void setDispatchTarget(InputComponent* _dispatchTarget);

protected:
	InputComponent* m_dispatchTarget = nullptr;
	PawnAction m_action;
};