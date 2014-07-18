#include "InputUnit.h"

void InputUnit::dispatchMessage() {

}

void InputUnit::translateInput(HGE* _gameSession) {

}

InputUnit::~InputUnit() {

}

InputUnit::InputUnit() {

}

void InputUnit::setDispatchTarget(InputComponent* _dispatchTarget) {
	if (_dispatchTarget)
		m_dispatchTarget = _dispatchTarget;
}
