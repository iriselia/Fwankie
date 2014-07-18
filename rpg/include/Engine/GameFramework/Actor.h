#pragma once
#include "Object.h"
#include <vector>
#include <map>

//Component
class IActorComponent;

class ISceneComponent;

//Level
class TileMap;

//ComponentTickFunc
struct FActorComponentTickFunc;


class AActor : public Object
{
public:
    AActor();

	AActor(ISceneComponent* _rootComponent, float _lifeSpan, TileMap* _map);

	virtual ~AActor();

	//Tick Functions
	//default tick
	void Tick(float _deltaTime);

	//Life Spans
	float getBirthTime();

	void setBirthTime(float _birthTime);

	float getLifeSpan();

	void setLifeSpan(float _lifeSpan);

	//register with level
	void registerWithLevel();

	void RegisterWithTileMap(TileMap* _pTileMap);

	void unregisterWithMap();

	void RegisterAllComponents();

	virtual void unregisterComponentWithMap(IActorComponent* _component);

	//get specific component
	template<class T>
	void getComponent(std::vector<T*>& _outComponent);

	template<class T>
	void getComponent(T* _component);

	void AddRootComponent(ISceneComponent* _pRootComponent);
	IActorComponent* getRootComponent();

	std::vector<IActorComponent*>* getAllComponents();

	//modify component
	void AddComponent(IActorComponent* _component);

	void RemoveComponent(IActorComponent* _component);

	void clearComponents();

	TileMap* getCurrMap();
protected:
    //actor flags
    bool m_bEnableCollision = false;
	bool m_bEnableRender = false;
	bool m_bBlockUserInput = false;
	bool m_bDestructible = false;

	//component
	ISceneComponent* m_pRootComponent = nullptr;
	std::vector<IActorComponent*> m_OwnedComponents;

	//lifespan, if destructible
	//if lifespan is set to 0, this Actor will be destroyed when certain circumstance happens
	float m_lifeSpan = 0;
	float m_birthTime = 0;

	//Environment: level
	TileMap* m_pCurrMap;
};