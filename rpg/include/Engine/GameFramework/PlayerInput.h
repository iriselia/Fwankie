#pragma once
#include "InputUnit.h"
#include <fstream>
#include <string>
#include <map>

struct KeyBinding {

	KeyBinding(hgeKeyCode_t _inputKey, bool _shiftModifier, bool _ctrlModifier, bool _altModifier, 
			   InputCommand _command)
		: m_centerKey(_inputKey), m_bShiftModifier(_shiftModifier), m_bCtrlModifier(_ctrlModifier), m_bAltModifier(_altModifier), m_bindedCommand(_command) {}

	//input key related 
	hgeKeyCode_t m_centerKey;
	bool m_bShiftModifier;
	bool m_bCtrlModifier;
	bool m_bAltModifier;
	//event related
	InputCommand m_bindedCommand;
};


struct keyMappingUnit {
	bool m_bIgnoreShift = true;
	bool m_bIgnoreCtrl = true;
	bool m_bIgnoreAlt = true;
	std::vector<KeyBinding> m_sameCenterkeyBindings;
};

class PlayerInput : public InputUnit {
public:
	PlayerInput() {}

	static void readKeyBinding(std::fstream _userKeySetting);

	static void modifiyKeyBinding(std::fstream _userKeySetting) {}

	virtual void translateInput(HGE* _gameSession);

	virtual void dispatchMessage();

private:
	InputComponent* m_CharacterCommand;
	InputComponent* m_guiCommand;
	static std::map<std::string, keyMappingUnit> m_skeyBindingMap;
};