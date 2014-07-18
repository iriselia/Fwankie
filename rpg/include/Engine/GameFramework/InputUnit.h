#pragma once
#include "Object.h"
#include "hge.h"
#include <queue>

class InputComponent;

class SpellInfo;

enum InputType {
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

struct InputCommand {
	InputCommand(InputType _type, SpellInfo* _spell) : type(_type), spell(_spell) {}
	InputType type;
	SpellInfo* spell = nullptr;
};

class InputUnit : public Object {
public:
	InputUnit();

	virtual ~InputUnit();

	virtual void translateInput(HGE* _gameSession);

	virtual void dispatchMessage();

protected:
	std::queue<InputCommand> m_messageQueue;
};