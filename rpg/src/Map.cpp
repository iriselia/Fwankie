#include "hge.h"
#include "Map.h"


const char* resourcePath = "resources/";
std::string filePath;
HGE* hge = 0;
/* @TODO: Reduce std map to 1 dimensional
*/
Map::Map(const char* file_name) {
	// parse map information from .tmx file.

	filePath = resourcePath;
	filePath.append(file_name);
	map_info = new Tmx::Map();
	map_info->ParseFile(filePath.c_str());
	width = map_info->GetWidth() * map_info->GetTileWidth();
	height = map_info->GetHeight() * map_info->GetTileHeight();
}

Map::~Map() {
	Destroy();
}

void Map::Load() {
	hge = hgeCreate(HGE_VERSION);
	// get number of tilesets
	for (int t = 0; t < map_info->GetNumTilesets(); t++) {
		// get attributes of tileset t
		const Tmx::Tileset *tileset = map_info->GetTileset(t);
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
		std::string imgDir = resourcePath;
		imgDir.append((img->GetSource()).c_str());
		HTEXTURE newTileset = hge->Texture_Load(imgDir.c_str());
		// allocate std::map at index t for tileset textures
		sprite_maps[tileset->GetFirstGid()] = std::map<int, hgeSprite*>();
		// parse & store
		for (int h = 0; h < numH; h++) {
			for (int w = 0; w < numW; w++) {
				// the particular tile in the particular tileset
				// of the map that we want to cut the tileset texture for
				sprite_maps[t][tileset->GetTile(h*numW + w)->GetId()] =
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

void Map::Destroy() {
	for (int t = 0; t < map_info->GetNumTilesets(); t++) {
		std::map<int, hgeSprite*> a = sprite_maps[t];
		for (auto pair : a) {
			delete pair.second;
		}
		//a.clear();
	}
	if (m_bIsLoaded)
		hge->Release();
	
	m_bIsLoaded = false;
	delete map_info;
}

// Default rendering function at position (0, 0). Only use for debugging, do not use for gameplay!!!
void Map::Render() {
	int tileW = map_info->GetTileWidth();
	int tileH = map_info->GetTileHeight();

	for (int l = 0; l < map_info->GetNumLayers(); l++) {
		const Tmx::Layer* layer = map_info->GetLayer(l);
		for (int w = 0; w < layer->GetWidth(); w++)
		for (int h = 0; h < layer->GetHeight(); h++) {
			int tileID = layer->GetTileId(w, h);
				if (tileID > 0) {
					int tilesetID = layer->GetTile(w, h).tilesetId;
					sprite_maps[1][tileID]->Render(w * tileW, h * tileH);
				}

		}
	}
}

void Map::Render(int width, int height, int x, int y) {
	int tileW = map_info->GetTileWidth();
	int tileH = map_info->GetTileHeight();

	//int startTileX = x - 


	for (int l = 0; l < map_info->GetNumLayers(); l++) {
		const Tmx::Layer* layer = map_info->GetLayer(l);
		for (int w = 0; w < layer->GetWidth(); w++)
		for (int h = 0; h < layer->GetHeight(); h++) {
			int tileID = layer->GetTileId(w, h);
			if (tileID > 0) {
				int tilesetID = layer->GetTile(w, h).tilesetId;
				sprite_maps[tilesetID][tileID]->Render(w * tileW + x, h * tileH + y);
			}

		}
	}
}