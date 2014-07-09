#include "Actor.h"

AActor::AActor() {

}

void AActor::Tick() {

}

void AActor::Tick(std::map<IActorComponent*, FActorComponentTickFunc*>& _tickScript) {

}

void AActor::registerTickScript(std::map<IActorComponent*, FActorComponentTickFunc*>& _tickScript) {

}

void AActor::unregisterTickScript(IActorComponent* _unregisterTarget) {

}


float AActor::getBirthTime() {
	return 0;
}

void AActor::setBirthTime(float _birthTime) {

}

float AActor::getLifeSpan() {
	return 0;
}

void AActor::setLifeSpan(float _lifeSpan) {

}

void AActor::registerWithMap() {

}

void AActor::unregisterWithMap() {

}

void AActor::registerComponentsWithMap(IActorComponent* _component) {

}

void AActor::unregisterComponentWithMap(IActorComponent* _component) {

}

template<class T>
void AActor::getComponent(std::vector<T*>& _outComponent) {

}

template<class T>
void AActor::getComponent(T* _component) {

}

void AActor::getRootComponent() {

}

void AActor::getAllComponent(std::vector<IActorComponent*>& _outComponent) {

}

void AActor::addComponent(IActorComponent* _component) {

}

void AActor::removeComponent(IActorComponent* _component) {

}

void AActor::clearComponent() {

}
