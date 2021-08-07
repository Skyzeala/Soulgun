#ifndef _MOVEMENT_
#define _MOVEMENT_
#define _USE_MATH_DEFINES

//theta = 0 is defined to be right ->
//negative theta is counterclockwise
//positive theta is clockwise
//left is negative x, right is positive x
//up is negative y, down is positive y
//basically opposite from what you might expect, be careful


//comment this out if not debugging
//#define ENTITYDEBUG

#ifdef ENTITYDEBUG
#include <iostream>
#endif
#include <cmath>

struct Position
{
    double x;
    double y;
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
double convertCoordsToRads(int startx, int starty, int endx, int endy);
Movement convertCoordsToMovement(int startx, int starty, int endx, int endy);
Movement convertRadsToMovement(double rads);
double convertMovementToRads(Movement &dir);

//nice clean code
typedef Position (*moveEntityFunc)(double posx, double posy, Movement dir, double speed);
typedef Position (*moveProjectileFunc)(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);

//entity movement functions
Position moveLeft(double posx, double posy, Movement dir, double speed);
Position movePlayer(double posx, double posy, Movement dir, double speed);

//projectile movement functions
Position moveLeft(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveDirection(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
//Position moveTracking(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveSpiral(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveCorkscrew(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveSine(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);
Position moveFlower(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed);


#endif