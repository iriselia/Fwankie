#include "InputComponent.h"
#include "Character.h"

InputComponent::InputComponent() {
	m_bActive = true;
}

InputComponent::InputComponent(Character* _owner) {
	m_bActive = true;
	m_pOwner = _owner;
}

void InputComponent::addKeyBinding(std::tstring _command, Callback<void()> _delegate) {
	m_movementKeyMapping[_command] = _delegate;
}

void InputComponent::executeAction() {
	while (!m_commandQueue.empty()) {
		if (m_movementKeyMapping.find(m_commandQueue.front()) != m_movementKeyMapping.end())
			m_movementKeyMapping[m_commandQueue.front()].operator()();
		m_commandQueue.pop();
	}
}
