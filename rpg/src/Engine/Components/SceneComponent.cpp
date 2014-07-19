#include "SceneComponent.h"

ISceneComponent::ISceneComponent() {
	m_pos = Vector2D::ZeroVector;
	x_DEPRECATED = 0;
	y_DEPRECATED = 0;
}

void FSceneComponentTickFunc::run(float _deltaTime) {

}

float ISceneComponent::getX_DEPRECATED() {
	return x_DEPRECATED;
}

float ISceneComponent::getY_DEPRECATED() {
	return y_DEPRECATED;
}

void ISceneComponent::setX_DEPRECATED(float _x_in) {
	x_DEPRECATED = _x_in;
}

void ISceneComponent::setY_DEPRECATED(float _y_in) {
	y_DEPRECATED = _y_in;
}

void ISceneComponent::Tick(float _deltaTime) {
	FSceneComponentTickFunc* tickFunc = dynamic_cast<FSceneComponentTickFunc*>(&m_tickFunc);
	if (tickFunc)
		tickFunc->run(0);
}

ISceneComponent::~ISceneComponent() {

}

void ISceneComponent::setPosition(Vector2D _newPosition)
{
	assert(_newPosition > Vector2D::ZeroVector);
	m_pos = _newPosition;
}
