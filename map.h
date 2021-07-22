#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "TextureManager.h"

const int TILE_HEIGHT = 30;
const int TILE_WIDTH = 30;
const int MAX_TILES = 30;

enum tileID 
{ 
	TID_TERRAIN,
	TID_WALL,
	TID_PIT,
};


class mapTile {
	public:
		//Constructor
		mapTile();
		//Argumented Constructor
		mapTile(int x, int y, tileID id);

		//Set tile data
		void setTileData(int x, int y, int h, int w, tileID id);
		//Returns tile ID
		tileID getType();
		//Returns SDL_Rect stored
		SDL_Rect getTile();

	private:

		tileID tID;
		SDL_Rect tileData;

};

class MapManager {
	public:	
		MapManager();
		~MapManager();

		void mapDrawer(SDL_Renderer * renderer, TextureManager * txMan); 


	private:
		SDL_Surface *mapSurface;
		std::vector<std::vector<mapTile*> > gameMap;
};
