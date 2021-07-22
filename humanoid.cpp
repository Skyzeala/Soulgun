

#include "humanoid.h"


using namespace std;

Humanoid::Humanoid() :
    Entity(),
    shootCooldown(0),
    shootTimer(10),
    moveStartTime(0),
    moveMode(0)  
{
}

Humanoid::Humanoid(const Humanoid &humanoid) :
    Entity(humanoid),
    shootCooldown(0),
    shootTimer(shootTimer)
{
}

Humanoid::Humanoid(int health, EntityType entityType, 
                int x, int y, int speed, moveEntityFunc entityMove, 
                int shootCooldown, ShootStyle shootStyle, moveProjectileFunc projectileMove, 
                TextureID textureID) :
    Entity(health, entityType, x, y, speed, entityMove, projectileMove, textureID),
    shootCooldown(0),
    shootTimer(shootTimer),
    moveStartTime(0),
    moveMode(0)    
{
}

Humanoid::~Humanoid()
{
    //todo
}


Projectile * Humanoid::shoot(int targetx, int targety, bool soulBullet)
{
    double aimDirection = atan2((targety-posy), (targetx-posx));
    //make a switch statement for shooting style later
    int texture = (soulBullet ? 1 : 0);
    int lifetime = 100;
    int power = 2;
    Projectile * proj = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
    return proj;
}




