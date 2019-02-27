//Tile class - Contains spikes, 
//Javadoc implementation (for easy copy paste)
/**
*@brief
*@param
*@return
*/

#ifndef __TILE_H__
#define __TILE_H__

#include "gf2d_sprite.h"
#include "gf2d_collision.h"

//Tile_S - Tile Structure - TILE
typedef struct Tile_S
{
	int inUse;
	Vector2D scale;
	Vector2D position;
	Vector2D flip;

	Sprite * sprite; //sprite

	Shape hitBox;//Collider or trigger

}Tile;

//Create Tile Manager
/**
*@brief Create an TileManager that keeps track of all entities and determines how they're used
*@param maxEntities is the max amount of on-screen enemies allowed (given by game.c)
*/
void tile_manager_init(Uint32 maxTiles);

//Create Tile (constructor)
/**
*@brief Return a pointer to a new tile
*@param NULL if there are no entities, or if there is no tile manager; else, gives a blank tile pointer
*/
Tile *tile_new();

//Create Normal Tile (constructor)
/**
*@brief Return a pointer to a new normal tile with some default properties
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*/
Tile *tile_new_normal(Vector2D position, Vector2D scale);

//Create Invisible Normal Tile (constructor)
/**
*@brief Return a pointer to a new normal tile with no sprite and some default properties
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*/
Tile *tile_new_invisible(Vector2D position, Vector2D scale);

//Destroy Tile
/**
*@brief Destroys tile for memory freeing
*@param tile to be destroyed (the current instance)
*/
void tile_free(Tile *self);

//Draw
/**
*@brief Draw or render tile into buffer/screen
*@param tile to be drawn (this current instance)
*/
void tile_draw(Tile *self);

//Draw All
/**
*@brief Draw all entities into buffer/screen
*/
void tile_draw_all();

//Add All to Space
/**
*@brief Add all tiles in tileManager to the space as static shapes
*@param space - world space to add tiles to.
*/
void tile_add_all_to_space(Space *space);

#endif

//eof