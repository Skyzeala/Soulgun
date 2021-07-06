#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class gameWindow {
	public:
		int render(const int x, const int y);
		bool load_media();
		void close();

	private:
		SDL_Window *ptr_window;
		SDL_Surface *ptr_image;
		SDL_Surface *ptr_background;
};

