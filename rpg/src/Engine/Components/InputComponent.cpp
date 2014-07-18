#include "InputComponent.h"
#include "Character.h"

InputComponent::InputComponent() {
	m_bActive = true;
}

InputComponent::InputComponent(Character* _owner) {
	m_bActive = true;
	m_pOwner = _owner;
}

void InputComponent::addKeyBinding(hgeKeyCode_t _key, Callback<void()> _delegate) {
	m_movementKeyMapping[_key] = _delegate;
}

void InputComponent::executeKeyAction(HGE* _gameSession) {
	for (auto& i : m_movementKeyMapping) {
		if (_gameSession->Input_KeyDown(i.first))
			i.second.operator()();
	}
}
