#pragma once
#include "Object.h"

class IActorComponent : public Object {
public:
	virtual ~IActorComponent();
	virtual void TickComponent(float DeltaTime) = 0;
	void RegisterComponent();
	//void RegisterComponentWithWorld();

private:

};