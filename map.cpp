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
mapTile::mapTile(int x, int y, tileID id, SDL_Texture * texture){
	tileData.x = x;
	tileData.y = y;
	tileData.h = TILE_HEIGHT;
	tileData.w = TILE_WIDTH;
	tID = id;
	tileTexture = texture;
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

SDL_Rect* mapTile::getTile(){
	return &tileData;
}
SDL_Texture* mapTile::getTileTexture(){
	return tileTexture;
}

//MAP MANAGER SECTION

MapManager::~MapManager() {
	for(int i = 0; i < MAX_TILES; ++i){
		gameMap[i].clear();
	}
	gameMap.clear();
}

MapManager::MapManager() {
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
				gameMap[i][j] = new mapTile(j*TILE_WIDTH, i*TILE_HEIGHT, textureToTile(tile_type), textureUnloader(tile_type));
			}
		}
	}else{
		std::cout << "Map file failed to load" << std::endl;
	}

	mapFile.close();

}
void MapManager::texturePreloader(TextureManager * txMan){ 
	
	mapTextures.resize(3);
	//preloads texture set
	for(int i = 0; i < 3; ++i){
		mapTextures[i] = txMan->getTexture(tileToTexture(i));
	}
	
}
SDL_Texture* MapManager::textureUnloader(int tile_type){
	return mapTextures[tile_type];
}
bool MapManager::mapCollision(Position player){
	if(player.x <= 0 || player.y <= 0 || player.x+20 >= 1024 || player.y+25 >= 1024) return false;
	if(gameMap[player.y / TILE_WIDTH][player.x / TILE_HEIGHT]->getType() == TID_WALL ||
		gameMap[(player.y+25) / TILE_WIDTH][ (player.x+20) / TILE_HEIGHT]->getType() == TID_WALL ||
		gameMap[(player.y+25) / TILE_WIDTH][ (player.x) / TILE_HEIGHT]->getType() == TID_WALL ||
		gameMap[(player.y) / TILE_WIDTH][ (player.x+20) / TILE_HEIGHT]->getType() == TID_WALL){
		return false;
	}
	else return true;

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
void MapManager::mapDrawer(SDL_Renderer * renderer) {

	//Loops itterate over map 2D vector
	for(int i = 0; i < MAX_TILES; ++i){
		for(int j = 0; j < MAX_TILES; ++j){
			SDL_RenderCopy(renderer, gameMap[i][j]->getTileTexture(), NULL, gameMap[i][j]->getTile());
			}
	}
}
