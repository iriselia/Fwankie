#include "SceneComponent.h"

void FSceneComponentTickFunc::run(float _deltaTime) {
	ISceneComponent* target = dynamic_cast<ISceneComponent*>(m_target);
	if (target) {
		if (m_bResetX) target->x = m_xReset;
		if (m_bResetY) target->y = m_yReset;
    }
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

void ISceneComponent::Tick(float _deltaTime) {
	FSceneComponentTickFunc* tickFunc = dynamic_cast<FSceneComponentTickFunc*>(m_tickFunc);
	if (tickFunc)
		tickFunc->run(0);
}

ISceneComponent::~ISceneComponent() {

}
