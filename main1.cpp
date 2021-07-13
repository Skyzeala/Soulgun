#include <iostream>
#include "../SDL/include/SDL2/SDL.h"
//#include "../SDL/include/SDL.h"
//#include "entity.h"

using namespace std;

//function prototypes
void eventFinder(SDL_Event &event);

struct movement{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

int main(){
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //While application is running
    while( !quit ){
        //Handle events on queue
        while( SDL_PollEvent( &event ) != 0 ){

            //User requests quit
            if( event.type == SDL_QUIT ){
                quit = true;
            }

            //calls function to figure out event type
            eventFinder(event);
        }

        //move(movement);
        //continue game stuff
    }

    return 0;
}


void eventFinder(SDL_Event &event){
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

