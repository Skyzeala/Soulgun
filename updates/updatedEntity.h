#ifndef _ENTITY_
#define _ENTITY_

//include image utilities
// #include "projectile.h"
//#include "movement.h"

//this struct and enum will be moved to a more included file so that they can be used almost anywhere in the program

enum EntityType
{
    TERRAIN,
    PLAYER,
    ROBOT,
    HUMAN,
    PROJECTILE
};

struct Position{
    int x;
    int y;
};

struct Movement
{
    bool UP = false;
    bool DOWN = false;
    bool LEFT = false;
    bool RIGHT = false;
};
class Entity{
public:
        Entity();
        ~Entity();
//**********************
        Entity(EntityType selectedEntityType);
        void move(Movement &dir);
//**********************
        //Entity(const Entity &entity);
        /*
        Entity(int health, EntityType entityType,
                int x, int y, int speed, moveEntityFunc entityMove,
                int shootCooldown, moveProjectileFunc projectileMove,
                int textureID);
        */
        //Entity& operator=(const Entity &entity); //for use with soul stealing

        Position getPosition(); //returns x and y position
        int getImage(); //returns TextureID

//        virtual void move(Movement &dir); //move based on movement function pointer
//        virtual Position testMove(Movement &dir); //return what the position would be after it moves, use to test collisions
        // Projectile * shoot(int targetx, int targety, bool soulBullet); //does this work?
        bool damage(int amount); //returns true if entity died

protected:
        int maxHealth;
        int health; //hit points
        EntityType entityType; //human, robot, player, etc
        Position pos;
        //int posx; //cuurent x coordinate
        //int posy; //current y coordinate
        int speed; //movement speed, how much does it move between frames
        //moveEntityFunc entityMove;
        //int shootCooldown; //the current time left before being able to shoot again
        //int shootTimer; //the time between each shot
        //moveProjectileFunc projectileMove;
        int textureID; //change to whatever type needed
        //potentially some sort of radius for the collision hitbox
        //this will probably have to be defined after some testing with graphics
        //collisions should be managed by a function that takes two objects (like two entities or an entity and the map)
        //and determines sizes and distance
};

/*
class Humanoid : public Entity
{
public:
        Projectile * shoot(int targetx, int targety); //returns a list of bullets

}
*/


#endif
