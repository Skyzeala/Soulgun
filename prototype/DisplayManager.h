/**
 * Display Manager for Soulgun
 */

#include "TextureManager.h"

// <placeholders>
// #include "Map.h"
// #include "Entity.h"
#define MAX_ENTITY 255

class Map { 
public:
    int offset_x;
    int offset_y;

    void refresh() { }
};

class Entity {
public:
    int x;
    int y;
    TextureID type;
};
// </placeholders>

/**
 * Manages where textures are drawn on-screen
 */
class DisplayManager
{
public:
    DisplayManager(SDL_Renderer *xRenderer, Map *xMap, TextureManager *xTexture) {
        map = xMap;
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
            if (entities[i] == entity)
                delete entity;
        }
    }

    void refresh() {
        // Put textures on screen
        SDL_Rect position;
        SDL_Point size;
        SDL_Texture *texture;
        Entity *e;

        // Map should draw the portion of its texture onscreen that it needs to
        map->refresh();

        for (int i = 0; i < MAX_ENTITY; ++i) {
            e = entities[i];

            texture = txMan->getTexture(e->type);
            size = txMan->getDimensions(e->type);
            position.h = size.y;
            position.w = size.x;

            position.x  = e->x - map->offset_x;
            position.y  = e->y - map->offset_y;

            SDL_RenderCopy(renderer, texture, NULL, &position);
        }
    }

private:
    int top = 0;
    Map *map;
    SDL_Renderer *renderer;
    TextureManager *txMan;
    Entity *entities[MAX_ENTITY];
}; 