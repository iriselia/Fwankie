#include "IComponent.h"
#include "GameEntity.h"

class PhysicsComponent : IActorComponent {

public:
	PhysicsComponent();
	~PhysicsComponent();
	virtual void Update(GameObject* obj);

private:

};