#include <stdio.h>
#include "Save.h"
#include "simple_logger.h"
#include "Player.h"
#include "gui.h"

//Save to save struct and write to file (game -> save -> file)
void save_file(Save *self, int level, Entity*player, Entity*enemy1, Entity*enemy2, Entity*enemy3) {
	//Set struct parameters
	self->level = level;
	self->player_position = player->position;
	self->player_colorShift = player->colorShift;
	self->player_lastDir = player->lastDir;
	self->player_flip = player->flip;
	self->player_onGround = player->onGround;
	self->player_velocity = player->velocity;
	self->player_health = player->health;

	self->enemy1 = *enemy1;
	self->enemy2 = *enemy2;
	self->enemy3 = *enemy3;

	//Save to file
	FILE *saveFile = fopen("save/saveFile.birbSav", "wb");
	fwrite(&(*self), sizeof(struct Save_S), 1, saveFile); //Check how this works...
	fclose(saveFile);

	//slog("Save");
	//slog("%f", self->player_health);
	//slog("Player");
	//slog("%f", player->health);
}
//Read save struct from file (file -> save -> game)
void read_file(Save *self, int level) {
	//Load from file
	FILE *saveFile = fopen("save/saveFile.birbSav", "rb");
	fread(&(*self), sizeof(struct Save_S), 1, saveFile);
	fclose(saveFile);

	//slog("%i", self->level);
	//Use file afterwards
}
//Read save struct from file (file -> save -> game) and change game
void load_file(Save *self, int level, Entity*player, Entity*enemy1, Entity*enemy2, Entity*enemy3) {
	//Load from file
	FILE *saveFile = fopen("save/saveFile.birbSav", "rb");
	fread(&(*self), sizeof(struct Save_S), 1, saveFile);
	fclose(saveFile);

	if (level != self->level) {
		if (self->level == 1) level1();
		else if (self->level == 2) level2();
		else slog("Invalid level");
	}

	//Starting properties when object is made
	vector2d_copy(player->position, self->player_position); //Copies current position into player position
	player->colorShift = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	player->lastDir = self->player_lastDir;
	player->flip = self->player_flip;
	player->onGround = self->player_onGround;
	player->velocity = self->player_velocity;
	player->health = self->player_health;
	gui_set_health(player->health);
	//player_health_set(player, health);

	enemy1->position = self->enemy1.position;
	enemy1->timer = self->enemy1.timer;
	enemy2->position = self->enemy2.position;
	enemy2->timer = self->enemy2.timer;
	enemy3->position = self->enemy3.position;
	enemy3->timer = self->enemy3.timer;

	//slog("%i", self->level);
	//slog("Save");
	//slog("%f", self->player_health);
	//slog("Player");
	//slog("%f", player->health);
	//Use file afterwards
}