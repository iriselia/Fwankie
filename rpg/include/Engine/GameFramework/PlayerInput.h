#pragma once
#include "InputUnit.h"
#include <fstream>

struct KeyBinding {

	KeyBinding(hgeKeyCode_t _inputKey, bool _shiftModifier, bool _ctrlModifier, bool _altModifier, InputCommand _command)
		: m_pressed_key(_inputKey), m_bShiftModifier(_shiftModifier), m_bCtrlModifier(_ctrlModifier), m_bAltModifier(_altModifier), m_bindedCommand(_command) {}

	//input key related 
	hgeKeyCode_t m_pressed_key;
	bool m_bShiftModifier;
	bool m_bCtrlModifier;
	bool m_bAltModifier;
	//event related
	InputCommand m_bindedCommand;
};

class PlayerInput : public InputUnit {
public:
	PlayerInput() {}

	static void readKeyBinding(std::fstream _userKeySetting) {}

	virtual void translateInput(HGE* _gameSession) {
		for (auto& i : m_keyBindingMap) {
			if (i.m_bShiftModifier && !_gameSession->Input_GetKeyState(HGEK_SHIFT))
				continue;
			if (i.m_bCtrlModifier && !_gameSession->Input_GetKeyState(HGEK_CTRL))
				continue;
			if (i.m_bAltModifier && !_gameSession->Input_GetKeyState(HGEK_ALT))
				continue;
			if (_gameSession->Input_GetKeyState(i.m_pressed_key))
				m_messageQueue.push(i.m_bindedCommand);
		}
	}

	virtual void dispatchMessage() {

	}

private:
	InputComponent* m_CharacterCommand;
	InputComponent* m_guiCommand;
	static std::vector<KeyBinding> m_keyBindingMap;
};