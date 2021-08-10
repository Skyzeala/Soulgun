#ifndef _HUMANOID_
#define _HUMANOID_

#include <vector>
#include "entity.h"
#include "projectile.h"

// Time enemy will move in one direction before changing
#define ROBOT_MOVE_TIME 500
#define HUMAN_MOVE_TIME 150

// Distance enemy will move toward player
#define ENEMY_MIN_DIST 250

// Distance enemy will move away from player
#define ENEMY_MAX_DIST 450

enum ShootStyle 
{
    SS_SINGLESHOT,
    SS_DOUBLESHOT,
    SS_TRIPLESHOT,
    SS_4WAY,
    SS_4WAYTILT,
    SS_8WAY,
    SS_SPIRAL,
    SS_3INAROW,
    SS_TOTAL
};

class Humanoid : public Entity
{
public:
    Humanoid(); //create generic humanoid
    Humanoid(const Humanoid &humanoid); //create humanoid from copy, useful for soul stealing?
    Humanoid(int health, EntityType entityType,  //create custom humanoid
                double x, double y, double speed, moveEntityFunc entityMove, 
                int shootCooldown, ShootStyle shootStyle, moveProjectileFunc projectileMove, 
                TextureID textureID);
    ~Humanoid();
    void move(Movement &dir); //let the humanoid walk around
    std::vector<Projectile*> shoot(double targetx, double targety, bool soulBullet); //returns a list of bullets to be added to the display manager

protected:
    int shootCooldown; //the current time left before being able to shoot again
    int shootTimer; //the time between each shot
    ShootStyle shootStyle; //what direction and how many projectiles to fire
};



#endif