#include <stdlib.h>
#include "Tile.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_collision.h"

//Tile Manager Structure to store and recall entities quickly
typedef struct {
	Tile *tileList;
	Uint32 maxTiles;
}TileManager;

//Make TileManager static (there can only be one, and it sits running as its own instance.
static TileManager tileManager = { 0 };

//Destroy tile Manager
void tile_manager_close() {
	//iterate through all entities
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		//Destroy if there
		tile_free(&tileManager.tileList[i]); //Kill the MEMORY address
	}
	if (tileManager.tileList) { //If there is a list of entities, kill it!
		free(tileManager.tileList);
	}
	tileManager.maxTiles = 0;
	tileManager.tileList = NULL;
}

//Create tile Manager (Creates this many blank entities for access.)
void tile_manager_init(Uint32 maxTiles)
{
	//If max tile value is not present
	if (!maxTiles)
	{
		slog("cannot allocate zero entities");
		return;
	}
	//Else, allocate memory based on max tile value (error check it too)
	tileManager.tileList = (Tile*)malloc(sizeof(Tile)*maxTiles);
	if (!tileManager.tileList)
	{
		slog("failed to allocate %i entities for system", maxTiles);
	}

	tileManager.maxTiles = maxTiles;

	//Set memory for manipulation
	memset(tileManager.tileList, 0, sizeof(Tile)*maxTiles);
	slog("memory allocated");

	//if exitting the game, destroy tile Manager
	atexit(tile_manager_close);
}

//Create Blank tile
Tile *tile_new() {
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		//Find empty slot in list to use
		if (tileManager.tileList[i].inUse) {
			continue;
		}
		//Set in use flag and make tile.
		tileManager.tileList[i].inUse = 1;
		slog("Tile is in use");
		tileManager.tileList[i].scale.x = 0.5; //SCALE/ALPHA CANNOT BE 0, ELSE YOU CANNOT SEE IT.
		tileManager.tileList[i].scale.y = 0.5; //SCALE/ALPHA CANNOT BE 0, ELSE YOU CANNOT SEE IT.
		return &tileManager.tileList[i];
	}
	//If tile cannot be created
	slog("all tiles in use, cannot provide a new tile"); //Will only trigger if tiles are all in use
	return NULL;
}

///Create an Invisible Normal Tile
Tile *tile_new_invisible(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 1024 * scale.x, 1024 * scale.y);
		return tile;
	}
	else
		return NULL;
}

///Create a Normal Tile
Tile *tile_new_normal(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/bricks2.jpg"); //Load normal tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 1024 * scale.x, 1024 * scale.y); //Sprite of jpg size
		return tile;
	}
	else
		return NULL;
}

//Destroy tile
void tile_free(Tile *self)
{
	if (!self)return;
	if (self->sprite != NULL)
	{
		gf2d_sprite_free(self->sprite);
	}
	memset(self, 0, sizeof(Tile));
}

//Draw tile
void tile_draw(Tile *self)
{
	if (!self)return;
	gf2d_sprite_draw(
		self->sprite, //Sprite
		self->position, //Position
		&self->scale,// self->scale, //address of self -> Scale
		NULL, //ScaleCenterPoint
		NULL, //Rotation
		&self->flip, //Flip
		NULL	//ColorShift
		, 0); //Frame
	gf2d_shape_draw(self->hitBox, gf2d_color(255, 0, 0, 255)); //FOR DEBUGGING PURPOSES
}

//Draw all entities
void tile_draw_all() {
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		tile_draw(&tileManager.tileList[i]);
	}
}

//Add tiles to space
void tile_add_all_to_space(Space *space) {
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		gf2d_space_add_static_shape(space, tileManager.tileList[i].hitBox);
	}
}
//END OF OMAR'S CODE