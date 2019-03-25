#ifndef _PROJECTILE_H_
#define _PLAYER_H__

#include "entity.h"
#include "gf2d_vector.h"

/**
*@brief Create a new projectile
*@param type - type of projectile to spawn (MELEE, LONG, SPREAD, RAPID)
*@param velocity - speed and direction of projectile
*@param shooter - entity that is shooting projectile
*@param space - the physics space the projectile should be placed in
*@return pointer to projectile entity
*/
Entity *projectile_new(Proj_Type type, Vector2D velocity, Entity *shooter, Space *space);

/**
*@brief Update position and collision of projectile
*@param self - pointer to projectile entity
*@param space - the physics space the projectile should be placed in
*/
void projectile_update(Entity *self, Space *space);

/** NON-FUNCTIONAL
*@brief Method that runs when projectile touches another body
*@param self - projectile body
*@return other - body that projectile touches
*/
int projectile_bodyTouch(struct Body_S *self, struct Body_S *other, Collision *collision);

/** NON-FUNCTIONAL
*@brief Method that runs when projectile touches another body
*@param self - projectile body
*@return other - body that projectile touches
*/
int projectile_worldTouch(struct Body_S *self, Collision *collision);

#endif