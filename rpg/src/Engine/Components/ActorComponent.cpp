#include "ActorComponent.h"
#include "Actor.h"

IActorComponent::IActorComponent() {

}

IActorComponent::IActorComponent(AActor* _owner_in, bool _bNeverTick, bool _bCanTick) : m_bNeverTick(_bNeverTick), m_bCanTick(_bCanTick) {
	if (_owner_in)
		m_owner = _owner_in;
}

void IActorComponent::registerWithOwner(AActor* _owner) {
	//if already registered, need to unregister before register again
	if (m_owner)
		unregisterWithOwner();
	_owner->addComponent(this);
	m_owner = _owner;
}

void IActorComponent::unregisterWithOwner() {
	m_owner->removeComponent(this);
	m_owner = nullptr;
}

bool IActorComponent::isRegisteredWithOwner() {
	return m_owner;
}

void IActorComponent::registerTickFunc(FActorComponentTickFunc* _tickFunc) {
	if (m_tickFunc)
		unregisterTickFunc();
	m_tickFunc = _tickFunc;
}

void IActorComponent::unregisterTickFunc() {
	m_tickFunc = nullptr;
}

AActor* IActorComponent::getOwner() {
	return m_owner;
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