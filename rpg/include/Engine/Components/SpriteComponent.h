#pragma once
#include "PrimitiveComponent.h"
#include "StaticSpriteSceneProxy.h"

class hgeSprite;
class AActor;

class SpriteComponent : public IPrimitiveComponent
{
public:
	SpriteComponent();
	~SpriteComponent();
	AActor* getOwner() { return m_pOwner; }
	void UpdateBounds();
	bool setStaticSprite(hgeSprite* _staticSprite);
	StaticSpriteSceneProxy* SpriteComponent::Create_SceneProxy();
	virtual void Tick(float _DeltaTime);
	void Render(float x, float y);

private:
	hgeSprite*		m_pStaticSprite;
	AActor*			m_pOwner;
};