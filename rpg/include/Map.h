#include "Tmx.h"
#include "hgeSprite.h"
#include <stdlib.h>

#pragma once
#ifndef MAP_H
#define MAP_H

class Map {
public:
	Map(const char* file_name);
	~Map();
	void Load();
	void Unload();
	bool isLoaded() { return m_bIsLoaded; }
	void Render();
	void Render(int width_2, int height_2, int x, int y);
	int Get_Width() { return width; }
	int Get_Height() { return height; }
private:
	bool m_bIsLoaded = false;
	int width;
	int height;
	Tmx::Map *map_info;
	HTEXTURE *raw_textures;
	// We use a map of sprite maps because different tilesets
	// have their own gid and can overlap with each other.
	std::map<int, std::map<int, hgeSprite*>> sprite_maps;
};

#endif