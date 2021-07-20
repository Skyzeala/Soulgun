#ifndef _ENTITY_
#define _ENTITY_

//ENTITY_DEBUG is defined in movement.h

//include image utilities
// #include "projectile.h"
#include "movement.h"
#include "TextureManager.h"

//this struct and enum will be moved to a more included file so that they can be used almost anywhere in the program

enum EntityType
{
        ET_PLAYER,
        ET_ROBOT,
        ET_HUMAN,
        ET_PROJECTILE
};

class Entity
{
public:
        Entity();
        Entity(const Entity &entity);
        Entity(int health, EntityType entityType, 
                int x, int y, int speed, moveEntityFunc entityMove, 
                moveProjectileFunc projectileMove, 
                TextureID textureID);
        Entity& operator=(const Entity &entity); //for use with soul stealing
        ~Entity();

        Position getPosition(); //returns x and y position
        int getImage(); //returns TextureID
        EntityType getType(); //returns Entity ID

        virtual void move(Movement &dir); //move based on movement function pointer
        virtual Position testMove(Movement &dir); //return what the position would be after it moves, use to test collisions
        // Projectile * shoot(int targetx, int targety, bool soulBullet); //does this work?
        bool damage(int amount); //returns true if entity died

protected:
        int maxHealth;
        int health; //hit points
        EntityType entityType; //human, robot, player, etc
        int posx; //cuurent x coordinate
        int posy; //current y coordinate
        int speed; //movement speed, how much does it move between frames
        moveEntityFunc entityMove;
        moveProjectileFunc projectileMove;
        TextureID textureID; //change to whatever type needed
        //potentially some sort of radius for the collision hitbox
        //this will probably have to be defined after some testing with graphics
        //collisions should be managed by a function that takes two objects (like two entities or an entity and the map)
        //and determines sizes and distance
};

#endif