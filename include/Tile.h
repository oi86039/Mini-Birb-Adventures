#ifndef __TILE_H__
#define __TILE_H__

#include "gf2d_sprite.h"
#include "gf2d_collision.h"

//Tile_S - Tile Structure - TILE
typedef struct Tile_S {
	int inUse;			/**flag that states if tile is being used*/
	Vector2D scale;		/**how big the tile is (1 for normal size)*/
	Vector2D position;	/**position of tile in scene*/
	Vector2D flip;		/**Determines if flipping sprite horizontally/vertically*/
	Sprite * sprite;	/**picture to draw of tile*/
	Shape hitBox;		/**Collider or trigger*/
}Tile;

/**
*@brief Create TileManager that keeps track of all entities
*@param maxEntities - max amount of on-screen tiles allowed
*/
void tile_manager_init(Uint32 maxTiles);

/**
*@brief Return a pointer to a new tile
*@return NULL if no tiles or tile manager; else, gives blank tile pointer
*/
Tile *tile_new();

/**
*@brief Return a pointer to a new normal tile with some default properties
*@param position - vector to determine where tile is placed
*@param shape_scale - vector to determine size of tile
*@param img_size - vector depicting size of sprite for tile (x pixels, y pixels)
*@param sprite - sprite of the tile chosen
*@return - pointer to Tile
*/
Tile* tile_new_normal(Vector2D position, Vector2D shape_scale, Sprite* sprite, Vector2D img_size, int collide);

/**
*@brief Return a pointer to a new normal tile with no sprite and some default properties
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*@return - pointer to Tile
*/
Tile *tile_new_invisible(Vector2D position, Vector2D scale);

/**
*@brief Return a pointer to a spike tile that knocks back and hurts the player on contact
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*@return - pointer to Tile
*/
Tile *tile_new_spike(Vector2D position, Vector2D scale);

/**
*@brief Return a pointer to an Exit Door tile that changes levels when touched
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*@return - pointer to Tile
*/
Tile *tile_new_Door(Vector2D position);

/**
*@brief Return a pointer to a fire tile that quickly saps health when touched
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*@return - pointer to Tile
*/
Tile *tile_new_fire(Vector2D position, Vector2D scale);
/**
*@brief Return a pointer to a Heat Area tile that slowly saps health when touched
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*@return - pointer to Tile
*/
Tile *tile_new_heatArea(Vector2D position, Vector2D scale);

/**
*@brief Return a pointer to an gravity tile that slows player movement when touched
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*@return - pointer to Tile
*/
Tile *tile_new_gravity(Vector2D position, Vector2D scale);

/**
*@brief Return a pointer to a bottomless pit tile that kills the player when touched
*@param position - vector to determine where tile is placed
*@param scale - vector to determine size of tile
*@return - pointer to Tile
*/
Tile *tile_new_bottomless(Vector2D position, Vector2D scale);

/**
*@brief Destroys tile for memory freeing
*@param tile to be destroyed (the current instance)
*/
void tile_free(Tile *self);

/**
*@brief Draw or render tile into buffer/screen
*@param tile to be drawn (this current instance)
*/
void tile_draw(Tile *self);

/**
*@brief Draw all entities into buffer/screen
*/
void tile_draw_all();

/**
*@brief Add all tiles in tileManager to the space as static shapes
*@param space - world space to add tiles to.
*/
void tile_add_all_to_space(Space *space);

/**
*@brief Load in level one or level 2
*@param level - which level to load
*@param tile - pointer to tile to load to
*/
void load_tilemap(int level, Tile *tile);

#endif

//eof