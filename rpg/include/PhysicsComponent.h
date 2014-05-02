#include "IComponent.h"
#include "GameObject.h"

class PhysicsComponent : IComponent {

public:
	PhysicsComponent();
	~PhysicsComponent();
	virtual void Update(GameObject* obj);

private:

};