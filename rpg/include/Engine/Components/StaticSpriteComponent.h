#pragma once
#include "PrimitiveComponent.h"
#include "Actor.h"

class hgeSprite;

class StaticSpriteComponent : public IPrimitiveComponent
{
public:
	StaticSpriteComponent();
	~StaticSpriteComponent();
	AActor* getOwner() { return m_pOwner; }
	void UpdateBounds();
	bool setStaticSprite(hgeSprite* _staticSprite);

private:
	hgeSprite*		m_pStaticSprite;
	AActor*			m_pOwner;
};

StaticSpriteComponent::StaticSpriteComponent()
{
}

StaticSpriteComponent::~StaticSpriteComponent()
{
}