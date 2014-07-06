#pragma once
#include <map>
#include <string>
#include "Map.h"

class Atlas
{
public:
	static void AddMap(const char* _mapName);
	static Map* queryByName(const char* _mapName);
	static void LoadResource(const char* _mapName);
	static void UnloadResource(const char* _mapName);

	static void DestroyAll();
private:
	static std::map<std::string, Map*> m_atlas;

};
