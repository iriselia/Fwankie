#include "BoxComponent.h"

BoxComponent::BoxComponent()
{

}

BoxComponent::~BoxComponent()
{

}

void BoxComponent::RegisterWithBox2D(b2World* _b2World)
{
	// Define the polyline body.
	b2BodyDef bodyDef;
	bodyDef.position.Set(getX(), getY());

	b2FixtureDef fixtureDef;

	// Define a polygon shape.
	b2PolygonShape* p_polygonShape = new b2PolygonShape();

	fixtureDef.shape = p_polygonShape;

	p_polygonShape->SetAsBox(x, y);

	b2Body* p_body = _b2World->CreateBody(&bodyDef);

	// Add the ground fixture to the ground body.
	m_pB2Fixture = p_body->CreateFixture(&fixtureDef);
}
