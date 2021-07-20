//implementation of the entity class

#include "entity.h"

using namespace std;

Entity::Entity() :
    maxHealth(10),
    health(maxHealth),
    entityType(ET_ROBOT),
    posx(0),
    posy(0),
    speed(1),
    entityMove(moveLeft),
    projectileMove(moveLeft),
    textureID(TX_ROBOT)
{
#ifdef ENTITYDEBUG
    cout << "Created default entity." << endl;
#endif
}

Entity::Entity(const Entity &entity) :
    maxHealth(maxHealth),
    health(maxHealth),
    entityType(entityType),
    posx(posx),
    posy(posy),
    speed(speed),
    entityMove(entityMove),
    projectileMove(projectileMove),
    textureID(textureID)
{
#ifdef ENTITYDEBUG
    cout << "Created entity from copy." << endl;
#endif
}

Entity::~Entity(void) {
    // todo
}

Entity::Entity(int health, EntityType entityType, 
                int x, int y, int speed, moveEntityFunc entityMove, 
                moveProjectileFunc projectileMove, 
                TextureID textureID) :
    maxHealth(health),
    health(health),
    entityType(entityType),
    posx(x),
    posy(y),
    speed(speed),
    entityMove(entityMove),
    projectileMove(projectileMove),
    textureID(textureID)
{
#ifdef ENTITYDEBUG
    cout << "Created entity with custom stats." << endl;
    cout << "Type is: " << (entityType == ET_PLAYER ? "player" : "npc") << endl;
    cout << "Position: " << posx << ", " << posy << endl;
    cout << "speed: " << speed << endl;
#endif
}


Position Entity::getPosition()
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    return pos;
}

int Entity::getImage()
{
    return textureID;
}

void Entity::move(Movement &dir)
{
#ifdef ENTITYDEBUG
    cout << "Moved entity from (" << posx << ", " << posy;
#endif
    Position pos = entityMove(posx, posy, dir, speed);
    posx = pos.x;
    posy = pos.y;
#ifdef ENTITYDEBUG
    cout << ") to (" << posx << ", " << posy << ") \n";
#endif
}

Position Entity::testMove(Movement &dir)
{
    return entityMove(posx, posy, dir, speed);
}

bool Entity::damage(int amount)
{
    health -= amount;
#ifdef ENTITYDEBUG
        cout << "Entity took " << amount << " damage. " << endl;
#endif
    if (health <= 0)
    {
#ifdef ENTITYDEBUG
        cout << "Entity died." << endl;
#endif
        return true;
    }
    else
        return false;
}

