#pragma once
#include "ActorComponent.h"
#include <vector>

class ISceneComponent;

class FSceneComponentTickFunc : FActorComponentTickFunc {
public:
    //default script, this script will update SceneComponent according to its current status
    FSceneComponentTickFunc();

	//customized script, will alter SceneComponent's movement status
	FSceneComponentTickFunc(bool _ResetX_in, bool _ResetY_in, float _xReset_in, float _yReset_in) :
		m_bResetX(_ResetX_in), m_bResetY(_ResetY_in), m_xReset(_xReset_in), m_yReset(_yReset_in) {}

    virtual void run(ISceneComponent* _sceneComponent, float _deltaTime);

private:
    bool m_bResetX = false;
	bool m_bResetY = false;
	float m_xReset = 0;
	float m_yReset = 0;
};

class ISceneComponent : public IActorComponent {
public:
	virtual ~ISceneComponent();

	virtual void Tick(float _deltaTime, FSceneComponentTickFunc* _tickScript);

protected:
	//default constructor
	ISceneComponent();

	//customize with initial position
	ISceneComponent(float _x_in, float _y_in) : x(_x_in), y(_y_in) {}

private:
    friend class FSceneComponentTickFunc;

	//Transform data
	float x;
	float y;
};