#pragma once
#include <map>
#include <vector>
#include <list>
#include "TileMap.h"
#include "CollisionMap.h"
#include "Camera.h"
#include "hgesprite.h"

class Map
{
public:
	Map(TileMap* _tileMap, CollisionMap* _collisionMap);
	~Map();
	void Update();
	void Render(Camera* _camera);
	void LoadResource();
	void UnloadResource();
	bool isLoaded() { return m_bIsLoaded; }
	//void AddCamera(Camera* _camera);
	int Get_Width();
	int Get_Height();

private:
	bool m_bIsLoaded = false;
	//std::vector<Camera*> m_cameras;
	TileMap* m_pTileMap;
	CollisionMap* m_pCollisionMap;

};

