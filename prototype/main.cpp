#include "gameWindow.h"

enum keyPress {
	  KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

int main()
{ 
	//Initializes SDL library
	if(SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
		std::cout << "SDL failed Init" << std::endl;
		return 0;
	}
	
	// Game window object
	gameWindow window_object;
	// Event object
	SDL_Event windowEvent;
	
	// Window initializer
	window_object.render(900, 900);

	//Game loop to keep window open
	while(true) {
		if (SDL_PollEvent( &windowEvent)) {
			if (SDL_QUIT == windowEvent.type) {
				std::cout << "Window closed";
				break;
			}
		}
	}
	//Clears memory and closes window
	window_object.close();


	return 0;
}
