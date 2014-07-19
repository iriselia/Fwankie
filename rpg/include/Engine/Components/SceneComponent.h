#pragma once
#include "ActorComponent.h"
#include <vector>

class ISceneComponent;

struct FSceneComponentTickFunc : FActorComponentTickFunc {
public:
    //default functor, this functor will tick SceneComponent according to its current status
    FSceneComponentTickFunc();

    virtual void run(float _deltaTime);
};

class ISceneComponent : public IActorComponent {
public:
    //default constructor
    ISceneComponent();

	//customize with initial position
	ISceneComponent(float _x_in, float _y_in);

	virtual ~ISceneComponent();

	virtual void Tick(float _deltaTime) override;

	float getX_DEPRECATED();

	float getY_DEPRECATED();

	Vector2D getPosition();
	void setPosition(Vector2D _newPosition);

	void setX_DEPRECATED(float _x_in);

	void setY_DEPRECATED(float _y_in);

protected:


	//Transform data
	float x_DEPRECATED;
	float y_DEPRECATED;
	Vector2D m_pos;

private:
	friend struct FSceneComponentTickFunc;
};