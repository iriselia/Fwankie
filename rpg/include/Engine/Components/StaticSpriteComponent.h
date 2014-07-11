#pragma once
#include "PrimitiveComponent.h"
#include "StaticSpriteSceneProxy.h"

class hgeSprite;
class AActor;

class StaticSpriteComponent : public IPrimitiveComponent
{
public:
	StaticSpriteComponent();
	~StaticSpriteComponent();
	AActor* getOwner() { return m_pOwner; }
	void UpdateBounds();
	bool setStaticSprite(hgeSprite* _staticSprite);
	StaticSpriteSceneProxy* StaticSpriteComponent::Create_SceneProxy();
	void Update(float _DeltaTime);
	void Render(float x, float y);

private:
	hgeSprite*		m_pStaticSprite;
	AActor*			m_pOwner;
};