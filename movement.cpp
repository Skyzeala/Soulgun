#include "movement.h"
#include <iostream>

using namespace std;

double convertCoordsToRads(int startx, int starty, int endx, int endy)
{
    double dir = atan2(endy-starty, endx-startx);
    if (dir == -M_PI)
        dir = M_PI;
    return dir;
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
        rads = -M_PI/2;
        if (dir.right)
            rads += M_PI/4;
        if (dir.left)
            rads -= M_PI/4;
    }
    else if (dir.down)
    {
        rads = M_PI/2;
        if (dir.right)
            rads -= M_PI/4;
        if (dir.left)
            rads += M_PI/4;
    }
    else if (dir.right)
        rads = 0;
    else if (dir.left)
        rads = M_PI;
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

Position moveLeft(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    pos.x -= speed;
    return pos;
}

Position moveDirection(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;

    pos.x += cos(direction)*2.5*speed;
    pos.y += sin(direction)*2.5*speed;

    return pos;
}

/* ALMOST works but doesnt actually, hasrouble when the player (thetaAim) goes from -pi to pi and back
Position moveTracking(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = posx;
    pos.y = posy;
    while (direction > M_PI)
        direction -= M_PI*2;
    while (direction <= -M_PI)
        direction += M_PI*2;
    double dif = direction - thetaAim;

    if (abs(dif) <= M_PI/2)
    {
        direction -= 0.1*dif;
        speed += 0.01;
    }
    else if (abs(dif + M_PI*2) <= M_PI/2)
    {
        direction -= 0.1*dif;
        speed += 0.01;
    }
    else if (abs(dif - M_PI*2) <= M_PI/2)
    {
        direction -= 0.1*dif;
        speed += 0.01;
    }

    pos.x += cos(direction)*0.25*speed;
    pos.y += sin(direction)*0.25*speed;

    return pos;
}
*/

//coded with help from https://forum.unity.com/threads/moving-an-object-in-a-spiral-pattern-math-inside.465693/
Position moveSpiral(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;

    double dist = sqrt(pow(posx - startx, 2) + pow(posy - starty, 2));
    if (dist == 0)
        dist = 8;
    dist += 0.17; 
    direction += M_PI/(3*dist);

    pos.x = cos(direction)*dist + startx;
    pos.y = sin(direction)*dist + starty;

    return pos;
}

//first attempt at a sine wave, will spawn a ways away from the entity, probably possible to fix
Position moveCorkscrew(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    pos.x = speed*cos(direction) - 20*sin(speed/8) + startx;
    pos.y = speed*sin(direction) - 20*cos(speed/8) + starty;
    speed += 0.3;

    return pos;
}


//coded with help from https://www.wolframalpha.com/input/?i=plot+%7By%3D-cos%28t%29%2Bt%2Cx%3Dcos%28t%29%2Bt%7D+from+-12+to+12
//it is NOT a perfectly tilted sine wave
Position moveSine(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;
    
    if ((direction < 0 && direction > -M_PI/2) || (direction > M_PI/2 && direction < M_PI))
    {
        //northeast and southwest
        pos.x = speed*cos(direction) - 15*sin(speed/15) + startx;
        pos.y = speed*sin(direction) - 15*sin(speed/15) + starty;
    }
    else
    {
        //northwest and southeast
        pos.x = speed*cos(direction) - 15*cos(speed/15) + startx;
        pos.y = speed*sin(direction) + 15*cos(speed/15) + starty;
    }
    speed += 0.5;

    return pos;
}


//NOT DONE, DOESNT WORK
//coded with help from http://jwilson.coe.uga.edu/EMT668/EMAT6680.2003.fall/Shiver/assignment11/PolarGraphs.htm
Position moveFlower(double startx, double starty, double posx, double posy, double &direction, double thetaAim, double &speed)
{
    Position pos;

    direction += 0.01;
    speed += 0.01;
    double distance = 2*sin(3*speed);

    pos.x = cos(speed)*distance;
    pos.y = sin(speed)*distance;

    return pos;
}