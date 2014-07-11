#include "Actor.h"
#include "SceneComponent.h"


AActor::AActor() {
	//m_birthTime = GetSystemTime();
}

AActor::AActor(ISceneComponent* _rootComponent, float _lifeSpan, TileMap* _map) :
m_RootComponent(_rootComponent), m_lifeSpan(_lifeSpan), m_map(_map) {
	//m_birthTime = GetSystemTime();
}

AActor::~AActor() {

}

void AActor::Tick(float _deltaTime) {

}

float AActor::getBirthTime() {
	return m_birthTime;
}

void AActor::setBirthTime(float _birthTime) {
	m_birthTime = _birthTime;
}

float AActor::getLifeSpan() {
	return m_lifeSpan;
}

void AActor::setLifeSpan(float _lifeSpan) {
	m_lifeSpan = _lifeSpan;
}

void AActor::registerWithLevel() {

}

void AActor::unregisterWithMap() {

}

void AActor::registerComponentsWithMap(IActorComponent* _component) {

}

void AActor::unregisterComponentWithMap(IActorComponent* _component) {

}

template<class T>
void AActor::getComponent(std::vector<T*>& _outComponent) {
	//check root component
	T* testComponent = dynamic_cast<T*>(m_RootComponent);
	if (testComponent)
		_outComponent.push_back(testComponent);
	//check other components
	for (auto& i : m_OwnedComponents) {
		testComponent = dynamic_cast<T*>(i);
		if (testComponent)
			_outComponent.push_back(testComponent);
	}
}

template<class T>
void AActor::getComponent(T* _component) {
	//check root component
	T* testComponent = dynamic_cast<T*>(m_RootComponent);
	if (testComponent) {
		_component = testComponent;
		return
	}
	//check other components
	for (auto& i : m_OwnedComponents) {
		testComponent = dynamic_cast<T*>(i);
		if (testComponent) {
			_component = testComponent;
			return;
		}
	}
}

IActorComponent* AActor::getRootComponent() {
	return m_RootComponent;
}

std::vector<IActorComponent*>* AActor::getAllComponent() {
	return &m_OwnedComponents;
}

void AActor::addComponent(IActorComponent* _component) {
	if (_component)
		m_OwnedComponents.push_back(_component);
}

void AActor::removeComponent(IActorComponent* _component) {
	if (_component)
		m_OwnedComponents.erase(std::find(m_OwnedComponents.begin(),
		m_OwnedComponents.end(), _component));
}

void AActor::clearComponent() {
	m_OwnedComponents.clear();
}
