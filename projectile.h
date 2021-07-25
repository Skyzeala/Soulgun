#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "entity.h"
#include "movement.h"


class Projectile : public Entity
{
public:
        Projectile();
        Projectile(const Projectile &projectile);
        Projectile(int lifetime, int power, int startx, int starty, double direction, bool soulBullet, moveProjectileFunc projectileMove, TextureID textureID);

        void move(Movement &dir); //not the ideal movement but will work
        Position testMove(Movement &dir);
        bool move(double thetaAim); //not implemented yet but use these instead with the player location
        Position testMove(double thetaAim); //these could be changed to accept a Position instead

        void changeDirection(double amount); //add radians to current direction
        //designed to be used for ease of multi bullet creation along with the copy constructor
        //could potentially be used for rebounding off walls, but this is not expected and wont work with all movement functions

        int getPower();
        double getDirection();
        bool isSoulBullet(); //returns the value of soulBullet, it is a "getter" function but the word "get" didnt make sense
protected:
        int power; //the number of health points the projectile will do upon contact
        bool soulBullet; //true if the bullet used will take a humans soul

        int startx;
        int starty;
        double direction; //radians for the direction the bullet is facing/aimed at
};
#endif