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

class Entity //ABS
{
public:
        Entity(); //construct a default entity
        Entity(int health, EntityType entityType,
                double x, double y, double speed, moveEntityFunc entityMove,
                moveProjectileFunc projectileMove,
                TextureID textureID); //construct a custom entity
        Entity& operator=(const Entity &entity); //for use with soul stealing?
        ~Entity();

        int getHealth();
        Position getPosition(); //returns x and y as a position

        TextureID getImage(); //returns TextureID
        EntityType getType(); //returns Entity ID
        moveProjectileFunc getProjMoveFunc();
        void setProjMoveFunc(moveProjectileFunc func);

				void setHitbox(EntityType ID); //Sets hitbox depending on EntityType
				void setHitboxPos(Position entity); //Sets hitbox pos with Position struct
				SDL_Rect * getHitbox(); //Returns hitbox
				bool entityCollision(SDL_Rect * a); //checks if a hitbox overlaps with the entity's hitbox

        virtual void move(Movement &dir) = 0; //move based on movement function pointer
        virtual Position testMove(Movement &dir); //return what the position would be after it moves, use to test collisions
        bool damage(int amount); //returns true if entity died
        void setLocation(Position &newPos); //change the x and y values of an entity

        // Todo: Protected getters and setters
        //for movement defined in display manager
        Movement moveDirection; // Last direction moved
        int moveStartTime;      // When humanoid started moving in this direction
        int moveAway;           // If true move away from player
protected:
        int maxHealth;
        int health; //hit points
				SDL_Rect hitbox; //must update hitbox position before each use
        EntityType entityType; //human, robot, player, etc
        double posx; //curent x coordinate
        double posy; //current y coordinate
        double speed; //movement speed, how much does it move between frames
        moveEntityFunc entityMove; //not fully implemented, used only with moveDirection
        moveProjectileFunc projectileMove; //define how the entity's projectiles will move after they've been shot
        TextureID textureID; //the image to load to the screen
};

#endif
