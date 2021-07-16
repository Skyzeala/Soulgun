//implementation of the entity class

//#include "entity.h"
#include "updatedEntity.h"

using namespace std;

Entity::Entity() :
    maxHealth(100),
    health(maxHealth),
    entityType(ROBOT),
//    entityMove(moveLeft),
//    shootCooldown(0),
//    shootTimer(10),
//    projectileMove(moveLeft),
    textureID(ROBOT)
{
#ifdef ENTITYDEBUG
    cout << "Created default entity." << endl;
#endif
    //make these random number generator
    pos.x = 50;
    pos.y = 50;
    speed = 1;
}

//**********************
Entity::Entity(EntityType selectedEntityType){
    if(selectedEntityType == PLAYER){
        maxHealth = 100;
        health = 100;
        entityType = selectedEntityType;
        pos.x = 0;
        pos.y = 0;
        speed = 5;
        textureID = PLAYER;
    }else if(selectedEntityType == HUMAN){
        maxHealth = 50;
        health = 20;
        entityType = selectedEntityType;
        pos.x = 100;
        pos.y = 100;
        speed = 5;
        textureID = HUMAN;
    }
}
//**********************

/*
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

*/

Entity::~Entity(void) {
    // todo
}

/*
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

*/

Position Entity::getPosition()
{
    Position tempPos;
    tempPos.x = pos.x;
    tempPos.y = pos.y;
    return tempPos;
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

    /*
    Position pos = entityMove(posx, posy, dir, speed);
    posx = pos.x;
    posy = pos.y;
    */
//*************************
    if(dir.UP){
        pos.y -= speed;
    }else if(dir.DOWN){
        pos.y += speed;
    }else if(dir.LEFT){
        pos.x -= speed;
    }else if(dir.RIGHT){
        pos.x += speed;
    }
//*************************
#ifdef ENTITYDEBUG
    cout << " to " << posx << ", " << posy;
#endif
}

/*
Position Entity::testMove(Movement &dir)
{
    return entityMove(posx, posy, dir, speed);
}

*/
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

