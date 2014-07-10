#pragma once
#include <vector>
class Scene
{
public:
	Scene();
	~Scene();

	void AddStaticSprite(class StaticSpriteComponent* _StaticSpriteComponent) {
		//FStaticSpriteSceneProxy* StaticSpriteSceneProxy = _StaticSpriteComponent->CreateSceneProxy();
		//_StaticSpriteComponent->SceneProxy = StaticSpriteSceneProxy;
	}

private:
	std::vector<StaticSpriteComponent> m_staticSpriteDrawList;
};

Scene::Scene()
{
}

Scene::~Scene()
{
}