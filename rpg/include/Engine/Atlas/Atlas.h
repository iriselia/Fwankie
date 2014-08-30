#pragma once
#include <map>
#include <string>
#include "TileMap.h"

class Atlas
{
public:
	static void AddMap(const TCHAR* _mapName);
	static TileMap* queryByName(const TCHAR* _mapName);
	static void LoadResource(const TCHAR* _mapName);
	static void UnloadResource(const TCHAR* _mapName);

	static void DestroyAll();
private:
	static std::map<std::tstring, TileMap*> m_atlas;


// new Altas

public:

private:
	// controllers
	// pawns
	// phx scene
};
