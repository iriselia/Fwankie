#pragma once
#include "Object.h"

class AActor;

class Map;

class IActorComponent;

class FActorComponentTickFunc {
public:
    virtual ~FActorComponentTickFunc();

	virtual void run(float _deltaTime) = 0;

protected:
	IActorComponent* m_target;

};

class IActorComponent : public Object {
public:
    IActorComponent();

	IActorComponent(AActor* _owner_in, bool _bNeverTick, bool _bCanTick);

	virtual ~IActorComponent();

	//register with owner
	void registerWithOwner(AActor* _owner);

	void unregisterWithOwner();

	bool isRegisteredWithOwner();

	//register a tickFunc
	void registerTickFunc(FActorComponentTickFunc* _tickFunc);

	void unregisterTickFunc();

	AActor* getOwner();

	//activation status methods
	virtual void Activate();

	virtual void Deactivate();

	virtual void ToggleActive();

	bool isActive();

	//Tick status methods
	virtual void EnableTick();

	virtual void DisableTick();

	bool canTick();

	//Tick
	virtual void Tick(float _deltaTime);

private:
	//active status
	bool m_bActive = false;
	//environment
	AActor* m_owner = nullptr;
	//tick status flag
	bool m_bNeverTick = false;
	bool m_bCanTick = false;

protected:
	//tick Func
	FActorComponentTickFunc* m_tickFunc = nullptr;
};