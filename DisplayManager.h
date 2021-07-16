/**
 * Display Manager for Soulgun
 */

#pragma once
#include "TextureManager.h"
#include "entity.h"

// <placeholders>
// #include "Map.h"
// #include "Entity.h"
#define MAX_ENTITY 255
// </placeholders>

/**
 * Manages where textures are drawn on-screen
 */
class DisplayManager
{
public:
    DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture) {
        renderer = xRenderer;
        txMan = xTexture;

        for (int i = 0; i < MAX_ENTITY; ++i) {
            entities[i] = NULL;
        }
    }

    ~DisplayManager(void) {
        for (int i = 0; i < MAX_ENTITY; ++i) {
            if (entities[i] != NULL)
                delete entities[i];
        }
    }

    void addEntity(Entity *entity) {
        entities[top++] = entity;
    }

    void removeEntity(Entity *entity) {
        for (int i = 0; i < MAX_ENTITY; ++i) {
            if (entities[i] == entity) {
                delete entity;
                --top;
            }
        }
    }

    void refresh() {
        // Put textures on screen
        SDL_Rect position;
        SDL_Point size;
        SDL_Texture *texture;
        Entity *e;

        // Map should draw the portion of its texture onscreen that it needs to
		texture = txMan->getTexture(TX_TERRAIN);
	 	size = txMan->getDimensions(TX_TERRAIN);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

        for (int i = 0; i < MAX_ENTITY; ++i) {
            e = entities[i];

            texture = txMan->getTexture(static_cast<TextureID>(e->getImage()));
            size = txMan->getDimensions(static_cast<TextureID>(e->getImage()));
            position.h = size.y;
            position.w = size.x;

            // position.x  = e->x - map->offset_x;
            // position.y  = e->y - map->offset_y;
            Position pos = e->getPosition();
            position.x  = pos.x;
            position.y  = pos.y;

            SDL_RenderCopy(renderer, texture, NULL, &position);
        }
    }

private:
    int top = 0;
    SDL_Renderer *renderer;
    TextureManager *txMan;
    Entity *entities[MAX_ENTITY];
}; 