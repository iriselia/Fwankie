#pragma once

class IActor;

class IWorld;

class IActorComponentTickFunction;

class IActorComponent {
public:
    //register methods
    virtual void RegisterWithWorld(IWorld* world) = 0;

	virtual void UnregisterWithWorld() = 0;

	virtual void RegisterWithOwner(IActor* owner) = 0;

	//get environment methods
	virtual IActor* getOwner() = 0;

	virtual IWorld* getWorld() = 0;

	//activation status methods
	virtual void Activate() = 0;

	virtual void Deactivate() = 0;

	virtual void ToggleActive() = 0;

	virtual bool isActive() = 0;

	//Dirty flag
	virtual void MarkTransfromStateDirty() = 0;

	virtual void MarkTransfromStateClear() = 0;

	virtual void MarkRenderStateDirty() = 0;

	virtual void MarkRenderStateClear() = 0;

	virtual void MarkPhysicsStateDirty() = 0;

	virtual void MarkPhysicsStateClear() = 0;

	virtual void Tick(float deltaTime, IActorComponentTickFunction* tickFunc) = 0;

private:
    //register
    bool m_bRegisteredWithOwner;
	bool m_bRegisteredWithWorld;
	//active status
	bool m_bActive;
	//whether render, physics is needed
	bool m_bRender;
	bool m_bPhysics;
	//environment
	IActor* m_owner;
	IWorld* m_world;
	//tick status
	bool m_bNeverTick;
	//Dirty Flag
	bool m_bTransformStateDirty;
	bool m_bRenderStateDirty;
	bool m_bPhysicsStateDirty;
};