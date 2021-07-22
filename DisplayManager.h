/**
 * Display Manager for Soulgun
 */

#pragma once
#include "TextureManager.h"
#include "humanoid.h"
#include <vector>
#include <math.h>

#define MIN_HUMAN 2
#define MIN_ROBOT 8

// Distance enemies will spawn away from the player
#define SPAWN_DIST 512

// Hard-coded until Manager is merged with Map
#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024

/**
 * Manages entities and where textures are drawn on-screen
 */
class DisplayManager
{
public:
    DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture);
    ~DisplayManager(void);

    void spawnEnemies(void);
    Humanoid *spawnHumanoid(EntityType type, Humanoid *player = NULL);
    void moveEnemies(Humanoid *player = NULL);
    bool isNearEnemy(int x, int y, int proximity);

    void addEntity(Entity *entity);
    void removeEntity(Entity *entity);
    void refresh(void);

private:
    std::vector<Entity *> entities;
    SDL_Renderer *renderer;
    TextureManager *txMan;
}; 