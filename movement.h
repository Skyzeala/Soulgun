#ifndef _MOVEMENT_
#define _MOVEMENT_
#define _USE_MATH_DEFINES

//comment this out if not debugging entity
#define ENTITYDEBUG

#ifdef ENTITYDEBUG
#include <iostream>
#endif
#include <cmath>

struct Position
{
        int x;
        int y;
};

struct Movement
{
    bool left = false;
    bool down = false;
    bool up = false;
    bool right = false;
};

//0 radians is up, positive y is up, positive x is right
//these functions are for convenience
Movement convertCoordsToMovement(int startx, int starty, int endx, int endy);
Movement convertRadsToMovement(double rads);
double convertMovementToRads(Movement &dir);

//nice clean code
typedef Position (*moveEntityFunc)(int posx, int posy, Movement dir, int speed);
typedef Position (*moveProjectileFunc)(int startx, int starty, int posx, int posy, int thetaAim);

//entity movement functions
Position moveLeft(int posx, int posy, Movement dir, int speed);



//projectile movement functions
Position moveLeft(int startx, int starty, int posx, int posy, int thetaAim);



#endif