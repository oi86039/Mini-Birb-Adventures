#include <stdio.h>
#include "Save.h"
#include "simple_logger.h"

//Save to save struct and write to file (game -> save -> file)
void save_file(Save *self, int level, Entity*player) {
	//Set struct parameters
	self->level = level;
	self->player_position = player->position;
	//Save to file
	FILE *saveFile = fopen("save/saveFile.bin", "wb");
	fwrite(&(*self), sizeof(struct Save_S), 1, saveFile); //Check how this works...
	fclose(saveFile);

	slog("%i", self->level);
	slog("%f", self->player_position.x);
	slog("%f", self->player_position.y);
}
//Read save struct from file (file -> save -> game)
Save load_file(Save *self) {
	//Load from file
	FILE *saveFile = fopen("save/saveFile.bin", "rb");
	fread(&(*self), sizeof(struct Save_S), 1, saveFile); //Read to contents of save file once into the address of out save struct.
	fclose(saveFile);

	slog("%i", self->level);
	slog("%f", self->player_position.x);
	slog("%f", self->player_position.y);


	//Use file afterwards
}