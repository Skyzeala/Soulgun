#ifndef _HUMANOID_
#define _HUMANOID_

#include "entity.h"
#include "projectile.h"

// Time enemy will move in one direction before changing
#define ROBOT_MOVE_TIME 500
#define HUMAN_MOVE_TIME 150

// Distance enemy will move toward player
#define ENEMY_MIN_DIST 250

// Distance enemy will move away from player
#define ENEMY_MAX_DIST 500

enum ShootStyle 
{
    SS_SINGLESHOT,
    SS_DOUBLESHOT,
    SS_TRIPLESHOT,
    SS_4WAY,
    SS_4WAYTILT,
    SS_8WAY,
    SS_SPIRAL
};

class Humanoid : public Entity
{
public:
    Humanoid();
    Humanoid(const Humanoid &humanoid);
    Humanoid(int health, EntityType entityType, 
                int x, int y, int speed, moveEntityFunc entityMove, 
                int shootCooldown, ShootStyle shootStyle, moveProjectileFunc projectileMove, 
                TextureID textureID);
    ~Humanoid();
    void move(Movement &dir);
    Projectile ** shoot(int targetx, int targety, bool soulBullet); //returns a list of bullets

protected:
    int shootCooldown; //the current time left before being able to shoot again
    int shootTimer; //the time between each shot
    ShootStyle shootStyle;
};



#endif 