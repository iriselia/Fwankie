#include "TileMap.h"
#include "Actor.h"

TileMap::TileMap(MapParser* _tileMap, CollisionMap* _collisionMap)
{
	m_pTileMap = _tileMap;
	m_pCollisionMap = _collisionMap;
}

TileMap::~TileMap()
{
	delete m_pTileMap;
	delete m_pCollisionMap;
}

void TileMap::Update()
{

}

void TileMap::Render(Camera* _camera) {
	m_pTileMap->RenderLayer(_camera, BACKGROUND);
	m_pTileMap->RenderLayer(_camera, MIDGROUND);
	m_pTileMap->RenderLayer(_camera, FOREGROUND);
	m_pCollisionMap->Render(_camera);
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
	m_ActorList.push_back(_actor);
}

AActor* TileMap::spawnActor() {
	AActor* spawn = new AActor();
	return spawn;
}

void TileMap::addTickFunc(FActorComponentTickFunc* _tickFunc) {
	if (_tickFunc)
		m_tickFuncList.push_back(_tickFunc);
}

void TileMap::removeTickFunc(FActorComponentTickFunc* _tickFunc) {
	if (_tickFunc)
		m_tickFuncList.erase(std::find(m_tickFuncList.begin(), m_tickFuncList.end(), _tickFunc));
}
