#include "projectile.h"

using namespace std;

Projectile::Projectile() :
    Entity(),
    power(2),
    soulBullet(false),
    startx(0),
    starty(0),
    direction(0)
{
#ifdef ENTITYDEBUG
        cout << "Created default projectile. " << endl;
#endif
}

Projectile::Projectile(const Projectile &projectile) :
    Entity(projectile),
    power(power),
    soulBullet(soulBullet),
    startx(startx),
    starty(starty),
    direction(direction)
{
#ifdef ENTITYDEBUG
        cout << "Created projectile from copy. " << endl;
#endif
}

Projectile::Projectile(int lifetime, int power, int startx, int starty, double direction, 
                        bool soulBullet, moveProjectileFunc projectileMove, int textureID) :
    //Entity(lifetime, ET_PROJECTILE, startx, starty, 0, movePlayer, projectileMove, textureID),
    power(power),
    soulBullet(soulBullet),
    startx(startx),
    starty(starty),
    direction(direction)
{
#ifdef ENTITYDEBUG
        cout << "Created projectile with custom stats. " << endl;
#endif
}

void Projectile::move(Movement &dir)
{
    double thetaAim = convertMovementToRads(dir);
    Position pos = projectileMove(startx, starty, posx, posy, thetaAim);
    posx = pos.x;
    posy = pos.y;
}

Position Projectile::testMove(Movement &dir)
{
    double thetaAim = convertMovementToRads(dir);
    Position pos = projectileMove(startx, starty, posx, posy, thetaAim);
    return pos;
}


/*
-------------------------------------------------

these next two functions are not implemented yet.

-------------------------------------------------
*/
void Projectile::move(double thetaAim)
{
    Position pos = projectileMove(startx, starty, posx, posy, thetaAim);
    posx = pos.x;
    posy = pos.y;
    return;
}
//and this one
Position Projectile::testMove(double thetaAim)
{
    Position pos = projectileMove(startx, starty, posx, posy, thetaAim);
    return pos;
}
//end of unimplemented functions

void Projectile::changeDirection(double amount)
{
#ifdef ENTITYDEBUG
    cout << "Projectile direction changed from " << direction;
#endif
    direction += amount;
    while (direction > M_PI)
        direction -= 2*M_PI;
    while (direction <= -M_PI)
        direction += 2*M_PI;
#ifdef ENTITYDEBUG
    cout << " to " << direction << ". " << endl;
#endif
}

int Projectile::getPower()
{
    return power;
}

double Projectile::getDirection()
{
    return direction;
}

bool Projectile::isSoulBullet()
{
    return soulBullet;
}
