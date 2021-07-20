/**
 * Display Manager for Soulgun
 */

#pragma once
#include "TextureManager.h"
#include "entity.h"
#include <vector>

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
    std::vector<Entity *> entities;
    SDL_Renderer *renderer;
    TextureManager *txMan;
}; 