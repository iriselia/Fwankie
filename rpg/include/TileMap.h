#pragma once
#include "Tmx.h"
#include "hgeSprite.h"
#include "Box2D.h"
#include "hgeb2draw.h"
#include <stdlib.h>

enum{ BACKGROUND, MIDGROUND, FOREGROUND };

class Camera;

class TileMap {
public:
	TileMap(const char* file_name);
	~TileMap();
	void Load();
	void Unload(); 
	bool isLoaded() { return m_bIsLoaded; }
	void Render();
	void RenderLayer(Camera* _camera, int _layer);
	void Render(int width_2, int height_2, int x, int y);
	int Get_Width() { return m_width; }
	int Get_Height() { return m_height; }
	void SetCamera(Camera* _pCamera) { m_pCamera = _pCamera; }

private:
	HGE* m_pHGE;
	bool m_bIsLoaded = false;
	int m_width;
	int m_height;
	Tmx::Map *m_pMap_info; 
	const Tmx::Layer* m_pLayer_BG;
	const Tmx::Layer* m_pLayer_MG;
	const Tmx::Layer* m_pLayer_FG;
	// We use a map of sprite maps because different tilesets
	// have their own gid and can overlap with each other.
	std::map<int, std::map<int, hgeSprite*>> m_tiles;

	Camera* m_pCamera;
};