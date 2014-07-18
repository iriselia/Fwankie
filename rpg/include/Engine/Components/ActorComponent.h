#pragma once
#include "Object.h"

class AActor;

class TileMap;

class IActorComponent;

struct FActorComponentTickFunc {

	FActorComponentTickFunc();

	FActorComponentTickFunc(IActorComponent* _target);

	void registerWithTarget(IActorComponent* _target);

	void unregisterWithTarget();

	void RegisterWithTileMap(TileMap* _map);

	void unregisterWithLevel();

	virtual ~FActorComponentTickFunc();

	virtual void run(float _deltaTime);

	IActorComponent* m_target;
	TileMap* m_map;

};

class IActorComponent : public Object {
public:
    IActorComponent();

	IActorComponent(AActor* _owner_in, bool _bNeverTick, bool _bCanTick);

	virtual ~IActorComponent();

	//customize component register behaviors here.
	virtual void OnRegister();

	//register with owner
	void RegisterTickFuncWithTileMap(TileMap* _pTileMap);

	void unregisterWithOwner();

	bool isRegisteredWithOwner();

	//register a tickFunc
	void registerTickFunc(FActorComponentTickFunc _tickFunc);

	void unregisterTickFunc();

	bool isRegistered();
	void SetRegistered(bool _isRegistered);

	AActor* getOwner();
	void SetOwner(AActor* _pOwner);

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

protected:
	//active status
	bool m_bActive : 1;
	bool m_bRegistered : 1;
	//environment
	AActor* m_pOwner = nullptr;
	//tick status flag
	bool m_bNeverTick : 1;
	bool m_bCanTick : 1;
	//tick Func
	FActorComponentTickFunc m_tickFunc = nullptr;
};
