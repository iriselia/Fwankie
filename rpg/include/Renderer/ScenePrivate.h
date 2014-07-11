#pragma once
#include <vector>
#include "hge.h"
class Scene
{
public:
	Scene();
	~Scene();

	void RenderAtPosition(float x, float y);
	void AddStaticSprite(class StaticSpriteComponent* _StaticSpriteComponent);

private:
	HGE* m_pHGE;
	std::vector<StaticSpriteComponent*> m_staticSpriteDrawList;
};