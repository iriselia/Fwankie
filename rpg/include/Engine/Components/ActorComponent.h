#pragma once
#include "Object.h"

class AActor;

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

	virtual void RegisterWithOwner(AActor* _owner);

	virtual bool isRegisteredWithWorld();

	//get environment methods
	virtual AActor* getOwner();

	virtual Map* getMap();

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
	AActor* m_owner;
	Map* m_map;
	//tick status flag
	bool m_bNeverTick;
	bool m_bCanTick;
	
};