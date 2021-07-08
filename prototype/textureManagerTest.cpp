// This is just a test of the Texture Manager for demonstration purposes

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include <iostream>

int main(int argv, char** args)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("Texture Manager Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	TextureManager tex(renderer);
	
	bool isRunning = true;
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
				}
			}
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		// Put textures on screen
		SDL_Rect position;
		SDL_Point bgsize;
		SDL_Point fgsize;
		SDL_Texture *texture;

		texture = tex.getTexture(TX_TERRAIN);
	 	bgsize = tex.getDimensions(TX_TERRAIN);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		texture = tex.getTexture(TX_PLAYER);
		position.x  = bgsize.x / 2;
		position.y  = bgsize.y / 2;
	 	fgsize = tex.getDimensions(TX_PLAYER);
		position.h = fgsize.y;
		position.w = fgsize.x;
		SDL_RenderCopy(renderer, texture, NULL, &position);

		texture = tex.getTexture(TX_ROBOT);
		position.x  = bgsize.x / 4;
		position.y  = bgsize.y / 4;
	 	fgsize = tex.getDimensions(TX_ROBOT);
		position.h = fgsize.y;
		position.w = fgsize.x;
		SDL_RenderCopy(renderer, texture, NULL, &position);

		texture = tex.getTexture(TX_HUMAN);
		position.x  = bgsize.x / 1.5;
		position.y  = bgsize.y / 1.5;
	 	fgsize = tex.getDimensions(TX_HUMAN);
		position.h = fgsize.y;
		position.w = fgsize.x;
		SDL_RenderCopy(renderer, texture, NULL, &position);

		// Draw a bunch of bullets
		texture = tex.getTexture(TX_BULLET);
		fgsize = tex.getDimensions(TX_BULLET);
		position.h = fgsize.y;
		position.w = fgsize.x;
		for (int i = 1; i <= 15; ++i) {
			position.x -= 10;
			position.y -= 10;
			SDL_RenderCopy(renderer, texture, NULL, &position);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}