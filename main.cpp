#ifdef LAB
    #include "../SDL/include/SDL2/SDL.h"
#else
    #include <SDL2/SDL.h>
#endif //LAB

#include <iostream>
#include "map.h"
#include "entity.h"
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

    Entity *thePlayer = new Entity(100, player, 100, 100, 5, movePlayer, 0, moveLeft, static_cast<int>(TX_PLAYER));
    dispMan.addEntity(thePlayer);

    Entity *theHuman = new Entity(100, human, 400, 400, 5, moveLeft, 0, moveLeft, static_cast<int>(TX_HUMAN));
    dispMan.addEntity(theHuman);

    Entity *theRobot = new Entity(100, robot, 200, 200, 5, moveLeft, 0, moveLeft, static_cast<int>(TX_ROBOT));
    dispMan.addEntity(theRobot);

    //While application is running
    while( !quit ){
        //Handle events on queue
        while( SDL_PollEvent( &event ) != 0 ){

            //User requests quit
            if( event.type == SDL_QUIT ){
                quit = true;
            }

            //calls function to figure out event type
            eventFinder(event, movement);

            thePlayer->move(movement);

            dispMan.refresh();
        }

        //move(movement);
        //continue game stuff
    }

    return 0;
}

void eventFinder(SDL_Event &event, Movement &movement){
    //User presses a key
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

