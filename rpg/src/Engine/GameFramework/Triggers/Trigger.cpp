#include "Trigger.h"
#include "TriggerRegion_Circle.h"
#include "Player.h"

template <class Entity_Type>
Trigger<Entity_Type>::Trigger(unsigned int id) {
}

template <class Entity_Type>
Trigger<Entity_Type>::~Trigger() {
	delete m_pRegionOfInfluence;
}

template <class Entity_Type>
void Trigger<Entity_Type>::AddCircularTriggerRegion(float _x, float _y, float _radius) {
	m_pRegionOfInfluence = new TriggerRegion_Circle(_x, _y, _radius);
}

template <class Entity_Type>
bool Trigger<Entity_Type>::isTouchingTrigger(float _x, float _y, float _entityRadius)const {
	return m_pRegionOfInfluence->isTouching(_x, _y, _entityRadius);
}

// Explicit Declaration
template class Trigger<Player>;
