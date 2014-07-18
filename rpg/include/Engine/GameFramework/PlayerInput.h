#pragma once
#include "InputUnit.h"
#include "hge.h"
#include <vector>
#include <fstream>

class SpellInfo;

struct KeyBinding {

	KeyBinding() {}

	KeyBinding(hgeKeyCode_t _inputKey, bool _shiftModifier, bool _ctrlModifier, bool _altModifier, PawnAction _action, SpellInfo* _spell)
		: m_pressed_key(_inputKey), m_bShiftModifier(_shiftModifier), m_bCtrlModifier(_ctrlModifier), m_bAltModifier(_altModifier), m_bindedAction(_action), m_targetSpell(_spell) {}

	//input key related 
	hgeKeyCode_t m_pressed_key;
	bool m_bShiftModifier;
	bool m_bCtrlModifier;
	bool m_bAltModifier;
	//event related
	PawnAction m_bindedAction;
	SpellInfo* m_targetSpell;
};

class PlayerInput : public InputUnit {
public:
	PlayerInput() {}

	static void readKeyBinding(std::fstream _userKeySetting) {}

	virtual void translateInput() {

	}

	virtual void dispatchMessage();

private:
	static std::vector<KeyBinding> m_keyBindingMap;
};