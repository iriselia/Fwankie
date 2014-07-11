#pragma once
#include <vector>
#include "hge.h"
class Scene
{
public:
	Scene();
	~Scene();

	void RenderAtPosition(float x, float y);
	void AddStaticSprite(class SpriteComponent* _StaticSpriteComponent);

private:
	HGE* m_pHGE;
	std::vector<SpriteComponent*> m_staticSpriteDrawList;
};