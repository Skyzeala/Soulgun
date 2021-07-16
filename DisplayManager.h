/**
 * Display Manager for Soulgun
 */

#pragma once
#include "TextureManager.h"
#include "entity.h"

#define MAX_ENTITY 255

/**
 * Manages entities and where textures are drawn on-screen
 */
class DisplayManager
{
public:
    DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture);
    ~DisplayManager(void);

    void addEntity(Entity *entity);
    void removeEntity(Entity *entity);
    void refresh(void);

private:
    int top = 0;
    SDL_Renderer *renderer;
    TextureManager *txMan;
    Entity *entities[MAX_ENTITY];
}; 