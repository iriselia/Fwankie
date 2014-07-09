#pragma once
#include <map>
#include <vector>
#include <list>
#include "TileMap.h"
#include "CollisionMap.h"
#include "Camera.h"
#include "hgesprite.h"
#include <vector>

class AActor;

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
	//modify ActorList
	//add an existing actor
	void addActor(AActor* _actor);
	//create and add an actor, then return its ptr
	AActor* spawnActor();
	//remove an actor from the level, but will not destroy it, returns its ptr
	AActor* removeActor(AActor* _actor);
	//destroy and remove an actor from the level
	void destroyActor(AActor* _actor);

private:
	bool m_bIsLoaded = false;
	//std::vector<Camera*> m_cameras;
	TileMap* m_pTileMap;
	CollisionMap* m_pCollisionMap;
	std::vector<AActor*> m_ActorList;

};

