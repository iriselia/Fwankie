#include "Atlas.h"

void Atlas::AddMap(const char* _mapName) {
	MapParser* tileMap = new MapParser(_mapName);
	CollisionMap* collisionMap = new CollisionMap(_mapName);
	TileMap* temp = new TileMap(tileMap, collisionMap);
	assert(temp);
	m_atlas[_mapName] = temp;
}

TileMap* Atlas::queryByName(const char* _mapName) {
	return m_atlas[_mapName] ?
		m_atlas[_mapName] : nullptr;
}

void Atlas::LoadResource(const char* _mapName) {
	assert(!m_atlas[_mapName]->isLoaded());
	m_atlas[_mapName]->LoadResource();
}

void Atlas::UnloadResource(const char* _mapName) {
	assert(m_atlas[_mapName]->isLoaded());
	m_atlas[_mapName]->UnloadResource();
}

void Atlas::DestroyAll() { for (auto i : m_atlas) delete i.second; }