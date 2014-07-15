#pragma once
#include "PrimitiveComponent.h"
#include "hgeb2world.h"

class BoxComponent : public IPrimitiveComponent
{
public:
	BoxComponent();
	~BoxComponent();
	void SetBoxTextent(float _x, float _y) {
		x = _x;
		y = _y;
	}
	void RegisterWithBox2D(hgeB2World* _hgeB2World);
	void UnregisterFromBox2D(hgeB2World* _hgeB2World);

	// TODO: fix it
	b2Fixture* m_pB2Fixture;
	b2Body* m_pB2Body;
private:
	float x, y;


};
