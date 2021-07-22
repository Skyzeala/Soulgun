#ifndef _HUMANOID_
#define _HUMANOID_

#include "entity.h"
#include "projectile.h"

// Time robot will move in one direction before changing
#define ROBOT_MOVE_TIME 1000

// Distance enemy will move toward player
#define ENEMY_MIN_DIST 100

// Distance enemy will move away from player
#define ENEMY_MAX_DIST 512

enum ShootStyle 
{
    SS_SINGLESHOT,
    SS_DOUBLESHOT,
    SS_TRIPLESHOT,
    SS_4WAY,
    SS_4WAYTILT,
    SS_8WAY
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
    Projectile * shoot(int targetx, int targety, bool soulBullet); //returns a list of bullets

    Movement moveDirection; // Last direction moved
    int moveStartTime;      // When humanoid started moving in this direction
    int moveMode;           // If 0 move toward player, if 1 move away
protected:
    int shootCooldown; //the current time left before being able to shoot again
    int shootTimer; //the time between each shot
    ShootStyle shootStyle;
};



#endif 