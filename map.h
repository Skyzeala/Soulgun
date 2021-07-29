#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "entity.h"
#include "TextureManager.h"

const int TILE_HEIGHT = 35;
const int TILE_WIDTH = 35;
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
		mapTile(int x, int y, tileID id, SDL_Texture * texture );

		//Set tile data
		void setTileData(int x, int y, int h, int w, tileID id);
		//Returns tile ID
		tileID getType();
		//Returns SDL_Rect stored
		SDL_Rect* getTile();
		//Returns SDL_Texture stored
		SDL_Texture* getTileTexture();

	private:

		tileID tID;
		SDL_Rect tileData;
		SDL_Texture* tileTexture;

};

class MapManager {
	public:	
		MapManager();
		~MapManager();
		
		void levelLoader(int level);
		void texturePreloader(TextureManager * txMan); 
		SDL_Texture* textureUnloader(int tile_type);

		tileID textureToTile(int tile_type);
		TextureID tileToTexture(int texture_type);
		void mapDrawer(SDL_Renderer * renderer); 
	private:
		std::vector<SDL_Texture*> mapTextures;
		std::vector<std::vector<mapTile*> > gameMap;
};
