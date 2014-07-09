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
    IActorComponent();

	IActorComponent(AActor* _owner_in, bool _bNeverTick, bool _bCanTick);

	virtual ~IActorComponent();

	void registerWithOwner(AActor* _owner);

	void unregisterWithOwner();

	bool isRegisteredWithOwner();

	AActor* getOwner();

	//activation status methods
	virtual void Activate();

	virtual void Deactivate();

	virtual void ToggleActive();

	virtual bool isActive();

	//Tick status methods
	virtual void EnableTick();

	virtual void DisableTick();

	//Tick
	virtual void Tick(float _deltaTime, FActorComponentTickFunc* _tickScript);

private:
	//active status
	bool m_bActive = false;
	//environment
	AActor* m_owner = nullptr;
	//tick status flag
	bool m_bNeverTick = false;
	bool m_bCanTick = false;
};