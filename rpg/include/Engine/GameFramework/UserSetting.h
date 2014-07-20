#pragma once
#include <fstream>
#include <hge.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

struct KeyBinding {

	KeyBinding(hgeKeyCode_t _inputKey, bool _shiftModifier, bool _ctrlModifier, bool _altModifier,
			   std::string _command)
			   : m_centerKey(_inputKey), m_bShiftModifier(_shiftModifier), m_bCtrlModifier(_ctrlModifier), m_bAltModifier(_altModifier), m_bindedCommand(_command) {
	}

	//input key related 
	hgeKeyCode_t m_centerKey;
	bool m_bShiftModifier;
	bool m_bCtrlModifier;
	bool m_bAltModifier;
	//event related
	std::string m_bindedCommand;
};

struct keyMappingUnit {
	bool m_bIgnoreShift = true;
	bool m_bIgnoreCtrl = true;
	bool m_bIgnoreAlt = true;
	std::vector<KeyBinding*> m_sameCenterKeyBindings;
};

class UserSetting {
public:
	UserSetting();

	void setKeyBindingMap(std::string _userSettingFile);

	void modifyKeyBinding(std::string _userSettingFile, KeyBinding* _newKeyBinding, KeyBinding* _oldKeyBinding, HGE* _gameSession);

	std::map<std::string, keyMappingUnit>& getKeyBindingMap();

	~UserSetting() {
		for (auto& i : m_keyBindingMap) {
			for (auto& j : i.second.m_sameCenterKeyBindings) {
				delete j;
				j = nullptr;
			}
		}
	}

private:
	std::map<std::string, keyMappingUnit> m_keyBindingMap;

	bool m_ignoreModifiers;
		
		/*
		= {
		//Movement
		{ "CHARACTER_MOVEUP", HGEK_W }, { "CHARACTER_MOVELEFT", HGEK_A }, { "CHARACTER_MOVEDOWN", HGEK_S }, { "CHARACTER_MOVERIGHT", HGEK_D },
		//Spell
		{ "ACTION_BAR_1", HGEK_1 }, { "ACTION_BAR_2", HGEK_2 }, { "ACTION_BAR_3", HGEK_3 }, { "ACTION_BAR_4", HGEK_4 }, { "ACTION_BAR_5", HGEK_5 },
		{ "ACTION_BAR_6", HGEK_6 }, { "ACTION_BAR_7", HGEK_7 }, { "ACTION_BAR_8", HGEK_8 }, { "ACTION_BAR_9", HGEK_9 }, { "ACTION_BAR_10", HGEK_0 },
		{ "ACTION_BAR_11", HGEK_SLASH }, { "ACTION_BAR_1", HGEK_EQUALS }
	}
	*/
};