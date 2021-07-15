#ifdef LAB
    #include "../SDL/include/SDL2/SDL.h"
#else
    #include <SDL2/SDL.h>
#endif //LAB
#include <iostream>
#include "entity.h"

using namespace std;

//function prototype
void eventFinder(SDL_Event &event, Movement &movement){

int main(){
    //Main loop flag
    bool quit = false;
    Movement movement;

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
            eventFinder(event, movement);
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

