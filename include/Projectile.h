#ifndef _PROJECTILE_H_
#define _PLAYER_H__

#include "entity.h"
#include "gf2d_vector.h"

Entity projectile_new(Vector2D spawn_pos, Vector2D velocity);

#endif