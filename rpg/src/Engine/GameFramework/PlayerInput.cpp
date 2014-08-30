#include "PlayerInput.h"
#include "InputComponent.h"
#include "Spell.h"
#include "UserSetting.h"


static const std::map<std::tstring, hgeKeyCode_t> keyNameCodeMapping = { 
	{ TEXT("Left Mouse Button"), HGEK_LBUTTON },
	{ TEXT("Right Mouse Button"), HGEK_RBUTTON },
	{ TEXT("Middle Mouse Button"), HGEK_MBUTTON },
	{ TEXT("Backspace"), HGEK_BACKSPACE },
	{ TEXT("Tab"), HGEK_TAB },
	{ TEXT("Enter"), HGEK_ENTER },
	{ TEXT("Shift"), HGEK_SHIFT },
	{ TEXT("Ctrl"), HGEK_CTRL },
	{ TEXT("Alt"), HGEK_ALT },
	{ TEXT("Pause"), HGEK_PAUSE },
	{ TEXT("Caps Lock"), HGEK_CAPSLOCK },
	{ TEXT("Escape"), HGEK_ESCAPE },
	{ TEXT("Space"), HGEK_SPACE },
	{ TEXT("Page Up"), HGEK_PGUP },
	{ TEXT("Page Down"), HGEK_PGDN },
	{ TEXT("End"), HGEK_END },
	{ TEXT("Home"), HGEK_HOME },
	{ TEXT("Left Arrow"), HGEK_LEFT },
	{ TEXT("Up Arrow"), HGEK_UP },
	{ TEXT("Right Arrow"), HGEK_RIGHT },
	{ TEXT("Down Arrow"), HGEK_DOWN },
	{ TEXT("Insert"), HGEK_INSERT },
	{ TEXT("Delete"), HGEK_DELETE },
	{ TEXT("0"), HGEK_0 },
	{ TEXT("1"), HGEK_1 },
	{ TEXT("2"), HGEK_2 },
	{ TEXT("3"), HGEK_3 },
	{ TEXT("4"), HGEK_4 },
	{ TEXT("5"), HGEK_5 },
	{ TEXT("6"), HGEK_6 },
	{ TEXT("7"), HGEK_7 },
	{ TEXT("8"), HGEK_8 },
	{ TEXT("9"), HGEK_9 },
	{ TEXT("A"), HGEK_A },
	{ TEXT("B"), HGEK_B },
	{ TEXT("C"), HGEK_C },
	{ TEXT("D"), HGEK_D },
	{ TEXT("E"), HGEK_E },
	{ TEXT("F"), HGEK_F },
	{ TEXT("G"), HGEK_G },
	{ TEXT("H"), HGEK_H },
	{ TEXT("I"), HGEK_I },
	{ TEXT("J"), HGEK_J },
	{ TEXT("K"), HGEK_K },
	{ TEXT("L"), HGEK_L },
	{ TEXT("M"), HGEK_M },
	{ TEXT("N"), HGEK_N },
	{ TEXT("O"), HGEK_O },
	{ TEXT("P"), HGEK_P },
	{ TEXT("Q"), HGEK_Q },
	{ TEXT("R"), HGEK_R },
	{ TEXT("S"), HGEK_S },
	{ TEXT("T"), HGEK_T },
	{ TEXT("U"), HGEK_U },
	{ TEXT("V"), HGEK_V },
	{ TEXT("W"), HGEK_W },
	{ TEXT("X"), HGEK_X },
	{ TEXT("Y"), HGEK_Y },
	{ TEXT("Z"), HGEK_Z },
	{ TEXT("Left Win"), HGEK_LWIN },
	{ TEXT("Right Win"), HGEK_RWIN },
	{ TEXT("Application"), HGEK_APPS },
	{ TEXT("NumPad 0"), HGEK_NUMPAD0 },
	{ TEXT("NumPad 1"), HGEK_NUMPAD1 },
	{ TEXT("NumPad 2"), HGEK_NUMPAD2 },
	{ TEXT("NumPad 3"), HGEK_NUMPAD3 },
	{ TEXT("NumPad 4"), HGEK_NUMPAD4 },
	{ TEXT("NumPad 5"), HGEK_NUMPAD5 },
	{ TEXT("NumPad 6"), HGEK_NUMPAD6 },
	{ TEXT("NumPad 7"), HGEK_NUMPAD7 },
	{ TEXT("NumPad 8"), HGEK_NUMPAD8 },
	{ TEXT("NumPad 9"), HGEK_NUMPAD9 },
	{ TEXT("Multiply"), HGEK_MULTIPLY },
	{ TEXT("Add"), HGEK_ADD },
	{ TEXT("Subtract"), HGEK_SUBTRACT },
	{ TEXT("Decimal"), HGEK_DECIMAL },
	{ TEXT("Divide"), HGEK_DIVIDE },
	{ TEXT("F1"), HGEK_F1 },
	{ TEXT("F2"), HGEK_F2 },
	{ TEXT("F3"), HGEK_F3 },
	{ TEXT("F4"), HGEK_F4 },
	{ TEXT("F5"), HGEK_F5 },
	{ TEXT("F6"), HGEK_F6 },
	{ TEXT("F7"), HGEK_F7 },
	{ TEXT("F8"), HGEK_F8 },
	{ TEXT("F9"), HGEK_F9 },
	{ TEXT("F10"), HGEK_F10 },
	{ TEXT("F11"), HGEK_F11 },
	{ TEXT("F12"), HGEK_F12 },
	{ TEXT("Num Lock"), HGEK_NUMLOCK },
	{ TEXT("Scroll Lock"), HGEK_SCROLLLOCK },
	{ TEXT("Semicolon"), HGEK_SEMICOLON },
	{ TEXT("Equals"), HGEK_EQUALS },
	{ TEXT("Comma"), HGEK_COMMA },
	{ TEXT("Minus"), HGEK_MINUS },
	{ TEXT("Period"), HGEK_PERIOD },
	{ TEXT("Slash"), HGEK_SLASH },
	{ TEXT("Grave"), HGEK_GRAVE },
	{ TEXT("Left bracket"), HGEK_LBRACKET },
	{ TEXT("Backslash"), HGEK_BACKSLASH },
	{ TEXT("Right bracket"), HGEK_RBRACKET },
	{ TEXT("Apostrophe"), HGEK_APOSTROPHE }
};

/*
std::map<std::tstring, keyMappingUnit> PlayerInput::m_skeyBindingMap;

/ *
void PlayerInput::dispatchMessage() {
	while (!m_messageQueue.empty()) {
		if (m_messageQueue.front().isInGameCommand())
			m_CharacterCommand->addCommand(m_messageQueue.front());
		else
			m_guiCommand->addCommand(m_messageQueue.front());
		m_messageQueue.pop();
	}
}* /

void PlayerInput::translateInput(HGE* _gameSession) {
	for (auto& i : m_skeyBindingMap) {
		if (!_gameSession->Input_GetKeyState(keyNameCodeMapping.at(i.first)))
			continue;
		else {
			for (auto& j : i.second.m_sameCenterKeyBindings) {
				//logic to determine whether the current key combination (j) is pressed
				if (j.m_bShiftModifier && !_gameSession->Input_GetKeyState(HGEK_SHIFT)
					|| !j.m_bShiftModifier && !i.second.m_bIgnoreShift && _gameSession->Input_GetKeyState(HGEK_SHIFT)
					|| j.m_bCtrlModifier && !_gameSession->Input_GetKeyState(HGEK_CTRL)
					|| !j.m_bCtrlModifier && !i.second.m_bIgnoreCtrl && _gameSession->Input_GetKeyState(HGEK_CTRL)
					|| j.m_bAltModifier && !_gameSession->Input_GetKeyState(HGEK_ALT)
					|| !j.m_bAltModifier && !i.second.m_bIgnoreAlt && _gameSession->Input_GetKeyState(HGEK_ALT))
					continue;
				else
					m_messageQueue.push(j.m_bindedCommand);
			}
		}
	}
}

void PlayerInput::readKeyBinding(std::fstream _userKeySetting) {
	std::tstring line;
	if (_userKeySetting.is_open())
		std::getline(_userKeySetting, line);
	std::tstring KeyName;
	std::tstring EventName;
	std::tstring ModifierKey;
	while (_userKeySetting >> KeyName >> EventName) {
		std::getline(_userKeySetting, ModifierKey);
		m_skeyBindingMap[KeyName].m_sameCenterKeyBindings
			.push_back(KeyBinding(keyNameCodeMapping.at(KeyName), ModifierKey.find("Shift") != std::tstring::npos,
			ModifierKey.find("Ctrl") != std::tstring::npos, ModifierKey.find("Alt") != std::tstring::npos, InputCommand(EventName, nullptr)));
	}
	//set ignore flag
	for (auto& i : m_skeyBindingMap) {
		for (auto& j : i.second.m_sameCenterKeyBindings) {
			if (j.m_bShiftModifier)
				i.second.m_bIgnoreShift = false;
			if (j.m_bCtrlModifier)
				i.second.m_bIgnoreCtrl = false;
			if (j.m_bAltModifier)
				i.second.m_bIgnoreAlt = false;
		}
	}
}
*/

PlayerInput::PlayerInput(UserSetting* _userSetting, InputComponent* _targetCharacter) : m_keySetting(_userSetting), m_targetCharacterInputComponent(_targetCharacter) {

}

void PlayerInput::translateInput() {
	HGE* hge = hgeCreate(HGE_VERSION);
	for (auto& i : m_keySetting->getKeyBindingMap()) {
		if (!hge->Input_GetKeyState(keyNameCodeMapping.at(i.first)))
			continue;
		else {
			for (auto& j : i.second.m_sameCenterKeyBindings) {
				//logic to determine whether the current key combination (j) is pressed
				if (j->m_bShiftModifier && !hge->Input_GetKeyState(HGEK_SHIFT)
					|| !j->m_bShiftModifier && !i.second.m_bIgnoreShift && hge->Input_GetKeyState(HGEK_SHIFT)
					|| j->m_bCtrlModifier && !hge->Input_GetKeyState(HGEK_CTRL)
					|| !j->m_bCtrlModifier && !i.second.m_bIgnoreCtrl && hge->Input_GetKeyState(HGEK_CTRL)
					|| j->m_bAltModifier && !hge->Input_GetKeyState(HGEK_ALT)
					|| !j->m_bAltModifier && !i.second.m_bIgnoreAlt && hge->Input_GetKeyState(HGEK_ALT))
					continue;
				else
					m_messageQueue.push(j->m_bindedCommand);
			}
		}
	}
	hge->Release();
}

void PlayerInput::dispatchMessage() {
	while (!m_messageQueue.empty()) {
		m_targetCharacterInputComponent->addCommand(m_messageQueue.front());
		m_messageQueue.pop();
	}
}
