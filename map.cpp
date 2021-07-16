#include "map.h"

mapTile::mapTile(int x, int y, tileID id){
	tileData.x = x;
	tileData.y = y;
	tileData.h = 50;
	tileData.w = 50;
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

