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
#include "gf2d_collision.h"

typedef enum Proj_Type { MELEE, LONG, SPREAD, RAPID, ENEMY_LONG }Proj_Type;

typedef enum Anim { //Names of all animations
	NONE,
	BIRB_IDLE, BIRB_JUMP, BIRB_FLAP, BIRB_WALK, BIRB_DASH, BIRB_FALL, BIRB_ATTACK, BIRB_SPECIAL_ATTACK, BIRB_HURT,
}Anim;

typedef enum State { //Ability/firing state of player/ enemies
	BIRB_NORMAL, BIRB_FIRE, BIRB_ICE, BIRB_FAST
}State;


//Entity_S - Entity Structure - ENTITY
typedef struct Entity_S
{
	int inUse;	/**flag that states if entity is being used*/
	int lastDir; /**Determines if facing left of right (0 = right, 1 = left)*/
	int onGround; /**Determines if entity is on the ground or airborne*/
	Vector2D scale; /**how big the entity is (1 for normal size)*/
	Vector2D position; /**position of entity in scene*/
	Vector2D velocity; /**how fast (and what direction) the entity is traveling in*/
	Vector2D flip; /**Determines if flipping sprite horizontally/vertically*/

	State state; /**Ability/firing state of player/enemies*/
	Vector4D colorShift; /**Change color of entity if specified*/

	float health; /**Health of entity (if it is destructible)*/

	Sprite * spriteSheet; /**sprites of entity containing all animation frames)*/
	Anim currAnim; /**Name of Animation playing*/
	int loop; /**State if animation should loop or not*/
	float startFrame; /**currentFrame of animation*/
	float currFrame; /**currentFrame of animation*/
	float endFrame; /**What frame to stop on in spritesheet*/

	Shape hitBox; /**Collider or trigger*/
	Body body; /**Physics body*/
	Vector2D offset; /**Hitbox offset*/

	Proj_Type type; /**Type of projectile to fire*/

	float timer; /**Keeps track of time for updates and duration functions*/
	float timeLimit; /**Limit/duration of entity before destruction*/

	void(*update)(struct Entity_S* self); /**update function runs every frame for entity*/
	void(*projectile_update)(struct Entity_S* self, Space *space); /**update function for just projectiles*/
	void(*enemy_update)(struct Entity_S* self, struct Entity_S* player, Space *space); /**update function for just projectiles*/
	void(*anim_change_by_name)(struct Entity_S* self, Anim newAnim, int loop); /**changes animation state by enum*/
	//int(*bodyTouch)(struct Body_S *self, struct Body_S *other, Collision *collision); /**runs when touching another body/entity*/
	//int(*worldTouch)(struct Body_S *self, Collision *collision); /**run when touching the world space*/
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
*@param space - physics space of entity
*/
void entity_update(Entity *ent, Space*space);

//Update All
/**
*@brief Update all entities
*@param space - physics space of entity
*/
void entity_update_all(Space *space);

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