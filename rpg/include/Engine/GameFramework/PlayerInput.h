#pragma once
#include "InputUnit.h"
#include <fstream>
#include <string>
#include <map>

class UserSetting;

class PlayerInput : public InputUnit {
public:
	PlayerInput(UserSetting* _userSetting, InputComponent* _targetCharacter);

	virtual void translateInput();

	virtual void dispatchMessage();

private:
	InputComponent* m_targetCharacterInputComponent;
	UserSetting* m_keySetting;

};