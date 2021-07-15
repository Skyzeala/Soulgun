#include <SDL2/SDL.h>

enum tileID { Empty, Wall };

class mapTile {
	public:
		//Constructor
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
