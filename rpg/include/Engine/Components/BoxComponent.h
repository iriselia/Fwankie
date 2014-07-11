#pragma once
#include "PrimitiveComponent.h"
#include "Box2D.h"

class BoxComponent : public IPrimitiveComponent
{
public:
	BoxComponent();
	~BoxComponent();
	void SetBoxTextent(float _x, float _y) {
		x = _x;
		y = _y;
	}
	void RegisterWithBox2D(b2World* _b2World);
	void UnregisterFromBox2D(b2World* _b2World);

private:
	float x, y;

	b2Fixture* m_pB2Fixture;
};
