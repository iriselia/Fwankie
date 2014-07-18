#include "Actor.h"
#include "SceneComponent.h"


AActor::AActor() {
	//m_birthTime = GetSystemTime();
}

AActor::AActor(ISceneComponent* _rootComponent, float _lifeSpan, TileMap* _map) :
m_pRootComponent(_rootComponent), m_lifeSpan(_lifeSpan), m_pCurrMap(_map) {
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

void AActor::RegisterAllComponents() {
	for (auto& component : m_OwnedComponents)
	{
		//Must set component to be registered first before calling OnRegister.
		component->SetRegistered(true);
		component->OnRegister();
		component->RegisterTickFuncWithTileMap(m_pCurrMap);
	}
}

void AActor::unregisterComponentWithMap(IActorComponent* _component) {

}

template<class T>
void AActor::getComponent(std::vector<T*>& _outComponent) {
	//check root component
	T* testComponent = dynamic_cast<T*>(m_pRootComponent);
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
	T* testComponent = dynamic_cast<T*>(m_pRootComponent);
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
	return m_pRootComponent;
}

std::vector<IActorComponent*>* AActor::getAllComponents() {
	return &m_OwnedComponents;
}

void AActor::AddComponent(IActorComponent* _component) {
	if (_component != NULL) {
		m_OwnedComponents.push_back(_component);
		_component->SetOwner(this);
	}
}

void AActor::RemoveComponent(IActorComponent* _component) {
	if (_component != NULL) {
		m_OwnedComponents.erase(std::find(m_OwnedComponents.begin(), m_OwnedComponents.end(), _component));
		_component->SetOwner(NULL);
	}
}

void AActor::clearComponents() {
	m_OwnedComponents.clear();
}

void AActor::RegisterWithTileMap(TileMap* _pTileMap)
{
	assert(_pTileMap);

	m_pCurrMap = _pTileMap;
	RegisterAllComponents();
}

TileMap* AActor::getCurrMap()
{
	return m_pCurrMap;
}

void AActor::AddRootComponent(ISceneComponent* _pRootComponent)
{
	m_pRootComponent = _pRootComponent;
	AddComponent(_pRootComponent);
}
