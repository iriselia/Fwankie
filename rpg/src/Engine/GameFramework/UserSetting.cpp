#include "UserSetting.h"

static const std::map<std::string, hgeKeyCode_t> keyNameCodeMapping = {
	{ "Left Mouse Button", HGEK_LBUTTON }, { "Right Mouse Button", HGEK_RBUTTON }, { "Middle Mouse Button", HGEK_MBUTTON }, { "Backspace", HGEK_BACKSPACE },
	{ "Tab", HGEK_TAB }, { "Enter", HGEK_ENTER }, { "Shift", HGEK_SHIFT }, { "Ctrl", HGEK_CTRL }, { "Alt", HGEK_ALT }, { "Pause", HGEK_PAUSE }, { "Caps Lock", HGEK_CAPSLOCK },
	{ "Escape", HGEK_ESCAPE }, { "Space", HGEK_SPACE }, { "Page Up", HGEK_PGUP }, { "Page Down", HGEK_PGDN }, { "End", HGEK_END }, { "Home", HGEK_HOME },
	{ "Left Arrow", HGEK_LEFT }, { "Up Arrow", HGEK_UP }, { "Right Arrow", HGEK_RIGHT }, { "Down Arrow", HGEK_DOWN }, { "Insert", HGEK_INSERT }, { "Delete", HGEK_DELETE },
	{ "0", HGEK_0 }, { "1", HGEK_1 }, { "2", HGEK_2 }, { "3", HGEK_3 }, { "4", HGEK_4 }, { "5", HGEK_5 }, { "6", HGEK_6 }, { "7", HGEK_7 }, { "8", HGEK_8 }, { "9", HGEK_9 },
	{ "A", HGEK_A }, { "B", HGEK_B }, { "C", HGEK_C }, { "D", HGEK_D }, { "E", HGEK_E }, { "F", HGEK_F }, { "G", HGEK_G }, { "H", HGEK_H }, { "I", HGEK_I }, { "J", HGEK_J },
	{ "K", HGEK_K }, { "L", HGEK_L }, { "M", HGEK_M }, { "N", HGEK_N }, { "O", HGEK_O }, { "P", HGEK_P }, { "Q", HGEK_Q }, { "R", HGEK_R }, { "S", HGEK_S }, { "T", HGEK_T },
	{ "U", HGEK_U }, { "V", HGEK_V }, { "W", HGEK_W }, { "X", HGEK_X }, { "Y", HGEK_Y }, { "Z", HGEK_Z }, { "Left Win", HGEK_LWIN }, { "Right Win", HGEK_RWIN }, { "Application", HGEK_APPS },
	{ "NumPad 0", HGEK_NUMPAD0 }, { "NumPad 1", HGEK_NUMPAD1 }, { "NumPad 2", HGEK_NUMPAD2 }, { "NumPad 3", HGEK_NUMPAD3 }, { "NumPad 4", HGEK_NUMPAD4 }, { "NumPad 5", HGEK_NUMPAD5 },
	{ "NumPad 6", HGEK_NUMPAD6 }, { "NumPad 7", HGEK_NUMPAD7 }, { "NumPad 8", HGEK_NUMPAD8 }, { "NumPad 9", HGEK_NUMPAD9 }, { "Multiply", HGEK_MULTIPLY }, { "Add", HGEK_ADD },
	{ "Subtract", HGEK_SUBTRACT }, { "Decimal", HGEK_DECIMAL }, { "Divide", HGEK_DIVIDE }, { "F1", HGEK_F1 }, { "F2", HGEK_F2 }, { "F3", HGEK_F3 }, { "F4", HGEK_F4 }, { "F5", HGEK_F5 },
	{ "F6", HGEK_F6 }, { "F7", HGEK_F7 }, { "F8", HGEK_F8 }, { "F9", HGEK_F9 }, { "F10", HGEK_F10 }, { "F11", HGEK_F11 }, { "F12", HGEK_F12 }, { "Num Lock", HGEK_NUMLOCK }, { "Scroll Lock", HGEK_SCROLLLOCK },
	{ "Semicolon", HGEK_SEMICOLON }, { "Equals", HGEK_EQUALS }, { "Comma", HGEK_COMMA }, { "Minus", HGEK_MINUS }, { "Period", HGEK_PERIOD }, { "Slash", HGEK_SLASH }, { "Grave", HGEK_GRAVE },
	{ "Left bracket", HGEK_LBRACKET }, { "Backslash", HGEK_BACKSLASH }, { "Right bracket", HGEK_RBRACKET }, { "Apostrophe", HGEK_APOSTROPHE }
};

std::map<std::string, keyMappingUnit>& UserSetting::getKeyBindingMap() {
	return m_keyBindingMap;
}

void UserSetting::setKeyBindingMap(std::string _userSettingFile) {
	std::fstream userSettingFile(_userSettingFile.c_str());
	std::string line;
	m_ignoreModifiers = false;
	if (userSettingFile.is_open())
		std::getline(userSettingFile, line);
	else
		//error opening file
		return;
	if (line.find("true") != std::string::npos)
		m_ignoreModifiers = true;
	std::string KeyName;
	std::string EventName;
	std::string ModifierKey;
	std::getline(userSettingFile, line);
	std::getline(userSettingFile, line);
	while (userSettingFile >> KeyName >> EventName) {
		std::getline(userSettingFile, ModifierKey);
		m_keyBindingMap[KeyName].m_sameCenterKeyBindings
			.push_back(new KeyBinding(keyNameCodeMapping.at(KeyName), ModifierKey.find("Shift") != std::string::npos,
			ModifierKey.find("Ctrl") != std::string::npos, ModifierKey.find("Alt") != std::string::npos, EventName));
	}
	userSettingFile.close();
	if (m_ignoreModifiers)
		//set ignore flag
		for (auto& i : m_keyBindingMap) {
			for (auto& j : i.second.m_sameCenterKeyBindings) {
				if (j->m_bShiftModifier)
					i.second.m_bIgnoreShift = false;
				if (j->m_bCtrlModifier)
					i.second.m_bIgnoreCtrl = false;
				if (j->m_bAltModifier)
					i.second.m_bIgnoreAlt = false;
			}
		}
	else {
		for (auto& i : m_keyBindingMap) {
			i.second.m_bIgnoreShift = false;
			i.second.m_bIgnoreCtrl = false;
			i.second.m_bIgnoreAlt = false;
		}
	}
}

UserSetting::UserSetting() {

}

void UserSetting::modifyKeyBinding(std::string _userSettingFile, KeyBinding* _newKeyBinding, KeyBinding* _oldKeyBinding, HGE* _gameSession) {
	//change keyBindingMap
	//delete old key binding
	keyMappingUnit* keyMappingUnitPtr = &(m_keyBindingMap[_gameSession->Input_GetKeyName(_oldKeyBinding->m_centerKey)]);
	std::vector<KeyBinding*>* sameCenterKeyBindingsPtr = &(keyMappingUnitPtr->m_sameCenterKeyBindings);
	sameCenterKeyBindingsPtr->erase(std::find(sameCenterKeyBindingsPtr->begin(), sameCenterKeyBindingsPtr->end(), _oldKeyBinding));
	//renew ignore flag
	if (m_ignoreModifiers) {
		if (_oldKeyBinding->m_bShiftModifier) {
			keyMappingUnitPtr->m_bIgnoreShift = true;
			for (auto i = sameCenterKeyBindingsPtr->begin(); i != sameCenterKeyBindingsPtr->end(); i++) {
				if ((*i)->m_bShiftModifier) {
					keyMappingUnitPtr->m_bIgnoreShift = false;
					break;
				}
			}
		}
		if (_oldKeyBinding->m_bCtrlModifier) {
			keyMappingUnitPtr->m_bIgnoreCtrl = true;
			for (auto i = sameCenterKeyBindingsPtr->begin(); i != sameCenterKeyBindingsPtr->end(); i++) {
				if ((*i)->m_bCtrlModifier) {
					keyMappingUnitPtr->m_bIgnoreCtrl = false;
					break;
				}
			}
		}
		if (_oldKeyBinding->m_bAltModifier) {
			keyMappingUnitPtr->m_bIgnoreAlt = true;
			for (auto i = sameCenterKeyBindingsPtr->begin(); i != sameCenterKeyBindingsPtr->end(); i++) {
				if ((*i)->m_bAltModifier) {
					keyMappingUnitPtr->m_bIgnoreAlt = false;
					break;
				}
			}
		}
	}
	//TODO finish implementation
}
