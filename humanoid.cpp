

#include "humanoid.h"
#include <iostream>

using namespace std;

Humanoid::Humanoid() :
    Entity(),
    shootCooldown(0),
    shootTimer(10),
    shootStyle(SS_SINGLESHOT)
{
}

Humanoid::Humanoid(const Humanoid &humanoid) :
    Entity(humanoid),
    shootCooldown(0),
    shootTimer(shootCooldown),
    shootStyle(shootStyle)
{
}

Humanoid::Humanoid(int health, EntityType entityType, 
                int x, int y, int speed, moveEntityFunc entityMove, 
                int shootCooldown, ShootStyle shootStyle, moveProjectileFunc projectileMove, 
                TextureID textureID) :
    Entity(health, entityType, x, y, speed, entityMove, projectileMove, textureID),
    shootCooldown(0),
    shootTimer(shootCooldown),
    shootStyle(shootStyle)
{
}

Humanoid::~Humanoid()
{
    //todo
}

void Humanoid::move(Movement &dir)
{
#ifdef ENTITYDEBUG
    bool printSecondHalfOfDebug;
    if (dir.right || dir.left || dir.up || dir.down)  //only print if its going to move
    {
        cout << "Moved entity from (" << posx << ", " << posy;
        printSecondHalfOfDebug = true;
    }
#endif
    Position pos = entityMove(posx, posy, dir, speed);
    posx = pos.x;
    posy = pos.y;
    moveDirection = dir;
    shootCooldown -=1;
#ifdef ENTITYDEBUG
    if (printSecondHalfOfDebug)
        cout << ") to (" << posx << ", " << posy << ") \n";
#endif
}


//slightly unfinished, may not need to be finished
Projectile ** Humanoid::shoot(int targetx, int targety, bool soulBullet)
{
    double aimDirection = atan2((targety-posy), (targetx-posx));
    TextureID texture = (soulBullet ? TX_BULLET : TX_BULLET); //change when new texture is available
    int lifetime = 500;
    int power = 1;
    Projectile ** proj = nullptr;
    if (shootCooldown <= 0)
    {
        switch (shootStyle)
        {
            case SS_SINGLESHOT:
                proj = new Projectile*[1];
                proj[0] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                break;
            case SS_DOUBLESHOT:
                proj = new Projectile*[2];
                aimDirection -= M_PI/8;
                proj[0] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                aimDirection += M_PI/4;
                proj[1] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                break;
            case SS_TRIPLESHOT:
                proj = new Projectile*[3];
                aimDirection -= M_PI/6;
                proj[0] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                aimDirection += M_PI/6;
                proj[1] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                aimDirection += M_PI/6;
                proj[2] = new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture);
                break;
            case SS_4WAY:
                break;
            case SS_4WAYTILT:
                break;
            case SS_8WAY:
                break;
            case SS_SPIRAL:
                break;
            default:
                cout << "no type" << endl;
                break;
        }
        shootCooldown = shootTimer;
    }
    return proj;
}




