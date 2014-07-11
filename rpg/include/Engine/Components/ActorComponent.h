#pragma once
#include "Object.h"

class AActor;

class TileMap;

class IActorComponent;

class FActorComponentTickFunc {
public:
    FActorComponentTickFunc();

	FActorComponentTickFunc(IActorComponent* _target);

	void registerWithTarget(IActorComponent* _target);

	void unregisterWithTarget();

	void registerWithLevel(TileMap* _map);

	void unregisterWithLevel();

	virtual ~FActorComponentTickFunc();

	virtual void run(float _deltaTime);

protected:
	IActorComponent* m_target = nullptr;

	TileMap* m_map = nullptr;

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