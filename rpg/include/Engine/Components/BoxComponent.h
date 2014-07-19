#pragma once
#include "PrimitiveComponent.h"
#include "hgeb2world.h"

class BoxComponent : public IPrimitiveComponent
{
public:
	BoxComponent();
	~BoxComponent();
	void SetBoxTextent(Vector2D _extent) {
		assert(_extent > Vector2D::ZeroVector);
		m_extent = _extent;
	}
	void RegisterWithBox2D(hgeB2World* _hgeB2World);
	void UnregisterFromBox2D(hgeB2World* _hgeB2World);

	// TODO: fix it
	b2Fixture* m_pB2Fixture;
	b2Body* m_pB2Body;
private:
	float x_DEPRECATED, y_DEPRECATED;
	Vector2D m_extent;

};
