#pragma once
#include "Object.h"

class IActor;

class Map;

class IActorComponent;

class FActorComponentTickFunc {
public:
    virtual ~FActorComponentTickFunc();

	virtual void run(IActorComponent* _sceneComponent, float _deltaTime) = 0;
};

class IActorComponent : public Object {
public:
	virtual ~IActorComponent();

    //register methods
    virtual void RegisterWithMap(Map* _map);

	virtual void UnregisterWithMap();

	virtual void RegisterWithOwner(IActor* _owner);

	//get environment methods
	virtual IActor* getOwner();

	virtual Map* getWorld();

	//activation status methods
	virtual void Activate();

	virtual void Deactivate();

	virtual void ToggleActive();

	virtual bool isActive();

	//Tick status methods
	virtual void EnableTick();

	virtual void DisableTick();

	//Tick
	virtual void Tick(float _deltaTime, FActorComponentTickFunc* _tickScript) = 0;

private:
	//active status
	bool m_bActive;
	//environment
	IActor* m_owner;
	Map* m_world;
	//tick status flag
	bool m_bNeverTick;
	bool m_bCanTick;
	
};