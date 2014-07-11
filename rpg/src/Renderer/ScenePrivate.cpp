#include "ScenePrivate.h"
#include "SpriteComponent.h"

void Scene::RenderAtPosition(float x, float y)
{
	for (auto& i : m_staticSpriteDrawList) {
		i->Render(x, y);
	}
}

void Scene::AddStaticSprite(SpriteComponent* _StaticSpriteComponent)
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
