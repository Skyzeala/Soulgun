#include "gameWindow.h"

int gameWindow::render(const int x,const int y) {	

	//Initializes the window to its pointer
	ptr_window = SDL_CreateWindow( "Test",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_ALLOW_HIGHDPI );

	//If it fails to initialize
	if(!ptr_window) {
		std::cout << "Error: Window failed to initialize" << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	else {
		ptr_background = SDL_GetWindowSurface(ptr_window);
	}

	//loads image onto window
	if(load_media()) {
		std::cout << "Media loaded" << std::endl;
	}
	else {
		std::cout << "Media load failed" << std::endl;
	}

	SDL_BlitScaled( ptr_image, NULL, ptr_background, NULL);
	SDL_UpdateWindowSurface(ptr_window);


	return 0;
}

bool gameWindow::load_media() {

	bool success = true;

	ptr_image = IMG_Load("ygb.jpg");
	if(!ptr_image) {
		std::cout << "Image load failed" << std::endl;
		success = false;
	}

	return success;
}

void gameWindow::close() {

	SDL_FreeSurface(ptr_image);
	ptr_image = NULL;

	SDL_DestroyWindow(ptr_window);
	ptr_window = NULL;

	SDL_Quit();
}
