/**
 * Display Manager for Soulgun
 */

#pragma once
#include "map.h"
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
    DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture, MapManager *map);
    ~DisplayManager(void);

    void spawnEnemies(void);
    Humanoid *spawnHumanoid(EntityType type, Humanoid *player = NULL);
    void moveEnemies(Humanoid *player = NULL);
    bool isNearEnemy(int x, int y, int proximity);
    void fireEnemies(Humanoid *player = NULL);
    void moveProjectiles(Humanoid *player = NULL);

    void addEntity(Humanoid *entity);
    void removeEntity(Humanoid *entity);
    void addProjectile(Projectile *proj);
    void removeProjectile(Projectile *proj);
    void refresh(void);

    void flashBox(int startx, int starty, int Width, int Height);
    void flashScreen();
    bool swapSpots(Humanoid *toSwap);

private:
    std::vector<Humanoid *> entities;
    std::vector<Projectile *> projectiles;
    SDL_Renderer *renderer;
	MapManager *renderMap;
    TextureManager *txMan;
};
