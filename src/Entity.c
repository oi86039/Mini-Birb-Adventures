#include <stdlib.h>
#include "entity.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"

//Entity Manager Structure to store and recall entities quickly
typedef struct {
	Entity *entityList; /**ArrayList of all entities in scene*/
	Uint32 maxEntities; /**Max limit of entities allowed in scene*/
}EntityManager;

//Make EntityManager static (there can only be one, and it sits running as its own instance.
static EntityManager entityManager = { 0 };

//Destroy Entity Manager
void entity_manager_close() {
	//iterate through all entities
	int i;
	for (i = 0; i < entityManager.maxEntities; i++) {
		//Destroy if there
		entity_free(&entityManager.entityList[i]); //Kill the MEMORY address
	}
	if (entityManager.entityList) { //If there is a list of entities, kill it!
		free(entityManager.entityList);
	}
	entityManager.maxEntities = 0;
	entityManager.entityList = NULL;
}

//Create Entity Manager (Creates this many blank entities for access.)
void entity_manager_init(Uint32 maxEntities)
{
	//If max entity value is not present
	if (!maxEntities)
	{
		slog("cannot allocate zero entities");
		return;
	}
	//Else, allocate memory based on max entities value (error check it too)
	entityManager.entityList = (Entity*)malloc(sizeof(Entity)*maxEntities);
	if (!entityManager.entityList)
	{
		slog("failed to allocate %i entities for system", maxEntities);
	}

	entityManager.maxEntities = maxEntities;

	//Set memory for manipulation
	memset(entityManager.entityList, 0, sizeof(Entity)*maxEntities);
	//slog("memory allocated");

	//if exitting the game, destroy entity Manager
	atexit(entity_manager_close);
}

//Create New Entity
Entity *entity_new() {
	int i;
	for (i = 0; i < entityManager.maxEntities; i++) {
		//Find empty slot in list to use
		if (entityManager.entityList[i].inUse) {
			continue;
		}
		//Set in use flag and make entity.
		entityManager.entityList[i].inUse = 1;
		//slog("Entity is in use");
		entityManager.entityList[i].scale.x = 0.5; //SCALE/ALPHA CANNOT BE 0, ELSE YOU CANNOT SEE IT.
		entityManager.entityList[i].scale.y = 0.5; //SCALE/ALPHA CANNOT BE 0, ELSE YOU CANNOT SEE IT.
		return &entityManager.entityList[i];
	}
	//If entity cannot be created
	slog("all entities in use, cannot provide a new entity"); //Will only trigger if entities are all in use
	return NULL;
}

//Destroy Entity
void entity_free(Entity *self)
{
	if (!self)return;
	if (self->spriteSheet != NULL)
	{
		gf2d_sprite_free(self->spriteSheet);
	}
	memset(self, 0, sizeof(Entity));
	//slog("entity freed");
}

//Draw entity
void entity_draw(Entity *self)
{
	if (!self)return;
	gf2d_sprite_draw(
		self->spriteSheet, //Sprite
		self->position, //Position
		&self->scale,// self->scale, //address of self -> Scale
		NULL, //ScaleCenterPoint
		NULL, //Rotation
		&self->flip, //Flip
		&self->colorShift,	//ColorShift
		self->currFrame); //Frame
	if (&self->hitBox)
		gf2d_shape_draw(self->hitBox, gf2d_color(0, 255, 0, 255)); //DEBUGGING PURPOSES
}

//Draw all entities
void entity_draw_all() {
	int i;
	for (i = 0; i < entityManager.maxEntities; i++) {
		entity_draw(&entityManager.entityList[i]);
	}
}

void entity_update(Entity *ent, Space*space, Entity *player) {
	if ((!ent) || (!ent->inUse))return; //DO not update unless entity is being used or exists.
	ent->currFrame += 0.40;
	if ((ent->currFrame > ent->endFrame)) { //If animation is finished
		if (ent->loop == 1)
			ent->currFrame = ent->startFrame; //Loop animation
		else if (ent->loop == 0)
			ent->currFrame = ent->endFrame; //Stall animation
	}
	//if (ent->update)ent->update(ent); //Run entity's Update function after this
	if (ent->projectile_update)ent->projectile_update(ent, space);
	if (ent->enemy_update)ent->enemy_update(ent,player, space);
}

void entity_update_all(Space *space, Entity *player) {
	int i;
	for (i = 0; i < entityManager.maxEntities; i++) {
		entity_update(&entityManager.entityList[i],space,player);
	}
}

//Change animation
void anim_change_by_number(Entity *self, float start, float end, int loop) {
	self->startFrame = start;
	self->currFrame = start;
	self->endFrame = end;
	self->loop = loop;
}


//END OF OMAR'S CODE