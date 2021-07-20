#include "map.h"
#include "TextureManager.h"


mapTile::mapTile(){
	// Tile (x,y) coordinate
	tileData.x = 0;
	tileData.y = 0;
	// Tile height*width
	tileData.h = TILE_HEIGHT;
	tileData.w = TILE_WIDTH;
	// Tile type enum ID
	tID = TID_EMPTY;

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
	
	std::ifstream mapFile;
	int tile_type;
	mapFile.open("maps/levelone.txt");

	gameMap.resize(MAX_TILES);

	if(mapFile.is_open()) {
		for(int i = 0; i < MAX_TILES; ++i){
			gameMap[i].resize(MAX_TILES);
			for(int j = 0; j < MAX_TILES; ++j){
				mapFile >> tile_type; 
				gameMap[i][j] = new mapTile(i, j, static_cast<tileID>(tile_type));
			}
		}
	}else{
		std::cout << "Map file failed to load" << std::endl;
	}

	mapFile.close();
}
void MapManager::mapDrawer(SDL_Renderer * renderer, SDL_Texture * texture) {

	SDL_Rect rect;
	//mapSurface = SDL_CreateRGBSurface(0, TILE_WIDTH, TILE_HEIGHT, 32, 0, 0, 0, 0);

	for(int i = 0; i < MAX_TILES; ++i){
			for(int j = 0; j < MAX_TILES; ++j){
				if(gameMap[i][j]->getType() == TID_WALL) SDL_RenderDrawRect(renderer, &rect);

				rect = gameMap[i][j]->getTile();
				SDL_RenderCopy(renderer, texture, NULL, &rect);
			//	SDL_FillRect(mapSurface, &rect, SDL_MapRGB(mapSurface->format, 255, 0, 0));
			}
	}
}

