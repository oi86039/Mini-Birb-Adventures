#ifndef __SAVE_H__
#define __SAVE_H__
#include "Tile.h"

/**
*@brief Create a level transition door at the specified position
*/
Tile *door_new(Vector2D position);

/**
*@brief monitor if door is touched, and load the next level if it is touched (level 1 to level 2)
*/
void door_update();

#endif