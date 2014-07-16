#include "SceneComponent.h"

ISceneComponent::ISceneComponent() {
	x = 0;
	y = 0;
}

void FSceneComponentTickFunc::run(float _deltaTime) {

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
	FSceneComponentTickFunc* tickFunc = dynamic_cast<FSceneComponentTickFunc*>(&m_tickFunc);
	if (tickFunc)
		tickFunc->run(0);
}

ISceneComponent::~ISceneComponent() {

}
