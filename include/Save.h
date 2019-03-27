#ifndef __SAVE_H__
#define __SAVE_H__

#include "gf2d_vector.h"
#include "Player.h"

//CANNOT HAVE POINTERS IN BIN SAVE FILE
typedef struct Save_S {
	int level;						/**Current level the player is on*/
	Vector2D player_position;		/**Current position of player in world space*/
	Vector4D player_colorShift;		/**Change color of entity if specified*/
	int player_lastDir;				/**Determines if facing left of right (0 = right, 1 = left)*/
	Vector2D player_flip;			/**Determines if flipping sprite horizontally/vertically*/
	int player_onGround;			/**Determines if entity is on the ground or airborne*/
	Vector2D player_velocity;		/**how fast (and what direction) the entity is traveling in*/
	float player_health;			/**Current health of player (30.0/full health by default)*/

	Entity enemy1;					/**pointer to enemy in game world*/
	Entity enemy2;					/**pointer to enemy in game world*/
	Entity enemy3;					/**pointer to enemy in game world*/
}Save;

/**
*@brief - Save game state to bin file
*@param - self - pointer to save struct to save to file
*@param - level - current level to save to file
*@param - player - pointer to player in game world to save state of
*@param - enemy1 - pointer to enemy in game world to save state of
*@param - enemy2 - pointer to enemy in game world to save state of
*@param - enemy3 - pointer to enemy in game world to save state of
*/
void save_file(Save *self, int level, Entity*player, Entity*enemy1, Entity*enemy2, Entity*enemy3 );

/**
*@brief - Load game state from bin file but do not change game (used for initialization)
*@param - self - pointer to save struct to load from file
*@param - level - current level of the game running (NOT THE SAVE'S LEVEL)
*/
void read_file(Save *self, int level);

/**
*@brief - Load game state from bin file and change game based on file
*@param - self - pointer to save struct to load from file
*@param - level - current level of the game running (NOT THE SAVE'S LEVEL)
*@param - player - pointer to player in game world to manipulate from save
*@param - enemy1 - pointer to enemy in game world to save state of
*@param - enemy2 - pointer to enemy in game world to save state of
*@param - enemy3 - pointer to enemy in game world to save state of
*/
void load_file(Save *self, int level, Entity*player, Entity*enemy1, Entity*enemy2, Entity*enemy3 );

#endif