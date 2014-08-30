#pragma once
#include <vector>
#include <string>
#include "hge.h"
#include "SpriteComponent.h"

class Scene
{
public:
	Scene(const std::tstring _mapName);
	~Scene();

	void RenderAtPosition(float x, float y);
	void AddStaticSprite(SpriteComponent* _StaticSpriteComponent);

private:
	HGE* m_pHGE;
	std::tstring m_mapName;
	std::vector<SpriteComponent*> m_staticSpriteDrawList;
};