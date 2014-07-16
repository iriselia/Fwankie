#include "ActorComponent.h"
#include "Actor.h"
#include "TileMap.h"

FActorComponentTickFunc::~FActorComponentTickFunc() {

}

FActorComponentTickFunc::FActorComponentTickFunc(IActorComponent* _target) : m_target(_target) {

}

void FActorComponentTickFunc::registerWithTarget(IActorComponent* _target) {
	if (m_target)
		unregisterWithTarget();
	m_target = _target;
}

void FActorComponentTickFunc::unregisterWithTarget() {
	m_target = nullptr;
}

void FActorComponentTickFunc::RegisterWithTileMap(TileMap* _map) {
	if (_map) {
		_map->addTickFunc(this);
		m_map = _map;
	}
}

void FActorComponentTickFunc::unregisterWithLevel() {

}

void FActorComponentTickFunc::run(float _deltaTime) {
	m_target->Tick(_deltaTime);
}

IActorComponent::IActorComponent() {

}

IActorComponent::IActorComponent(AActor* _owner_in, bool _bNeverTick, bool _bCanTick) : m_bNeverTick(_bNeverTick), m_bCanTick(_bCanTick) {
	if (_owner_in)
		m_pOwner = _owner_in;
}

void IActorComponent::RegisterTickFuncWithTileMap(TileMap* _pTileMap) {
	if (m_bRegistered) {
		if (getOwner() != NULL && _pTileMap != NULL) {
			m_tickFunc.m_target = this;
			m_tickFunc.RegisterWithTileMap(_pTileMap);
		}
	}
}

void IActorComponent::unregisterWithOwner() {
	m_pOwner->removeComponent(this);
	m_pOwner = nullptr;
}

bool IActorComponent::isRegisteredWithOwner() {
	return m_pOwner != NULL;
}

void IActorComponent::registerTickFunc(FActorComponentTickFunc _tickFunc) {
// 	if (m_tickFunc)
// 		unregisterTickFunc();
// 	m_tickFunc = _tickFunc;
}

void IActorComponent::unregisterTickFunc() {
	m_tickFunc = nullptr;
}

AActor* IActorComponent::getOwner() {
	return m_pOwner;
}

void IActorComponent::Activate() {
	m_bActive = true;
}

void IActorComponent::Deactivate() {
	m_bActive = false;
}

void IActorComponent::ToggleActive() {
	m_bActive = !m_bActive;
}

bool IActorComponent::isActive() {
	return m_bActive;
}

void IActorComponent::EnableTick() {
	if (!m_bNeverTick)
		m_bCanTick = true;
}

void IActorComponent::DisableTick() {
	if (!m_bNeverTick)
		m_bCanTick = false;
}

bool IActorComponent::canTick() {
	return m_bCanTick;
}

void IActorComponent::Tick(float _deltaTime) {

}

IActorComponent::~IActorComponent() {

}

void IActorComponent::OnRegister()
{
	m_bRegistered = true;
}

void IActorComponent::SetOwner(AActor* _pOwner)
{
	m_pOwner = _pOwner;
}
