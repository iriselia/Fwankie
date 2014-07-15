#include "BoxComponent.h"
#include "hgeb2draw.h"

BoxComponent::BoxComponent()
{

}

BoxComponent::~BoxComponent()
{

}

void BoxComponent::RegisterWithBox2D(hgeB2World* _hgeB2World)
{
	// Define the polyline body.
	b2BodyDef bodyDef;
	bodyDef.position.Set(getX(), _hgeB2World->GetMapHeight() - getY());
	//bodyDef.type = b2_dynamicBody;

	b2FixtureDef fixtureDef;

	// Define a polygon shape.
	b2PolygonShape* p_polygonShape = new b2PolygonShape();

	fixtureDef.shape = p_polygonShape;

	p_polygonShape->SetAsBox(x, y);

	m_pB2Body  = _hgeB2World->CreateBody(&bodyDef);

	// Add the ground fixture to the ground body.
	m_pB2Fixture = m_pB2Body->CreateFixture(&fixtureDef);
}
