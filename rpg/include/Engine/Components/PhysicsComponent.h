#include "IComponent.h"
#include "GameEntity.h"

class PhysicsComponent : IComponent {

public:
	PhysicsComponent();
	~PhysicsComponent();
	virtual void Update(GameObject* obj);

private:

};