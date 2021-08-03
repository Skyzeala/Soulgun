

#include "humanoid.h"

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
                double x, double y, double speed, moveEntityFunc entityMove, 
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
    if (dir.up || dir.down || dir.left || dir.right)
        moveDirection = dir;
    shootCooldown -=1;
#ifdef ENTITYDEBUG
    if (printSecondHalfOfDebug)
        cout << ") to (" << posx << ", " << posy << ") \n";
#endif
}


//unfinished, only singleshot works
//how to watch the proj pointer in vscode with gdb: (Projectile*[9]) *proj
//will convert this over to using vectors in the future
vector<Projectile*> Humanoid::shoot(double targetx, double targety, bool soulBullet)
{
    double aimDirection;
    if (entityType != ET_PLAYER) 
        aimDirection = atan2((targety-posy), (targetx-posx));
    else
        aimDirection = convertMovementToRads(moveDirection);
    TextureID texture = (soulBullet ? TX_BULLET : TX_BULLET); //change when new texture is available
    int lifetime = 500;
    int power = 1;
    vector<Projectile*> proj;
    if (shootCooldown <= 0)
    {
        switch (shootStyle)
        {
            case SS_SINGLESHOT:
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                break;
            case SS_DOUBLESHOT:
                aimDirection -= M_PI/15;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/7.5;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                break;
            case SS_TRIPLESHOT:
                aimDirection -= M_PI/12;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/12;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/12;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                break;
            case SS_4WAY:
                aimDirection = 0;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/2;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/2;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/2;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                break;
            case SS_4WAYTILT:
                aimDirection = M_PI/4;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/2;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/2;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                aimDirection += M_PI/2;
                proj.push_back(new Projectile(lifetime, power, posx, posy, aimDirection, soulBullet, projectileMove, texture));
                break;
            case SS_8WAY:
                break;
            case SS_SPIRAL:
                break;
            default:
                break;
        }
        shootCooldown = shootTimer;
    }
    return proj;
}




