#ifdef LAB
#include "../SDL/include/SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif //LAB

#include <iostream>
#include "map.h"
#include "humanoid.h"
#include "TextureManager.h"
#include "DisplayManager.h"

using namespace std;

//function prototype
void eventFinder(SDL_Event &event, Movement &movement);

int main( int argc, char **argv ) {
	//Main loop flag
	bool quit = false;
	Movement movement;

	//Event handler
	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Texture Manager Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	TextureManager *txMan = new TextureManager(renderer);
	DisplayManager dispMan(renderer, txMan);

	Humanoid *thePlayer = new Humanoid(100, ET_PLAYER, 100, 100, 10, movePlayer, 0, SS_SINGLESHOT, moveLeft, TX_PLAYER);
	dispMan.addEntity(thePlayer);

	Humanoid *theHuman = new Humanoid(100, ET_PLAYER, 400, 400, 5, moveLeft, 0, SS_SINGLESHOT, moveLeft, TX_HUMAN);
	dispMan.addEntity(theHuman);

	Humanoid *theRobot = new Humanoid(100, ET_PLAYER, 200, 200, 5, moveLeft, 0, SS_SINGLESHOT, moveLeft, TX_ROBOT);
	dispMan.addEntity(theRobot);

	//While application is running
	while( !quit ){
		//Handle events on queue
		while( SDL_PollEvent( &event ) != 0 ){
			
			//User requests quit
			if( event.type == SDL_QUIT ){
				quit = true;
			}

		}
		
		SDL_RenderPresent(renderer);
		//calls function to figure out event type
			eventFinder(event, movement);
			Position pos = thePlayer->getPosition();
			thePlayer->move(movement);
			dispMan.refresh();
		
		//move(movement);
		//continue game stuff
	}

		
	return 0;
}

void eventFinder(SDL_Event &event, Movement &movement){
	//User presses a key
	movement.up = false;
	movement.down = false;
	movement.right = false;
	movement.left = false;
	if( event.type == SDL_KEYDOWN){
		//Figure out which key was pressed
		switch( event.key.keysym.sym ){
			case SDLK_UP:
				movement.up = true;
				break;
			case SDLK_DOWN:
				movement.down = true;
				break;
			case SDLK_LEFT:
				movement.left = true;
				break;
			case SDLK_RIGHT:
				movement.right = true;
				break;
			case SDLK_SPACE:
				//shoot();
				break;
			default:
				break;
		}
	}
	//If a key was released
	else if( event.type == SDL_KEYUP){
		//Adjust the velocity
		//TODO reset player to undo what we just pressed
		switch( event.key.keysym.sym )
		{
			case SDLK_UP:
				movement.up = false;
				break;
			case SDLK_DOWN:
				movement.down = false;
				break;
			case SDLK_LEFT:
				movement.left = false;
				break;
			case SDLK_RIGHT:
				movement.right = false; 
				break;
			default:
				break;
		}
	}
}

