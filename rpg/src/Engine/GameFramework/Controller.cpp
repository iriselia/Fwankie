#include "Controller.h"
#include "Character.h"

bool Controller::stopCasting() {
	return false;
}

bool Controller::abortMovement() {
	return false;
}

bool Controller::movetoTransform(float x, float y) {
	return false;
}

bool Controller::isControllingCharacter() {
	return dynamic_cast<Character*>(m_controlTarget) != nullptr;
}

void Controller::unpossess() {
	if (m_controlTarget) {
		delete m_controlTarget;
	}
	m_controlTarget = nullptr;
}

void Controller::possess(Pawn* _newTarget) {
	m_controlTarget = _newTarget;
}

void Controller::TickActor() {

}

Controller::~Controller() {

}

Controller::Controller() {

}

