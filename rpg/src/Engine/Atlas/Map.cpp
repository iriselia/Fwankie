#include "Map.h"
#include "Actor.h"

Map::Map(TileMap* _tileMap, CollisionMap* _collisionMap)
{
	m_pTileMap = _tileMap;
	m_pCollisionMap = _collisionMap;
}

Map::~Map()
{
	delete m_pTileMap;
	delete m_pCollisionMap;
}

void Map::Update()
{

}

void Map::Render(Camera* _camera) {
	m_pTileMap->RenderLayer(_camera, BACKGROUND);
	m_pTileMap->RenderLayer(_camera, MIDGROUND);
	m_pTileMap->RenderLayer(_camera, FOREGROUND);
	m_pCollisionMap->Render(_camera);
}

void Map::LoadResource()
{
	m_pTileMap->Load();
	m_pCollisionMap->Load();
}

void Map::UnloadResource()
{
	m_pTileMap->Unload();
	m_pCollisionMap->Unload();
}

int Map::Get_Width()
{
	return m_pTileMap->Get_Width();
}

int Map::Get_Height()
{
	return m_pTileMap->Get_Height();
}

// void Map::AddCamera(Camera* _camera) {
// 	m_cameras.push_back(_camera);
// }

void Map::addActor(AActor* _actor) {
	m_ActorList.push_back(_actor);
}

AActor* Map::spawnActor() {
	AActor* spawn = new AActor();
	return spawn;
}

void Map::addTickFunc(FActorComponentTickFunc* _tickFunc) {
	if (_tickFunc)
		m_tickFuncList.push_back(_tickFunc);
}

void Map::removeTickFunc(FActorComponentTickFunc* _tickFunc) {
	if (_tickFunc)
		m_tickFuncList.erase(std::find(m_tickFuncList.begin(), m_tickFuncList.end(), _tickFunc));
}
