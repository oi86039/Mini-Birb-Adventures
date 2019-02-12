#include <SDL.h>
#include "entity.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "Player.h"

//GAME.C
//THE ACTUAL GAME CODE THAT RUNS WHEN THE EXE RUNS.
//UTILIZES ALL ENGINE FILES

int main(int argc, char * argv[])
{
	/*variable declarations (C standard) */
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;

	Entity * player; //Player

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
	gf2d_sprite_init(1024);

	//Initialize entity manager

	entity_manager_init(1024); //Max entities allowed on screen

	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png"); // background var
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16); // mouse pointer var

	//Create entity (player)
	player = player_new(vector2d(0, 0));

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

		//Tiles

		//Static Objects

		//Entities

		entity_draw_all();
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
		// exit condition (SDL SCANCODE = Input.GetKey())


		if (mf > 2) {
			slog("currFrame: %f", player->currFrame);
			slog("endFrame: %f", player->endFrame);
			slog("loop: %f", player->loop);

			//slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second()); //Display framerate
			mf = 0;
		}
	}
	slog("---==== END ====---");
	return 0;
}
/*eol@eof*/
