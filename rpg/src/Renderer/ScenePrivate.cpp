#include "ScenePrivate.h"
#include "SpriteComponent.h"

void Scene::RenderAtPosition(float x, float y)
{
	assert(!m_staticSpriteDrawList.empty());
	for (auto& i : m_staticSpriteDrawList) {
		i->Render(i->getX_DEPRECATED(), i->getY_DEPRECATED());
	}
}

void Scene::AddStaticSprite(SpriteComponent* _StaticSpriteComponent)
{
	m_staticSpriteDrawList.push_back(_StaticSpriteComponent);
}

Scene::Scene(const std::string _mapName)
{
	m_pHGE = hgeCreate(HGE_VERSION);
	m_mapName = _mapName;
}

Scene::~Scene()
{
	m_pHGE->Release();
}
