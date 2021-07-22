#include "map.h"


mapTile::mapTile(){
	// Tile (x,y) coordinate
	tileData.x = 0;
	tileData.y = 0;
	// Tile height*width
	tileData.h = TILE_HEIGHT;
	tileData.w = TILE_WIDTH;
	// Tile type enum ID
	tID = TID_PIT;

}
mapTile::mapTile(int x, int y, tileID id){
	tileData.x = x;
	tileData.y = y;
	tileData.h = TILE_HEIGHT;
	tileData.w = TILE_WIDTH;
	tID = id;
}

void mapTile::setTileData(int x, int y, int h, int w, tileID id){
	tileData.x = x;
	tileData.y = y;
	tileData.h = h;
	tileData.w = w;
	tID = id;
}
tileID mapTile::getType() {
	return tID;
}

SDL_Rect mapTile::getTile(){
	return tileData;
}

//MAP MANAGER SECTION

MapManager::~MapManager() {
}

MapManager::MapManager() {
	levelLoader(1);
}
void MapManager::levelLoader(int level){
	
	std::ifstream mapFile;
	int tile_type;

	switch (level){
		case 1:
			mapFile.open("maps/levelone.txt");
			break;
 	}
	gameMap.resize(MAX_TILES);

	if(mapFile.is_open()) {
		for(int i = 0; i < MAX_TILES; ++i){
			gameMap[i].resize(MAX_TILES);
			for(int j = 0; j < MAX_TILES; ++j){
				mapFile >> tile_type;
				gameMap[i][j] = new mapTile(i*TILE_WIDTH, j*TILE_HEIGHT, textureToTile(tile_type));
			}
		}
	}else{
		std::cout << "Map file failed to load" << std::endl;
	}

	mapFile.close();

}

tileID MapManager::textureToTile(int tile_type) {
	tileID tid;
	switch (tile_type) {
		case 0:
			tid = TID_TERRAIN;
		break;
		case 1:
			tid = TID_WALL;
		break;
		case 2:
			tid = TID_PIT;
		break;
	}
	return tid;
}

TextureID MapManager::tileToTexture(int texture_type) {
	TextureID tid;
	switch (texture_type) {
		case 0:
			tid = TX_TERRAIN;
		break;
		case 1:
			tid = TX_WALL;
		break;
		case 2:
			tid = TX_PIT;
		break;
	}
	return tid;
}

void MapManager::mapDrawer(SDL_Renderer * renderer, TextureManager * txMan) {

	SDL_Rect rect;
	SDL_Texture *texture[3];

	//preloads texture set
	for(int i = 0; i < 3; ++i){
		texture[i] = txMan->getTexture(tileToTexture(i));
	}

	//Loops itterate over map 2D vector
	for(int i = 0; i < MAX_TILES; ++i){
		for(int j = 0; j < MAX_TILES; ++j){
			rect = gameMap[i][j]->getTile();
			
			//Switch to load texture of choice
			switch (gameMap[i][j]->getType()) {
				case TID_TERRAIN:
					SDL_RenderCopy(renderer, texture[0], NULL, &rect);
					break;
				case TID_WALL:
					SDL_RenderCopy(renderer, texture[1], NULL, &rect);
					break;
				case TID_PIT:
					SDL_RenderCopy(renderer, texture[2], NULL, &rect);
					break;
			}
		}
	}
}
