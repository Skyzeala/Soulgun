//implementation of the entity class

#include "entity.h"

using namespace std;

Entity::Entity() :
    maxHealth(10),
    health(maxHealth),
    entityType(robot),
    posx(0),
    posy(0),
    speed(1),
    entityMove(moveLeft),
    shootCooldown(0),
    shootTimer(10),
    projectileMove(moveLeft),
    textureID(0)
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
    shootCooldown(0),
    shootTimer(shootTimer),
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
                int shootCooldown, moveProjectileFunc projectileMove, 
                int textureID) :
    maxHealth(health),
    health(health),
    entityType(entityType),
    posx(x),
    posy(y),
    speed(speed),
    entityMove(entityMove),
    shootCooldown(0),
    shootTimer(shootCooldown),
    projectileMove(projectileMove),
    textureID(textureID)
{
#ifdef ENTITYDEBUG
    cout << "Created entity with custom stats." << endl;
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
    cout << "Moved entity from " << posx << ", " << posy;
#endif
    Position pos = entityMove(posx, posy, dir, speed);
    posx = pos.x;
    posy = pos.y;
#ifdef ENTITYDEBUG
    cout << " to " << posx << ", " << posy;
#endif
}

Position Entity::testMove(Movement &dir)
{
    return entityMove(posx, posy, dir, speed);
}

/*
Projectile * Entity::shoot(int targetx, int targety, bool soulBullet)
{
    double aimDirection = atan2((targety-posy), (targetx-posx));
    //make a switch statement for shooting style later
    int texture = (soulBullet ? 1 : 0);
    int lifetime = 100;
    int power = 2;
    Projectile * proj = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
    return proj;
}
*/

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

