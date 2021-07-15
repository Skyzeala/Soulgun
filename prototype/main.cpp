#include "entity.h"

using namespace std;

int main()
{
    Movement dir;
    dir.down = true;

    Entity a = Entity();
    a.move(dir);
    Projectile * b = a.shoot(0,0,false);
    a.damage(5);

    b->move(dir);
    b->changeDirection(M_PI/2);

    delete b;
    b = NULL;
    return 0;
}

