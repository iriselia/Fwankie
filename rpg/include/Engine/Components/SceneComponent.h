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

	float getX();

	float getY();

	void setX(float _x_in);

	void setY(float _y_in);

private:
    friend struct FSceneComponentTickFunc;

	//Transform data
	float x;
	float y;
};