#include <stdio.h>
#include "Save.h"
#include "simple_logger.h"
#include "Player.h"

//Save to save struct and write to file (game -> save -> file)
void save_file(Save *self, int level, Entity*player) {
	//Set struct parameters
	self->level = level;
	self->player_health = player->health;
	self->player_state = player->state;
	self->player_position = player->position;
	//Save to file
	FILE *saveFile = fopen("save/saveFile.birbSav", "wb");
	fwrite(&(*self), sizeof(struct Save_S), 1, saveFile); //Check how this works...
	fclose(saveFile);

	slog("%i", self->level);
	slog("%f", self->player_health);
	//slog("%s", self->player_state);
	slog("%f", self->player_position.x);
	slog("%f", self->player_position.y);
}
//Read save struct from file (file -> save -> game)
void read_file(Save *self, int level) {
	//Load from file
	FILE *saveFile = fopen("save/saveFile.birbSav", "rb");
	fread(&(*self), sizeof(struct Save_S), 1, saveFile); //Read to contents of save file once into the address of out save struct.
	fclose(saveFile);

	slog("%i", self->level);

	//Use file afterwards
}
//Read save struct from file (file -> save -> game) and change game
void load_file(Save *self, int level, Entity*player) {
	//Load from file
	FILE *saveFile = fopen("save/saveFile.birbSav", "rb");
	fread(&(*self), sizeof(struct Save_S), 1, saveFile); //Read to contents of save file once into the address of out save struct.
	fclose(saveFile);

	if (level != self->level) {
		if (self->level == 1) level1();
		else if (self->level == 2) level2();
		else slog("Invalid level");
	}
	
	player->position = self->player_position;
	player->health = self->player_health;
	player_health_change(player, 0);
	player->state = self->player_state;

	slog("%i", self->level);
	slog("%f", self->player_health);
	//slog("%s", self->player_state);
	slog("%f", self->player_position.x);
	slog("%f", self->player_position.y);
	//Use file afterwards
}