#include <SDL.h>
#include "entity.h"
#include "Tile.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gf2d_collision.h"
#include "simple_logger.h"
#include "Player.h"
#include "Save.h"

//GAME.C
//THE ACTUAL GAME CODE THAT RUNS WHEN THE EXE RUNS.
//UTILIZES ALL ENGINE FILES

int main(int argc, char * argv[])
{
	level1();
	return 0;
}

int level1() {

	/*variable declarations (C standard) */
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;

	Save save;
	Entity * player; //Player
	Tile * tile = tile_new_invisible(vector2d(0, 0), vector2d(0, 0)); //Test tile

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
	load_tilemap(1, tile);

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

	Save save; //Empty save struct

	Entity * player; //Player
	Tile * tile = tile_new_invisible(vector2d(0, 0), vector2d(0, 0)); //Test tile

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
	tile_manager_init(50); //Max entities allowed on screen

	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png"); // background var
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16, false); // mouse pointer var

	//Create entity (player)
	player = player_new(vector2d(70, 515));

	//create tilemap (Put in separate files)
	load_tilemap(2, tile);

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
					//When mf = 1 a full second has passed (use this to time ops!)
		if (mf >= 16.0)mf = 0;

		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame

		//Backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));
		//gf2d_space_draw(space, vector2d(0,0));

		//Saving
		if (keys[SDL_SCANCODE_O]) {
			save_file(&save, 1, player);
		}
		if (keys[SDL_SCANCODE_P]) {
			load_file(&save);
		}

		//Tiles
		tile_draw_all();

		//Static Objects

		//Entities
		entity_draw_all();
		player_update(player, space);
		entity_update_all();

		//Effects

		//UI elements last (Mouse counts as UI)
		gf2d_sprite_draw_image(gf2d_sprite_load_image("images/Health Text.png"),vector2d(0,630));

		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);

		gf2d_grahics_next_frame(); // render current draw frame and skip to the next frame

		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition

			//slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second()); //Display framerate

	}

	//level2();
	slog("---==== END ====---");
	return 0;
}


/*eol@eof*/
