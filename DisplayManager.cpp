#include "DisplayManager.h"

/**
 * Initializes the display manager
 * 
 * @param xRenderer External renderer
 * @param xTexture External texture manager
 */
DisplayManager::DisplayManager(SDL_Renderer *xRenderer, TextureManager *xTexture) {
    renderer = xRenderer;
    txMan = xTexture;
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
void DisplayManager::addEntity(Entity *entity) {
    entities.push_back(entity);
}

/**
 * Removes an entity from the manager
 * 
 * @param entity Pointer to an entity that is being managed
 */
void DisplayManager::removeEntity(Entity *entity) {
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
        Entity *e = entities[i];
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
	    player = new Humanoid(100, ET_PLAYER, MAP_WIDTH / 2, MAP_HEIGHT / 2, 1, movePlayer, 0, SS_SINGLESHOT, moveLeft, TX_PLAYER);

        addEntity(player);
        return player;
    }

    Position pos = player->getPosition();

    // Have enemies encircle the player
    float unitCircle = 2 * M_PI;
    float total = (MIN_HUMAN + MIN_ROBOT);
    for (float i = 0; i <= unitCircle; i += (unitCircle / total)) {
        int x = pos.x + cos(i) * MIN_DIST;
        int y = pos.y + sin(i) * MIN_DIST;

        if (!isNearEnemy(x, y, 0)) {
            Humanoid *e = new Humanoid(100, type, x, y, 1, moveLeft, 0, SS_SINGLESHOT, moveLeft, static_cast<TextureID>(type));
            addEntity(e);

            return e;
        }
    }

    return NULL;
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

/**
 * Draws textures on the window where they are currently located
 */
void DisplayManager::refresh(void) {
    // Put textures on screen
    SDL_Rect position;
    SDL_Point size;
    SDL_Texture *texture;
    Entity *e;

    // Map should draw the portion of its texture onscreen that it needs to
    texture = txMan->getTexture(TX_TERRAIN);
    size = txMan->getDimensions(TX_TERRAIN);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

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