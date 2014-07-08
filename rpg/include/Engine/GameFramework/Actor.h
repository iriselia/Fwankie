#pragma once
#include "Object.h"
#include <vector>
#include <map>

//Component
class IActorComponent;

//Level
class Map;

//ComponentTickScript
class FActorComponentTickFunc;


class IActor : public Object
{
public:
	virtual ~IActor();

	//Tick Functions
	//default tick
	virtual void Tick();

	//tick with given script(functor)
	virtual void Tick(std::map<IActorComponent*, FActorComponentTickFunc*>& _tickScript);

	//tick script(functor)
	virtual void registerTickScript(std::map<IActorComponent*, FActorComponentTickFunc*>& _tickScript);

	virtual void unregisterTickScript(IActorComponent* _unregisterTarget);

	//Life Spans
	virtual float getBirthTime();

	virtual void setBirthTime(float _birthTime);

	virtual float getLifeSpan();

	virtual void setLifeSpan(float _lifeSpan);

	//register with level
	virtual void registerWithMap();

	virtual void unregisterWithMap();

	virtual void registerComponentsWithMap(IActorComponent* _component);

	virtual void unregisterComponentWithMap(IActorComponent* _component);

	//get specific component
	template<class T>
	virtual void getComponent(std::vector<T*>& _outComponent);

	template<class T>
	virtual void getComponent(T* _component);

	virtual void getRootComponent();

	virtual void getAllComponent(std::vector<IActorComponent*>& _outComponent);

	//modify component
	virtual void addComponent(IActorComponent* _component);

	virtual void removeComponent(IActorComponent* _component);

	virtual void clearComponent();

private:
    //actor flags
    bool m_bEnableCollision;
	bool m_bEnableRender;
	bool m_bBlockUserInput;
	bool m_bDestructible;

	//component
	IActorComponent* m_RootComponent;
	std::vector<IActorComponent*> m_OwnedComponents;

	//lifespan, if destructible
	//if lifespan is set to 0, this Actor will be destroyed when certain circumstance happens
	float m_lifeSpan;
	float m_birthTime;

	//default tick script(functor)
	std::map<IActorComponent*, FActorComponentTickFunc*> m_tickScript;

	//Environment: level
	Map* m_map;
};
