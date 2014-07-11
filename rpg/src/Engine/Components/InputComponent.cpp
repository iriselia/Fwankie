#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent() {
	m_bActive = true;
}

InputComponent::InputComponent(AActor* _owner) {
	m_bActive = true;
	m_owner = _owner;
}

void InputComponent::addKeyBinding(hgeKeyCode_t _key, funcPtr _funcPtr) {
	m_keymapping[_key] = _funcPtr;
}

void InputComponent::executeKeyAction(HGE* _gameSession) {
	/*for (auto& i : m_keymapping) {
		if (_gameSession->Input_KeyDown(i.first)) {
			m_owner->(*_funcPtr);
			return;
		}
	}*/
}
