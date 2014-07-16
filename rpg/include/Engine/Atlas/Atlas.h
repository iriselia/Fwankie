#pragma once
#include <map>
#include <string>
#include "TileMap.h"

class Atlas
{
public:
	static void AddMap(const char* _mapName);
	static TileMap* queryByName(const char* _mapName);
	static void LoadResource(const char* _mapName);
	static void UnloadResource(const char* _mapName);

	static void DestroyAll();
private:
	static std::map<std::string, TileMap*> m_atlas;


// new Altas

public:

private:
	// controllers
	// pawns
	// phx scene
};
