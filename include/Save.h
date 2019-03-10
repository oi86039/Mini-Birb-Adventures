#ifndef __SAVE_H__
#define __SAVE_H__

#include "gf2d_vector.h"
#include "Player.h"

//CANNOT HAVE POINTERS IN BIN SAVE FILE
typedef struct Save_S {
	int level; /**Current level the player is on*/
	Vector2D player_position; /**Current position of player in world space*/
}Save;

//Save to save struct and write to file (game -> save -> file)
void save_file(Save *self, int level, Entity*player);
//Read save struct from file (file -> save -> game)
Save load_file(Save *self);

#endif