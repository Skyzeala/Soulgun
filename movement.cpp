#include "movement.h"
#include <iostream>

using namespace std;

double convertCoordsToRads(int startx, int starty, int endx, int endy)
{
    return atan2(endy-starty, endx-startx);
}

Movement convertCoordsToMovement(int startx, int starty, int endx, int endy)
{ //doesnt call convertRadsToMovement because thats an extra copy of the movement struct
    double rads = atan2(endy-starty, endx-startx);
    Movement dir;
    if (abs(rads) > M_PI*4/6)
        dir.down = true;
    if (abs(rads) < M_PI*2/6)
        dir.up = true;
    if (rads < M_PI*5/6 && rads > M_PI*1/6)
        dir.right = true;
    if (rads > -M_PI*5/6 && rads < -M_PI*1/6)
        dir.left = true;
    return dir;
}

Movement convertRadsToMovement(double rads)
{
    Movement dir;
    if (abs(rads) > M_PI*4/6)
        dir.down = true;
    if (abs(rads) < M_PI*2/6)
        dir.up = true;
    if (rads < M_PI*5/6 && rads > M_PI*1/6)
        dir.right = true;
    if (rads > -M_PI*5/6 && rads < -M_PI*1/6)
        dir.left = true;
    return dir;
}

double convertMovementToRads(Movement &dir)
{
    double rads = -M_PI; //default value, will be returned if conversion failed
    if (dir.up)
    {
        rads = 0;
        if (dir.right)
            rads += M_PI/4;
        if (dir.left)
            rads -= M_PI/4;
    }
    else if (dir.down)
    {
        rads = M_PI;
        if (dir.right)
            rads -= M_PI/4;
        if (dir.left)
            rads = -M_PI*3/4;
    }
    else if (dir.right)
        rads = M_PI/2;
    else if (dir.left)
        rads = -M_PI/2;
    return rads;
}


//entity movement

Position moveLeft(double posx, double posy, Movement dir, double speed)
{
    Position pos;
    pos.x = posx - speed;
    pos.y = posy;
    return pos;
}

Position movePlayer(double posx, double posy, Movement dir, double speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    if (dir.left)
        pos.x -= speed;
    if (dir.up)
        pos.y -= speed;
    if (dir.down)
        pos.y += speed;
    if (dir.right)
        pos.x += speed;
    return pos;
}


//projectile movement, speed decided by each function itself?

Position moveLeft(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    pos.x -= speed;
    return pos;
}

Position moveDirection(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;

    pos.x += cos(direction)*speed;
    pos.y += sin(direction)*speed;

    return pos;
}

//coded with help from https://forum.unity.com/threads/moving-an-object-in-a-spiral-pattern-math-inside.465693/
Position moveSpiral(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double speed)
{
    Position pos;

    double dist = sqrt(pow(posx - startx, 2) + pow(posy - starty, 2));
    dist *= 1.00001;
    dist += 0.15; 
    direction += M_PI/(5*dist);


    pos.x = cos(direction)*dist + startx;
    pos.y = sin(direction)*dist + starty;

    return pos;
}