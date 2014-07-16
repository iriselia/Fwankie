#pragma once
#include <map>
#include <vector>
#include <list>
#include "MapParser.h"
#include "CollisionMap.h"
#include "Camera.h"
#include "hgesprite.h"
#include <vector>

class AActor;

class TileMap;

struct FActorComponentTickFunc;

class FMapActorSpawningFunc {
	private:
	//random mode or customized mode
	//TODO random actor factory
	//TODO customized actor factory
};

class FMapTickFunc {
	public:
	FMapTickFunc();

	FMapTickFunc(TileMap* _map_in) : m_map(_map_in) {}

	//step 1: spawn actor (according to the current map info)
	//step 2: other update
	//step 3: finish tick
	void run();

	private:
	//current map info
	TileMap* m_map;
	//step 1, helper function: how many actor should be spawned in this tick
	int spawningNum();


};

class TileMap
{
public:
	TileMap(MapParser* _tileMap, CollisionMap* _collisionMap);
	~TileMap();
	void Update(float _dt);
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
	//add tickFunc
	void addTickFunc(FActorComponentTickFunc* _tickFunc);
	//remove tickFunc
	void removeTickFunc(FActorComponentTickFunc* _tickFunc);

private:
    friend class FMapTickFunc;
	bool m_bIsLoaded = false;
	//std::vector<Camera*> m_cameras;
	MapParser* m_pTileMap;
	CollisionMap* m_pCollisionMap;
	std::vector<AActor*> m_Actors;
	std::vector<FActorComponentTickFunc*> m_tickFuncs;

};

