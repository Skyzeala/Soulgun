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

#define REFRESH_RATE 15

using namespace std;

//function prototype
bool eventFinder(SDL_Event &event, Movement &movement);

int main( int argc, char **argv ) {
	//Main loop flag
	bool quit = false;
	Movement movement;

	//Event handler
	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Soulgun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	TextureManager *txMan = new TextureManager(renderer);
	//Creates MapManger object
	MapManager *map = new MapManager(txMan);
	DisplayManager dispMan(renderer, txMan, map);
	vector<Projectile*> playerShots;

	Humanoid *player = dispMan.spawnHumanoid(map, ET_PLAYER);

	int nextRefresh = SDL_GetTicks();
	while (event.type != SDL_QUIT) 
	{
		// Check for input
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				break;
		}	

		// Interpret event
		if (eventFinder(event, movement))
		{
			playerShots = player->shoot(0,0,true);
			for (int i = 0; i < playerShots.size(); ++i)
				dispMan.addProjectile(playerShots[i]);
		}
		if(map->mapCollision(player->testMove(movement)))
		{
			player->move(movement);
			dispMan.updateWindowPos(player->getPosition());
		}
		// Wait for refresh delay
		int now = SDL_GetTicks();
		if (now < nextRefresh)
			SDL_Delay(nextRefresh - now);
		nextRefresh = now + REFRESH_RATE;
		
		
		SDL_RenderClear(renderer);
		
		
		// Redraw entities
		dispMan.spawnEnemies(map);
		dispMan.moveEnemies(map, player);
		dispMan.fireEnemies(player);
		dispMan.moveProjectiles(player);
		dispMan.refresh();
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

bool eventFinder(SDL_Event &event, Movement &movement){
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	movement.left = (keystate[SDL_SCANCODE_LEFT] != 0);
	movement.up = (keystate[SDL_SCANCODE_UP] != 0);
	movement.right = (keystate[SDL_SCANCODE_RIGHT] != 0);
	movement.down = (keystate[SDL_SCANCODE_DOWN] != 0);
	return (keystate[SDL_SCANCODE_SPACE] != 0);
}

