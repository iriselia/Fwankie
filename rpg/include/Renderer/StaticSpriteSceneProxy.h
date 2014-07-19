#pragma once
#include "PrimitiveSceneProxy.h"

class StaticSpriteSceneProxy : public PrimitiveSceneProxy
{
public:
	StaticSpriteSceneProxy();
	~StaticSpriteSceneProxy();

	virtual void Render(float x, float y);
private:

};