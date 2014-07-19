#include "TileMap.h"
#include "ScenePrivate.h"
#include "Actor.h"
#include "ActorComponent.h"

TileMap::TileMap(MapParser* _tileMap, CollisionMap* _collisionMap, Scene* _scene)
{
	m_pTileMap = _tileMap;
	m_pCollisionMap = _collisionMap;
	m_pScene = _scene;
}

TileMap::~TileMap()
{
	delete m_pTileMap;
	delete m_pCollisionMap;
	delete m_pScene;
}

void TileMap::Update(float _dt)
{
	for (auto& tickFunc : m_tickFuncs)
	{
		tickFunc->run(_dt);
	}
	m_pCollisionMap->Update(_dt);
}

void TileMap::Render(Camera* _camera) {
	m_pTileMap->RenderLayer(_camera, BACKGROUND);
	m_pTileMap->RenderLayer(_camera, MIDGROUND);
	m_pTileMap->RenderLayer(_camera, FOREGROUND);
	m_pCollisionMap->Render(_camera);
}

void TileMap::Render()
{
	m_pScene->RenderAtPosition(0, 0);
}

void TileMap::LoadResource()
{
	m_pTileMap->Load();
	m_pCollisionMap->Load();
}

void TileMap::UnloadResource()
{
	m_pTileMap->Unload();
	m_pCollisionMap->Unload();
}

int TileMap::Get_Width()
{
	return m_pTileMap->Get_Width();
}

int TileMap::Get_Height()
{
	return m_pTileMap->Get_Height();
}

// void Map::AddCamera(Camera* _camera) {
// 	m_cameras.push_back(_camera);
// }

void TileMap::addActor(AActor* _actor) {
	m_Actors.push_back(_actor);
}

AActor* TileMap::spawnActor() {
	AActor* spawn = new AActor();
	return spawn;
}

void TileMap::addTickFunc(FActorComponentTickFunc* _tickFunc) {
	if (_tickFunc)
		m_tickFuncs.push_back(_tickFunc);
}

void TileMap::removeTickFunc(FActorComponentTickFunc* _tickFunc) {
	if (_tickFunc)
		m_tickFuncs.erase(std::find(m_tickFuncs.begin(), m_tickFuncs.end(), _tickFunc));
}

Scene* TileMap::getScene()
{
	return m_pScene;
}
