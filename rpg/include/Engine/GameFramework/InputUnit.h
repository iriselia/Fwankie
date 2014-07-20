#pragma once
#include "Object.h"
#include "hge.h"
#include <queue>
#include <string>


class InputComponent;

/*
class SpellInfo;

struct InputCommand {
	InputCommand(std::string _type, SpellInfo* _spell) : type(_type), spell(_spell) {}

	bool isInGameCommand() {
		return type[0] == 'C';
	}

	bool operator==(const InputCommand& other) {
		return this->type == other.type && this->spell == other.spell;
	}

	bool operator!=(const InputCommand& other) {
		return this->type != other.type || this->spell != other.spell;
	}

	std::string type;
	SpellInfo* spell = nullptr;
};
*/

class InputUnit : public Object {
public:
	InputUnit();

	virtual ~InputUnit();

	virtual void translateInput();

	virtual void dispatchMessage();

protected:
	std::queue<std::string> m_messageQueue;
};