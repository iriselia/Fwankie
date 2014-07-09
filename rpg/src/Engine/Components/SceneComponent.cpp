#include "SceneComponent.h"

void FSceneComponentTickFunc::run(ISceneComponent* _sceneComponent, float _deltaTime) {
	if (m_bResetX) _sceneComponent->x = m_xReset;
	if (m_bResetY) _sceneComponent->y = m_yReset;
}

ISceneComponent::ISceneComponent() {

}

ISceneComponent::ISceneComponent(float _x_in, float _y_in) : x(_x_in), y(_y_in) {

}

float ISceneComponent::getX() {
	return x;
}

float ISceneComponent::getY() {
	return y;
}

void ISceneComponent::setX(float _x_in) {
	x = _x_in;
}

void ISceneComponent::setY(float _y_in) {
	y = _y_in;
}

void ISceneComponent::Tick(float _deltaTime, FSceneComponentTickFunc* _tickScript) {

}

ISceneComponent::~ISceneComponent() {

}
