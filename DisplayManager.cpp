#include "DisplayManager.h"

/**
 * Initializes the display manager
 * 
 * @param xRenderer External renderer
 * @param xTexture External texture manager
 */
DisplayManager::DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture, MapManager *map) {
    renderer = xRenderer;
    txMan = xTexture;
		renderMap = map;
}

/**
 * Deconstructs all entities
 */
DisplayManager::~DisplayManager(void) {
    for (int i = 0; i != entities.size(); ++i) {
        delete entities[i];
    }
    entities.clear();
}

/**
 * Adds an entity to the manager
 * 
 * @param entity Pointer to an entity
 */
void DisplayManager::addEntity(Humanoid *entity) {
    entities.push_back(entity);
}

/**
 * Removes an entity from the manager
 * 
 * @param entity Pointer to an entity that is being managed
 */
void DisplayManager::removeEntity(Humanoid *entity) {
    for (int i = 0; i < entities.size(); ++i) {
        if (entities[i] == entity) {
            delete entity;
            entities.erase(entities.begin() + i);
        }
    }
}

/**
 * Spawns enemies as needed
 */
void DisplayManager::spawnEnemies(void) {
    int humans = 0;
    int robots = 0;
    Humanoid *player = NULL;
    
    for (int i = 0; i < entities.size(); ++i) {
        Humanoid *e = entities[i];
        switch (e->getType()) {
            case ET_HUMAN:
                ++humans;
            break;
            case ET_ROBOT:
                ++robots;
            break;
            case ET_PLAYER:
                player = dynamic_cast<Humanoid *>(e);
            break;
        }
    }

    // Spawn humans if there aren't enough
    if (humans < MIN_HUMAN) {
        for (int x = 0; x < MIN_HUMAN - humans; ++x) {
            spawnHumanoid(ET_HUMAN, player);
        }
    }

    // Spawn robots if there aren't enough
    if (robots < MIN_ROBOT) {
        for (int x = 0; x < MIN_ROBOT - robots; ++x) {
            spawnHumanoid(ET_ROBOT, player);
        }
    }
}

/**
 * Spawns a humanoid entity at an appropriate location considering player location and other enemies
 * 
 * @param type Type of humanoid to spawn
 * @param player Pointer to the player
 * @returns A pointer to the humanoid spawned
 */
Humanoid *DisplayManager::spawnHumanoid(EntityType type, Humanoid *player) {
    // Place player at center of map
    if (type == ET_PLAYER) {
	    player = new Humanoid(100, ET_PLAYER, MAP_WIDTH / 2, MAP_HEIGHT / 2, 2, movePlayer, 0, SS_SINGLESHOT, moveLeft, TX_PLAYER);

        addEntity(player);
        return player;
    }

    Position pos = player->getPosition();

    // Have enemies encircle the player
    float unitCircle = 2 * M_PI;
    float total = (MIN_HUMAN + MIN_ROBOT);

    for (float i = 0; i <= unitCircle; i += (unitCircle / total)) {
        int x = pos.x + cos(i) * SPAWN_DIST;
        int y = pos.y + sin(i) * SPAWN_DIST;

        if (!isNearEnemy(x, y, 0)) {
            Humanoid *e = new Humanoid(100, type, x, y, 2, movePlayer, 0, SS_SINGLESHOT, moveLeft, static_cast<TextureID>(type));
            addEntity(e);
            return e;
        }
    }

    return NULL;
}

/**
 * Enemy movement AI
 * 
 * @param player Pointer to the player
 */
void DisplayManager::moveEnemies(Humanoid *player) {
    Position playerPos = player->getPosition(); 
    Humanoid *h = NULL;

    for (int i = 0; i < entities.size(); ++i) {
        Humanoid *e = entities[i];
        Movement mov;
        int direction = 0;
        int now = SDL_GetTicks();

        Position enemyPos = e->getPosition();

        // All hail Pythagoras
        int distFromPlayer = static_cast<int>(sqrt(pow(abs(playerPos.x - enemyPos.x), 2) + pow(abs(playerPos.y - enemyPos.y), 2)));

        switch (e->getType()) {
            case ET_HUMAN:
                // Humans moves randomly on diagonals
                h = (e);
                if (now - h->moveStartTime > HUMAN_MOVE_TIME) {
                    h->moveStartTime = now;
                
                    // If too far away, force to move closer to player
                    if (distFromPlayer > ENEMY_MAX_DIST) {
                        mov.right = (playerPos.x > enemyPos.x);
                        mov.up = (playerPos.y < enemyPos.y);
                    }
                    // Otherwise be random
                    else {
                        // Vertical movement
                        direction = rand() % 2;
                        mov.up = direction;

                        // Horizontal movement
                        direction = rand() % 2;
                        mov.right = direction;
                    }
                    mov.down = !mov.up;
                    mov.left = !mov.right;
                    
                    h->move(mov);
                }
                else {
                    h->move(h->moveDirection);
                }
            break;
            case ET_ROBOT:
                // Robots move rigidly and nonstop
                h = (e);

                if (now - h->moveStartTime > ROBOT_MOVE_TIME) {
                    h->moveStartTime = now;
                
                    // If too far away, force to move closer to player
                    if (distFromPlayer > ENEMY_MAX_DIST) {
                        mov.right = (playerPos.x > enemyPos.x);
                        mov.up = (playerPos.y < enemyPos.y);
                    }
                    // Otherwise be random
                    else {
                        // Vertical movement
                        direction = rand() % 2;
                        mov.up = direction;

                        // Horizontal movement
                        direction = rand() % 2;
                        mov.right = direction;
                    }
                    mov.down = !mov.up;
                    mov.left = !mov.right;

                    // Enforce 90-degree movement
                    if (rand() % 2 == 1) {
                        // Disable vertical
                        mov.up = false;
                        mov.down = false;
                    }
                    else {
                        // Disable horizontal
                        mov.left = false;
                        mov.right = false;
                    }
                    h->move(mov);
                }
                else {
                    h->move(h->moveDirection);
                }
            break;
        }
    }
}

/**
 * Indicates whether an enemy is located near a coordinate
 * 
 * @param x X coorindate
 * @param y Y coordinate
 * @param proximity Distance from the coordinates to be considered "near"
 * @returns True if an enemy is located near this coordinate
 */
bool DisplayManager::isNearEnemy(int x, int y, int proximity) {
    for (int i = 0; i < entities.size(); ++i) {
        Entity *e = entities[i];
        Position pos = e->getPosition();

        // Todo: Do some pythagorean theorem magic to incorporate proximity
        if (pos.x == x && pos.y == y)
            return true;
    }    

    return false;
}



void DisplayManager::addProjectile(Projectile *proj) {
    projectiles.push_back(proj);
}
void DisplayManager::removeProjectile(Projectile *proj) {
    for (int i = 0; i < projectiles.size(); ++i) {
        if (projectiles[i] == proj) {
            delete proj;
            projectiles.erase(projectiles.begin() + i);
        }
    }
}
void DisplayManager::fireEnemies(Humanoid *player)
{
    Position playerPos = player->getPosition();
    int posx = playerPos.x;
    int posy = playerPos.y;
    Humanoid *e;
    for (int i = 0; i < entities.size(); ++i) 
    {
        e = entities[i];
        e->shoot(posx, posy, false);
    }
}


/**
 * Draws textures on the window where they are currently located
 */
void DisplayManager::refresh(void) {
    // Put textures on screen
    SDL_Rect position;
    SDL_Point size;
    SDL_Texture *texture;
    Entity *e;

    // Map rendering
		renderMap->mapDrawer(renderer);

    for (int i = 0; i < entities.size(); ++i) {
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
