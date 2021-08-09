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
                double x, double y, double speed, moveEntityFunc entityMove,
                moveProjectileFunc projectileMove,
                TextureID textureID);
        Entity& operator=(const Entity &entity); //for use with soul stealing
        ~Entity();

        Position getPosition(); //returns x and y position
        TextureID getImage(); //returns TextureID
        EntityType getType(); //returns Entity ID
				void setHitbox(EntityType ID); //Sets hitbox depending on EntityType
				void setHitboxPos(Position entity); //Sets hitbox pos with Position struct
				SDL_Rect * getHitbox(); //Returns hitbox
				bool entityCollision(SDL_Rect * a);

        virtual void move(Movement &dir) = 0; //move based on movement function pointer
        virtual Position testMove(Movement &dir); //return what the position would be after it moves, use to test collisions
        // Projectile * shoot(int targetx, int targety, bool soulBullet); //does this work?
        bool damage(int amount); //returns true if entity died
        void setLocation(Position &newPos);

        // Todo: Protected getters and setters
        Movement moveDirection; // Last direction moved
        int moveStartTime;      // When humanoid started moving in this direction
        int moveAway;           // If true move away from player
protected:
        int maxHealth;
        int health; //hit points
				SDL_Rect hitbox;
        EntityType entityType; //human, robot, player, etc
        double posx; //curent x coordinate
        double posy; //current y coordinate
        double speed; //movement speed, how much does it move between frames
        moveEntityFunc entityMove;
        moveProjectileFunc projectileMove;
        TextureID textureID; //change to whatever type needed
        //potentially some sort of radius for the collision hitbox
        //this will probably have to be defined after some testing with graphics
        //collisions should be managed by a function that takes two objects (like two entities or an entity and the map)
        //and determines sizes and distance
};

#endif
