#ifdef LAB
#include "../../SDL/include/SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif //LAB

#include <iostream>
#include "map.h"
//#include "entity.h"
#include "updatedEntity.h"
#include "TextureManager.h"
#include "DisplayManager.h"

using namespace std;

//function prototype
void eventFinder(SDL_Event &event, Movement &movement);

int main(){
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

	//Entity *thePlayer = new Entity(100, player, 100, 100, 5, movePlayer, 0, moveLeft, static_cast<int>(TX_PLAYER));
    Entity *thePlayer = new Entity(PLAYER);
	dispMan.addEntity(thePlayer);

    Entity *theRobot = new Entity();
	dispMan.addEntity(theRobot);
    /*
	Entity *theHuman = new Entity(100, human, 400, 400, 5, moveLeft, 0, moveLeft, static_cast<int>(TX_HUMAN));
	dispMan.addEntity(theHuman);

	Entity *theRobot = new Entity(100, robot, 200, 200, 5, moveLeft, 0, moveLeft, static_cast<int>(TX_ROBOT));
	dispMan.addEntity(theRobot);

    */

	//While application is running
	while( !quit ){
		//Handle events on queue
		while( SDL_PollEvent( &event ) != 0 ){

			//User requests quit
			if( event.type == SDL_QUIT ){
				quit = true;
			}

			eventFinder(event, movement);
		}

		SDL_RenderPresent(renderer);
		//calls function to figure out event type

			thePlayer->move(movement);

			dispMan.refresh();

		//move(movement);
		//continue game stuff
	}


	return 0;
}

void eventFinder(SDL_Event &event, Movement &movement){
	//User presses a key
	if( event.type == SDL_KEYDOWN  && event.key.repeat == 0){
		//Figure out which key was pressed
		switch( event.key.keysym.sym ){
			case SDLK_UP:
				movement.UP = true;
				break;
			case SDLK_DOWN:
				movement.DOWN = true;
				break;
			case SDLK_LEFT:
				movement.LEFT = true;
				break;
			case SDLK_RIGHT:
				movement.RIGHT = true;
				break;
			case SDLK_SPACE:
				//shoot();
				break;
			default:
				break;
		}
	}
	//If a key was released
	else if( event.type == SDL_KEYUP && event.key.repeat == 0){
		//Adjust the velocity
		//TODO reset player to undo what we just pressed
		switch( event.key.keysym.sym )
		{
			case SDLK_UP:
				movement.UP = false;
				break;
			case SDLK_DOWN:
				movement.DOWN = false;
				break;
			case SDLK_LEFT:
				movement.LEFT = false;
				break;
			case SDLK_RIGHT:
				movement.RIGHT = false;
				break;
			default:
				break;
		}
	}
}

