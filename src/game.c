#include <SDL.h>
#include <stdio.h>
#include "entity.h"
#include "Tile.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gf2d_collision.h"
#include "simple_logger.h"
#include "Player.h"

//GAME.C
//THE ACTUAL GAME CODE THAT RUNS WHEN THE EXE RUNS.
//UTILIZES ALL ENGINE FILES

int main(int argc, char * argv[])
{
	//Read save information
	long stringSize;
	char *buffer;
	int level; //Level to load player into
	Vector2D pos; //Position to spawn player in level
	FILE *saveFile; //File pointer to save file

	saveFile = fopen("save/saveFile.birbsav", "r");
	if (saveFile == NULL) {
		slog("Save file not found. Starting Level 1..");
		level1();
		return 0;
	}
	//Find char count
	fseek(saveFile, 0L, SEEK_END); //Read through file to find memory size
	stringSize = ftell(saveFile);
	rewind(saveFile); //Start at beginning
	//Allocate char array mem
	buffer = calloc(1, stringSize + 1); //Char allocate, start at 1 and index
	if (!buffer){
		slog("failed to allocate char array memory. Starting Level 1..");
		fclose(saveFile);
		level1();
		return 0;
	}
	//Store into char array
	if (1 != fread(buffer, stringSize, 1, saveFile)) { //If read fails
		slog("failed to read save data. Starting Level 1..");
		fclose(saveFile);
		level1();
		return 0;
	}
	fclose(saveFile);
	//Read Level
	slog("%s", buffer);

	//Split tokens by semi colons and determine what to do based on statement

	level = 2;
	free(buffer); //Destroy string at end of use.

	//spawn entities and tiles 
	if (level == 1) level1();
	else if (level == 2) level2();
	else {
		slog("Invalid level, starting level1...");
		level1();
	}
	return 0;
}

int level1() {

	/*variable declarations (C standard) */
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;

	Entity * player; //Player
	Tile * tile; //Test tile

	Space *space;

	int mx, my;
	float mf = 0; //mf = mouse frame; current mouse animation frame
	Sprite *mouse;
	Vector4D mouseColor = { 255,100,255,200 };

	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"Mini Birb Adventures - Omar Ilyas - IT 276",
		1200,
		720,
		1200,
		720,
		vector4d(0, 0, 0, 255),
		0);
	gf2d_graphics_set_frame_delay(16);
	gf2d_sprite_init(2048);

	//Initialize entity manager

	entity_manager_init(1024); //Max entities allowed on screen
	tile_manager_init(1024); //Max entities allowed on screen

	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png"); // background var
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16, false); // mouse pointer var

	//Create entity (player)
	player = player_new(vector2d(0, 420));

	//create tilemap (Put in separate files)
	tile = tile_new_invisible(vector2d(0, 520), vector2d(0.15, 0.2));
	tile = tile_new_invisible(vector2d(0, 290), vector2d(0.12, 0.01));
	tile = tile_new_invisible(vector2d(153.6, 400), vector2d(0.12, 0.01));
	tile = tile_new_invisible(vector2d(210, 190), vector2d(0.06, 0.01));
	tile = tile_new_invisible(vector2d(270.44, 650), vector2d(0.20, 0.11)); //Fridge Door
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

	//Create space
	space = gf2d_space_new_full(
		10,
		gf2d_rect(0, 0, 1280, 720),
		0.1,
		vector2d(0, 4),
		1,
		0.3);

	if (!space) slog("failed to create space");

	//Add to space
	gf2d_space_add_body(space, &player->body);
	tile_add_all_to_space(space);
	slog("Bodies added to space");

	/*main game loop */
	while (!done)	//UPDATE FUNCTION
	{
		SDL_PumpEvents();   // update SDL's internal event structures (ACTUAL UPDATING - DO NOT TOUCH)
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);

		mf += 0.01; //Mouse animation rate Adds +0.1 to animation every tic. 10 tics per animation frame
		if (mf >= 16.0)mf = 0;

		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame

		//Backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));
		//gf2d_space_draw(space, vector2d(0,0));

		//Tiles
		tile_draw_all();

		//Static Objects

		//Entities
		entity_draw_all();
		player_update(player, space);
		entity_update_all();

		//Effects

		//UI elements last (Mouse counts as UI)
		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);

		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition (SDL SCANCODE = Input.GetKey())

			//slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second()); //Display framerate

	}
	slog("---==== END ====---");
	return 0;
}

int level2() {
	/*variable declarations (C standard) */
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;

	Entity * player; //Player
	Tile * tile; //Test tile

	Space *space;

	int mx, my;
	float mf = 0; //mf = mouse frame; current mouse animation frame
	Sprite *mouse;
	Vector4D mouseColor = { 255,100,255,200 };

	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"Mini Birb Adventures - Omar Ilyas - IT 276",
		1200,
		720,
		1200,
		720,
		vector4d(0, 0, 0, 255),
		0);
	gf2d_graphics_set_frame_delay(16);
	gf2d_sprite_init(2048);

	//Initialize entity manager

	entity_manager_init(1024); //Max entities allowed on screen
	tile_manager_init(1024); //Max entities allowed on screen

	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png"); // background var
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16, false); // mouse pointer var

	//Create entity (player)
	player = player_new(vector2d(70, 515));

	//create tilemap (Put in separate files)
	tile = tile_new_invisible(vector2d(45, 570), vector2d(0.08, 0.03)); //Bottom start
	tile = tile_new_invisible(vector2d(115, 415), vector2d(0.05, 0.08)); //Waiter stage-left arm
	tile = tile_new_invisible(vector2d(214, 290), vector2d(0.07, 0.07)); //Waiter head
	tile = tile_new_invisible(vector2d(166.2, 360), vector2d(0.157, 0.3)); //Waiter body
	tile = tile_new_invisible(vector2d(325, 360), vector2d(0.05, 0.13)); //Waiter stage-right arm
	tile = tile_new_invisible(vector2d(0, 180), vector2d(0.2, 0.08)); //Cabinet above waiter
	//Create space
	space = gf2d_space_new_full(
		10,
		gf2d_rect(0, 0, 1280, 720),
		0.1,
		vector2d(0, 4),
		1,
		0.3);

	if (!space) slog("failed to create space");

	//Add to space
	gf2d_space_add_body(space, &player->body);
	tile_add_all_to_space(space);
	slog("Bodies added to space");

	/*main game loop */
	while (!done)	//UPDATE FUNCTION
	{
		SDL_PumpEvents();   // update SDL's internal event structures (ACTUAL UPDATING - DO NOT TOUCH)
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);

		mf += 0.01; //Mouse animation rate Adds +0.1 to animation every tic. 10 tics per animation frame
		if (mf >= 16.0)mf = 0;

		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame

		//Backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));
		//gf2d_space_draw(space, vector2d(0,0));

		//Tiles
		tile_draw_all();

		//Static Objects

		//Entities
		entity_draw_all();
		player_update(player, space);
		entity_update_all();

		//Effects

		//UI elements last (Mouse counts as UI)
		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);

		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition (SDL SCANCODE = Input.GetKey())

			//slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second()); //Display framerate

	}

	//level2();
	slog("---==== END ====---");
	return 0;
}



/*eol@eof*/
