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
		tile->hitBox.id = 1;
		return tile;
	}
	else
		return NULL;
}

///Create a Normal Tile
Tile *tile_new_normal(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/bricks2.png"); //Load normal tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 1024 * scale.x, 1024 * scale.y); //Sprite of jpg size
		tile->hitBox.id = 2;
		return tile;
	}
	else
		return NULL;
}
//Create a Spike Tile
Tile *tile_new_spike(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/Spikes.png"); //Load spike tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 20 * scale.x, 5 * scale.y); //Sprite of jpg size
		tile->hitBox.id = 3;
		return tile;
	}
	else
		return NULL;
}
//Create a Heat Area Tile
Tile *tile_new_heatArea(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/Heat Area.png"); //Load spike tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 400 * scale.x, 400 * scale.y); //Sprite of jpg size
		tile->hitBox.id = 4;
		return tile;
	}
	else
		return NULL;
}

//Create a Heat Area Tile
Tile *tile_new_fire(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/Fire.png"); //Load spike tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 482 * scale.x, 594 * scale.y); //Sprite of jpg size
		tile->hitBox.id = 5;
		return tile;
	}
	else
		return NULL;
}

//Create a Gravity Tile
Tile *tile_new_gravity(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/Gravity.png"); //Load spike tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 400 * scale.x, 400 * scale.y); //Sprite of jpg size
		tile->hitBox.id = 6;
		return tile;
	}
	else
		return NULL;
}

//Create a Heat Area Tile
Tile *tile_new_bottomless(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/Bottomless.png"); //Load spike tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 400 * scale.x, 518 * scale.y); //Sprite of jpg size
		tile->hitBox.id = 7;
		return tile;
	}
	else
		return NULL;
}

//Create Exit Door
Tile *tile_new_Door(Vector2D position, Vector2D scale) {
	Tile *tile = tile_new();
	if (tile) {
		tile->sprite = gf2d_sprite_load_image("images/SciFi_Door_Pixel.png"); //Load spike tile sprite
		tile->scale = scale;
		tile->position = position;
		tile->hitBox = gf2d_shape_rect(position.x, position.y, 32 * scale.x, 32 * scale.y); //Sprite of jpg size
		tile->hitBox.id = 10;
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

//Draw all tiles
void tile_draw_all() {
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		tile_draw(&tileManager.tileList[i]);
	}
}

//Clear all tiles (for level loading)
void tile_manager_clear() {
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		tile_free(&tileManager.tileList[i]);
	}
}

//Add tiles to space
void tile_add_all_to_space(Space *space) {
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		gf2d_space_add_static_shape(space, tileManager.tileList[i].hitBox);
	}
}

//Load tilemap
void load_tilemap(int level, Tile *tile) {
	if (level == 1 || !level) { //If level is null, load level 1 by default
		//create tilemap (Put in separate files)
		tile = tile_new_invisible(vector2d(0, 520), vector2d(0.15, 0.2));
		tile = tile_new_bottomless(vector2d(153.75, 680), vector2d(0.3, 0.1));
		tile = tile_new_invisible(vector2d(0, 290), vector2d(0.12, 0.01));
		tile = tile_new_spike(vector2d(153.6, 390), vector2d(2, 2));
		tile = tile_new_invisible(vector2d(153.6, 400), vector2d(0.12, 0.01));
		tile = tile_new_invisible(vector2d(210, 190), vector2d(0.06, 0.01));
		tile = tile_new_invisible(vector2d(270.44, 650), vector2d(0.20, 0.11)); //Fridge Door
		tile = tile_new_heatArea(vector2d(270.44, 70), vector2d(0.5, 0.2)); //Fridge Door
		tile = tile_new_gravity(vector2d(270.44, 300), vector2d(0.5, 0.6)); //Fridge Door
		tile = tile_new_fire(vector2d(276, 160), vector2d(0.05, 0.05)); //Fridge Door
		tile = tile_new_fire(vector2d(306, 160), vector2d(0.05, 0.05)); //Fridge Door
		tile = tile_new_fire(vector2d(336, 160), vector2d(0.05, 0.05)); //Fridge Door
		tile = tile_new_fire(vector2d(366, 160), vector2d(0.05, 0.05)); //Fridge Door
		tile = tile_new_fire(vector2d(396, 160), vector2d(0.05, 0.05)); //Fridge Door
		tile = tile_new_fire(vector2d(426, 160), vector2d(0.05, 0.05)); //Fridge Door
		tile = tile_new_invisible(vector2d(270.44, 190), vector2d(0.20, 0.11));
		tile = tile_new_invisible(vector2d(270.44, 190), vector2d(0.01, 0.35));
		tile = tile_new_invisible(vector2d(270.44, 540), vector2d(0.15, 0.01));
		tile = tile_new_invisible(vector2d(330, 400), vector2d(0.15, 0.01));
		tile = tile_new_invisible(vector2d(474, 400), vector2d(0.01, 0.3));
		tile = tile_new_invisible(vector2d(484, 450), vector2d(0.25, 0.4));
		tile = tile_new_invisible(vector2d(543, 270), vector2d(0.19, 0.04)); //Oven Cap
		tile = tile_new_invisible(vector2d(564, 0), vector2d(0.15, 0.265)); //Oven Vent
		tile = tile_new_invisible(vector2d(740, 230), vector2d(0.45, 0.1)); //Cabinet
		tile = tile_new_invisible(vector2d(804.25, 450), vector2d(0.05, 0.4)); //Chairs
		tile = tile_new_invisible(vector2d(856.2, 650), vector2d(0.09, 0.09)); //Chairs
		tile = tile_new_invisible(vector2d(986, 470), vector2d(0.03, 0.11)); //Table 	
		tile = tile_new_invisible(vector2d(904, 450), vector2d(0.19, 0.02)); //Table Top 	
		tile = tile_new_invisible(vector2d(1057.84, 650), vector2d(0.09, 0.09)); //Chairs
		tile = tile_new_invisible(vector2d(1150, 450), vector2d(0.05, 0.4)); //Chairs
		tile = tile_new_Door(vector2d(1150, 405), vector2d(1.5, 1.5)); //Door
	}
	else if (level == 2) {
		tile = tile_new_invisible(vector2d(0, 1), vector2d(0.32, 0.11)); //Cabinets above waiter
		tile = tile_new_invisible(vector2d(1, 112.64), vector2d(0.32, 0.11)); //Cabinets above waiter
		tile = tile_new_invisible(vector2d(45, 570), vector2d(0.08, 0.03)); //Bottom start
		tile = tile_new_invisible(vector2d(115, 360), vector2d(0.05, 0.13)); //Waiter stage-left arm
		tile = tile_new_invisible(vector2d(214, 290), vector2d(0.07, 0.07)); //Waiter head
		tile = tile_new_invisible(vector2d(166.2, 360), vector2d(0.157, 0.4)); //Waiter body
		tile = tile_new_invisible(vector2d(40, 405), vector2d(0.17, 0.01)); //Waiter tray
		tile = tile_new_spike(vector2d(40, 394.76), vector2d(2, 2)); //Waiter spikes test
		tile = tile_new_invisible(vector2d(325, 360), vector2d(0.05, 0.13)); //Waiter stage-right arm
		tile = tile_new_invisible(vector2d(400, 230), vector2d(0.32, 0.03)); //Top of mantle place
		tile = tile_new_invisible(vector2d(435, 260.72), vector2d(0.25, 0.03)); //Bottom of mantle place
		//Candelabra
		tile = tile_new_invisible(vector2d(428, 121), vector2d(0.01, 0.05)); //Candle 1
		tile = tile_new_invisible(vector2d(464, 121), vector2d(0.01, 0.05)); //Candle 2
		tile = tile_new_invisible(vector2d(499, 121), vector2d(0.01, 0.05)); //Candle 3
		tile = tile_new_invisible(vector2d(428, 171), vector2d(0.08, 0.01)); //Top holder
		tile = tile_new_invisible(vector2d(464, 182), vector2d(0.01, 0.04)); //Middle support
		tile = tile_new_invisible(vector2d(464, 182), vector2d(0.01, 0.04)); //Middle support
		tile = tile_new_invisible(vector2d(450, 220), vector2d(0.04, 0.01)); //Bottom Base
		//Candelabra 2
		tile = tile_new_invisible(vector2d(608, 121), vector2d(0.01, 0.05)); //Candle 1
		tile = tile_new_invisible(vector2d(644, 121), vector2d(0.01, 0.05)); //Candle 2
		tile = tile_new_invisible(vector2d(679, 121), vector2d(0.01, 0.05)); //Candle 3
		tile = tile_new_invisible(vector2d(608, 171), vector2d(0.08, 0.01)); //Top holder
		tile = tile_new_invisible(vector2d(644, 182), vector2d(0.01, 0.04)); //Middle support
		tile = tile_new_invisible(vector2d(644, 182), vector2d(0.01, 0.04)); //Middle support
		tile = tile_new_invisible(vector2d(630, 220), vector2d(0.04, 0.01)); //Bottom Base

		tile = tile_new_invisible(vector2d(400, 380), vector2d(0.32, 0.03)); //Top of china cabinet
		tile = tile_new_invisible(vector2d(420, 410), vector2d(0.013, 0.11)); //Plate 1
		tile = tile_new_invisible(vector2d(460, 410), vector2d(0.013, 0.08)); //Plate 2
		tile = tile_new_invisible(vector2d(500, 410), vector2d(0.013, 0.11)); //Plate 3
		tile = tile_new_invisible(vector2d(540, 410), vector2d(0.013, 0.08)); //Plate 4
		tile = tile_new_invisible(vector2d(580, 410), vector2d(0.013, 0.11)); //Plate 5
		tile = tile_new_invisible(vector2d(620, 410), vector2d(0.013, 0.08)); //Plate 6
		tile = tile_new_invisible(vector2d(660, 410), vector2d(0.013, 0.11)); //Plate 7
		tile = tile_new_invisible(vector2d(380, 620), vector2d(0.32, 0.1)); //Bottom of china cabinet

		tile = tile_new_invisible(vector2d(800, 415), vector2d(0.32, 0.15)); //Tablecloth
		tile = tile_new_invisible(vector2d(953.6, 568.6), vector2d(0.02, 0.19)); //Table middle
		//Chandelier
		tile = tile_new_invisible(vector2d(962.824, 0), vector2d(0.007, 0.15)); //Top Cord
		tile = tile_new_invisible(vector2d(828, 151), vector2d(0.013, 0.07)); //Candle 1
		tile = tile_new_invisible(vector2d(894, 151), vector2d(0.013, 0.07)); //Candle 2
		tile = tile_new_invisible(vector2d(959, 151), vector2d(0.013, 0.07)); //Candle 3
		tile = tile_new_invisible(vector2d(1025, 151), vector2d(0.013, 0.07)); //Candle 4
		tile = tile_new_invisible(vector2d(1090, 151), vector2d(0.013, 0.07)); //Candle 5
		tile = tile_new_invisible(vector2d(818, 221.48), vector2d(0.29, 0.015)); //Candle holder (top)
		tile = tile_new_invisible(vector2d(908, 236), vector2d(0.013, 0.06)); //Candle 1 bottom
		tile = tile_new_invisible(vector2d(959, 236), vector2d(0.013, 0.06)); //Candle 2 bottom
		tile = tile_new_invisible(vector2d(1009, 236), vector2d(0.013, 0.06)); //Candle 3 bottom
		tile = tile_new_invisible(vector2d(893, 295), vector2d(0.14, 0.015)); //Candle holder (bottom)
		tile = tile_new_invisible(vector2d(918.5, 310.36), vector2d(0.09, 0.015)); //Candle holder (bottom-most)
	}
	else slog("invalid level value");
}

//Destroy Tilemap
void destroy_tilemap(Space *space) {
	//Free all tiles
	int i;
	for (i = 0; i < tileManager.maxTiles; i++) {
		tile_free(&tileManager.tileList[i]);
	}
	gf2d_space_free(space);
}

//END OF OMAR'S CODE