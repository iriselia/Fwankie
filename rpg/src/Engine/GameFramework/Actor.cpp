#include "Actor.h"
#include "ActorComponent.h"


AActor::AActor() {
	//m_birthTime = GetSystemTime();
}

AActor::AActor(IActorComponent* _rootComponent, float _lifeSpan, Map* _map) :
m_RootComponent(_rootComponent), m_lifeSpan(_lifeSpan), m_map(_map) {
	//m_birthTime = GetSystemTime();
}

AActor::~AActor() {

}

void AActor::Tick(float _deltaTime) {
	for (auto& i : m_tickFunc)
		i.first->Tick(_deltaTime, i.second);
}
