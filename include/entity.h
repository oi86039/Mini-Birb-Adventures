/* Entity Header file (ENTITY_H = Entity Header) - contains elements every entity should have */
//Player, Enemies, Projectiles, Items, etc.

//Javadoc implementation (for easy copy paste)
/**
*@brief
*@param
*@return
*/

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gf2d_sprite.h"

typedef enum Anim { //Names of all animations
	NONE,
	BIRB_IDLE, BIRB_JUMP, BIRB_FLAP, BIRB_WALK, BIRB_DASH, BIRB_FALL, BIRB_ATTACK, BIRB_SPECIAL_ATTACK, BIRB_HURT,
}Anim;

//Entity_S - Entity Structure - ENTITY
typedef struct Entity_S
{
	int inUse;
	int lastDir; //Determines if facing left of right (0 = right, 1 = left)
	Vector2D scale;
	Vector2D position;
	Vector2D velocity;
	Vector2D flip;

	Sprite * spriteSheet; //spriteSheet (pointer, because you're not making a new one)
	Anim currAnim; //Name of Animation playing
	int loop; //State if animation should loop or not.
	float startFrame; //currentFrame of animation
	float currFrame; //currentFrame of animation
	float endFrame; //What frame to stop on in spritesheet

	Vector2D collider;//Collider or trigger

	//UNCOMMENT these when (and it) they are being used
	void(*update)(struct Entity_S* self); //must include pointer to ourselves
	void(*anim_change_by_name)(struct Entity_S* self, Anim newAnim, int loop);
	void(*think)(struct Entity_S* self); //behavior method
	void(*touch)(struct Entity_S* self, struct Entity_S * other); //Collision with this entity and another entity

}Entity;

//Create Entity Manager
/**
*@brief Create an EntityManager that keeps track of all entities and determines how they're used
*@param maxEntities is the max amount of on-screen enemies allowed (given by game.c)
*/
void entity_manager_init(Uint32 maxEntities);

//Create Entity (constructor)
/**
*@brief Return a pointer to a new entity
*@param NULL if there are no entities, or if there is no entity manager; else, gives a blank entity pointer
*/
Entity *entity_new();

//Destroy Entity
/**
*@brief Destroys entity for memory freeing
*@param Entity to be destroyed (the current instance)
*/
void entity_free(Entity *self);

//Draw
/**
*@brief Draw or render entity into buffer/screen
*@param Entity to be drawn (this current instance)
*/
void entity_draw(Entity *self);

//Draw All
/**
*@brief Draw all entities into buffer/screen
*/
void entity_draw_all();

//Update
/**
*@brief Update position, and vars and frame
*@param Entity to be updated (this current instance)
*/
void entity_update(Entity *ent);

//Update All
/**
*@brief Update all entities
*/
void entity_update_all();

/**
*@brief Change animation of entity and determine whether to loop or not.
*@param Pointer to entity changing animations
*@param Frame to start new animation from
*@param Frame to end new animation on
*@param Flag to determine if animation should loop or not
*/
void anim_change_by_number(Entity *self, float start, float end, int loop);
#endif

//eof