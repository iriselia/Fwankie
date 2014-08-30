#include "Atlas.h"
#include "ScenePrivate.h"

void Atlas::AddMap(const TCHAR* _mapName) {
	MapParser* tileMap = new MapParser(_mapName);
	CollisionMap* collisionMap = new CollisionMap(_mapName);
	Scene* scene = new Scene(_mapName);
	TileMap* temp = new TileMap(tileMap, collisionMap, scene);
	assert(temp);
	m_atlas[_mapName] = temp;
}

TileMap* Atlas::queryByName(const TCHAR* _mapName) {
	return m_atlas[_mapName] ?
		m_atlas[_mapName] : nullptr;
}

void Atlas::LoadResource(const TCHAR* _mapName) {
	assert(!m_atlas[_mapName]->isLoaded());
	m_atlas[_mapName]->LoadResource();
}

void Atlas::UnloadResource(const TCHAR* _mapName) {
	assert(m_atlas[_mapName]->isLoaded());
	m_atlas[_mapName]->UnloadResource();
}

void Atlas::DestroyAll() { for (auto i : m_atlas) delete i.second; }