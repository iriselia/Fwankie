#include "ScenePrivate.h"
#include "StaticSpriteComponent.h"

void Scene::RenderAtPosition(float x, float y)
{
	for (auto& i : m_staticSpriteDrawList) {
		i->Render(x, y);
	}
}

void Scene::AddStaticSprite(StaticSpriteComponent* _StaticSpriteComponent)
{
	m_staticSpriteDrawList.push_back(_StaticSpriteComponent);
}

Scene::Scene()
{
	m_pHGE = hgeCreate(HGE_VERSION);
}

Scene::~Scene()
{
	m_pHGE->Release();
}
