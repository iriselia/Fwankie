#include "hge.h"
#include "TileMap.h"
#include "Camera.h"

/* @TODO: Reduce std map to 1 dimensional
*/
TileMap::TileMap(const char* file_name) {
	// parse map information from .tmx file.
	m_pHGE = hgeCreate(HGE_VERSION);
	const char* resourcePath = "resources/";
	std::string filePath = resourcePath;
	filePath.append(file_name);
	m_pMap_info = new Tmx::Map();
	m_pMap_info->ParseFile(filePath.c_str());
	m_width = m_pMap_info->GetWidth() * m_pMap_info->GetTileWidth();
	m_height = m_pMap_info->GetHeight() * m_pMap_info->GetTileHeight();
}

TileMap::~TileMap() {
	Unload();
	delete m_pMap_info;
}

void TileMap::Load() {
	for (int l = 0; l < m_pMap_info->GetNumLayers(); l++) {
		const Tmx::Layer* layer = m_pMap_info->GetLayer(l);
		if (layer->GetName() == "Background") {
			printf("Found background layer.\n");
			m_pLayer_BG = layer;
		}
		if (layer->GetName() == "Midground") {
			printf("Found midground layer.\n");
			m_pLayer_MG = layer;
		}
		if (layer->GetName() == "Foreground") {
			printf("Found foreground layer.\n");
			m_pLayer_FG = layer;
		}
	}


	// get number of tilesets
	for (int t = 0; t < m_pMap_info->GetNumTilesets(); t++) {
		// get attributes of tileset t
		const Tmx::Tileset *tileset = m_pMap_info->GetTileset(t);
		int margin = tileset->GetMargin();
		int spacing = tileset->GetSpacing();
		int tileH = tileset->GetTileHeight();
		int tileW = tileset->GetTileWidth();
		// get attributes of tileset texture
		const Tmx::Image *img = tileset->GetImage();
		int imgH = img->GetHeight();
		int imgW = img->GetWidth();
		int numH = (imgH - spacing) / (tileH + spacing);
		int numW = (imgW - spacing) / (tileW + spacing);
		// generate texture path and load texture
		const char* resourcePath = "resources/";
		std::string imgDir = resourcePath;
		imgDir.append((img->GetSource()).c_str());
		HTEXTURE newTileset = m_pHGE->Texture_Load(imgDir.c_str());
		// allocate std::map at index t for tileset textures
		m_tiles[tileset->GetFirstGid()] = std::map<int, hgeSprite*>();
		// parse & store
		for (int h = 0; h < numH; h++) {
			for (int w = 0; w < numW; w++) {
				// the particular tile in the particular tileset
				// of the map that we want to cut the tileset texture for
				m_tiles[t][tileset->GetTile(h*numW + w)->GetId()] =
					new hgeSprite(
					newTileset,
					(w + 1)*spacing + w*tileW,
					(h + 1)*spacing + h*tileH,
					tileW,
					tileH);
			}
		}
		// end of map parsing
	}
	m_bIsLoaded = true;
}

void TileMap::Unload() {
	for (int t = 0; t < m_pMap_info->GetNumTilesets(); t++) {
		std::map<int, hgeSprite*> a = m_tiles[t];
		for (auto pair : a) {
			delete pair.second;
		}
		//a.clear();
	}

	if (m_bIsLoaded)
		m_pHGE->Release();
	
	m_bIsLoaded = false;
}

// void TileMap::StepB2World() {
// 	// Instruct the world to perform a single step of simulation.
// 	// It is generally best to keep the time step and iterations fixed.
// 	m_pB2World->Step(timeStep, velocityIterations, positionIterations);
// }

// Default rendering function at position (0, 0). Only use for debugging, do not use for gameplay!!!
void TileMap::Render() {
	int tileW = m_pMap_info->GetTileWidth();
	int tileH = m_pMap_info->GetTileHeight();

	for (int l = 0; l < m_pMap_info->GetNumLayers(); l++) {
		const Tmx::Layer* layer = m_pMap_info->GetLayer(l);
		for (int w = 0; w < layer->GetWidth(); w++)
		for (int h = 0; h < layer->GetHeight(); h++) {
			int tileID = layer->GetTileId(w, h);
				if (tileID > 0) {
					int tilesetID = layer->GetTile(w, h).tilesetId;
					m_tiles[1][tileID]->Render(w * tileW, h * tileH);
				}

		}
	}
}

void TileMap::Render(int width, int height, int x, int y) {
	int tileW = m_pMap_info->GetTileWidth();
	int tileH = m_pMap_info->GetTileHeight();

	//int startTileX = x - 


	for (int l = 0; l < m_pMap_info->GetNumLayers(); l++) {
		const Tmx::Layer* layer = m_pMap_info->GetLayer(l);
		for (int w = 0; w < layer->GetWidth(); w++)
		for (int h = 0; h < layer->GetHeight(); h++) {
			int tileID = layer->GetTileId(w, h);
			if (tileID > 0) {
				int tilesetID = layer->GetTile(w, h).tilesetId;
				m_tiles[tilesetID][tileID]->Render(w * tileW + x, h * tileH + y);
			}

		}
	}
}

void TileMap::RenderLayer(Camera* _camera, int _layer) {
	// translate camera position to screen top left corner
	int x, y;
	x = _camera->Get_Display_Width_2() - _camera->GetXPosition();
	y = _camera->Get_Display_Height_2() - _camera->GetYPosition();
	// translate camera position again if map is smaller than screen
	// center the content.
	if (m_width < _camera->Get_Display_Width_2() * 2)
		x = (_camera->Get_Display_Width_2() * 2 - m_width) / 2;
	if (m_height < _camera->Get_Display_Height_2() * 2)
		y = (_camera->Get_Display_Height_2() * 2 - m_height) / 2;


	const Tmx::Layer* layer;
	switch (_layer)
	{
	case BACKGROUND:
		layer = m_pLayer_BG;
		break;
	case MIDGROUND:
		layer = m_pLayer_MG;
		break;
	case FOREGROUND:
		layer = m_pLayer_FG;
		break;
	default:
		
		break;
	}

	int tileW = m_pMap_info->GetTileWidth();
	int tileH = m_pMap_info->GetTileHeight();

	for (int w = 0; w < layer->GetWidth(); w++)
	for (int h = 0; h < layer->GetHeight(); h++) {
		int tileID = layer->GetTileId(w, h);
		if (tileID > 0) {
			int tilesetID = layer->GetTile(w, h).tilesetId;
			m_tiles[tilesetID][tileID]->Render(w * tileW + x, h * tileH + y);
		}
	}

}
