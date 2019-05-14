#include <SDL.h>
#include "entity.h"
#include "Tile.h"
#include "gf2d_graphics.h"
#include "gf2d_text.h"
#include "gf2d_audio.h"
#include "gf2d_sprite.h"
#include "gf2d_collision.h"
#include "simple_logger.h"
#include "Save.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "gui.h"

int main(int argc, char* argv[])
{
	//int next = level1();
	//Load Level 1
	//level_load(1);
	//Load Level 2
	//level_load(2, (vector2d(70, 515));
	//Load Level 3
	level_load(2);
	//Load Level 4
	//level_load(4, vector2d(0, 420));
	//level3();
	return 0;
}

int level_load(int level) {
	/*variable declarations (C standard) */
	int done = 0;
	const Uint8* keys;
	SDL_Event event; //SDL Current Keyboard/mouse event (GOD HELP US ALL)
	Sprite* sprite; //Background pic
	int saveUIFlag = 0; //Trigger save UI timer
	float saveUITimer; //Delay in Save UI
	//Sound shoot;

	Save save;
	Entity* player;
	Entity* enemy[1009];
	int enemyIndex = 3;
	Tile* tile = tile_new_invisible(vector2d(0, 0), vector2d(0, 0)); //Test tile

	Space* space;

	int debug_id = 0; //index for painting

	int mx, my;
	float mf = 0; //mf = mouse frame; current mouse animation frame
	Sprite* saveMessage; Vector2D msgScale;
	Sprite* mouse;
	Vector2D mouseScale = vector2d(0.1, 0.1);
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
	gf2d_audio_init(256, 16, 4, 1, 1, 1);
	gf2d_sprite_init(2048);

	Sound* music[] = {
		gf2d_sound_load("audio/bensound-theelevatorbossanova.wav", 0.5, 1),
		gf2d_sound_load("audio/heliumplains_cut.wav", 0.5, 1),
		gf2d_sound_load("audio/Frozen In Time (Chiptune).wav", 0.5, 1),
		gf2d_sound_load("audio/FinalBoss.wav", 0.5, 1),
	};

	//Initialize entity manager
	entity_manager_init(1010); //Max entities allowed on screen
	tile_manager_init(130); //Max entities allowed on screen

	//setup gui
	gui_setup_hud();
	gui_set_health(30);
	gui_set_energy(1);
	//gf2d_text_init("config/fonts.cfg");

	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png"); // background var
	msgScale = vector2d(0.35, 0.35);
	//mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16, false); // mouse pointer var

	//Create space
	space = gf2d_space_new_full(
		10,
		gf2d_rect(0, 0, 1280, 720),
		0.1,
		vector2d(0, 4),
		1,
		0.3);
	if (!space) slog("failed to create space");

	//Init save file
	read_file(&save, level);

	//Create entity (player)
	if (level == 1)
		player = player_new(vector2d(0, 420), level, save);
	else if (level == 2)
		player = player_new(vector2d(70, 515), level, save);
	else if (level == 3)
		player = player_new(vector2d(20, 0), level, save);
	else if (level == 4)
		player = player_new(vector2d(0, 420), level, save);

	//create tilemap (Put in separate files)
	load_tilemap(level, tile);

	//create enemies
	enemy[0] = enemy_new(11, vector2d(1000, 330), level, save);
	enemy[1] = enemy_new(12, vector2d(271, 400), level, save);
	enemy[2] = enemy_new(13, vector2d(980, 330), level, save);

	Sprite * debugSprites[] = {
		player->spriteSheet,
		enemy[0]->spriteSheet,
		enemy[1]->spriteSheet,
		enemy[2]->spriteSheet };
	mouse = debugSprites[0]; // mouse pointer var

	//Add to space
	gf2d_space_add_body(space, &player->body);
	gf2d_space_add_body(space, &enemy[0]->body);
	gf2d_space_add_body(space, &enemy[1]->body);
	gf2d_space_add_body(space, &enemy[2]->body);
	tile_add_all_to_space(space);
	slog("Bodies added to space");

	gf2d_sound_play(music[level - 1], 5000, 1, 0.1, -1); //Play background music

	/*main game loop */
	while (!done)	//UPDATE FUNCTION
	{
		SDL_PumpEvents();   // update SDL's internal event structures (ACTUAL UPDATING - DO NOT TOUCH)
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

		/*update things here*/
		SDL_GetMouseState(&mx, &my);

		if (SDL_PollEvent(&event) == 1) {
			//Toggle enemy
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFTBRACKET) {
				debug_id--;
				if (debug_id < 0)debug_id = 3;
				mouse = debugSprites[debug_id];
			}
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHTBRACKET) {
				debug_id++;
				if (debug_id > 3)debug_id = 0;
				mouse = debugSprites[debug_id];
			}

			//Paint enemies on click
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				if (debug_id == 0 && mf <= 0) {
					enemy[enemyIndex] = player_new(vector2d(mx, my), level, save);
					enemyIndex++;
					mf++;
				}
				else if (debug_id == 1 && mf <= 0) {
					enemy[enemyIndex] = enemy_new(11, vector2d(mx, my), level, save);
					enemyIndex++;
					mf++;
				}
				else if (debug_id == 2 && mf <= 0)
				{
					enemy[enemyIndex] = enemy_new(12, vector2d(mx, my), level, save);
					enemyIndex++;
					mf++;
				}
				else if (debug_id == 3 && mf <= 0)
				{
					enemy[enemyIndex] = enemy_new(13, vector2d(mx, my), level, save);
					enemyIndex++;
					mf++;
				}
			}
		}
		if (mf >= 1) { //Paint Speed limiter
			mf += 0.01;
			if (mf > 1.2)
				mf = 0;
		}

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
		if (player) {
			//Update main player
			player_update(player, space, level, save, enemy[0], enemy[1], enemy[2]); //Prevents undeclared identifier error;
			//Update other players
			for (int i = 3; i < enemyIndex; i++)
			{
				if (enemy[i]->hitBox.id == 0)
					player_update(enemy[i], space, level, save, enemy[0], enemy[1], enemy[2]); //Prevents undeclared identifier error;

			}
		}
		entity_update_all(space, player);

		//Effects

		//Saving
		if (keys[SDL_SCANCODE_O] && player->health > 0) {
			save_file(&save, level, player, enemy[0], enemy[1], enemy[2]);
			saveMessage = gf2d_sprite_load_image("images/ui/Saved.png");
			saveUITimer = 0;
			saveUIFlag = 1;
		}
		//Loading
		if (keys[SDL_SCANCODE_P]) {
			load_file(&save, level, player, enemy[0], enemy[1], enemy[2]);
			for (int i = 3; i < enemyIndex; i++)
				entity_free(enemy[i]);
			enemyIndex = 3;
			saveMessage = gf2d_sprite_load_image("images/ui/Loaded.png");
			saveUITimer = 0;
			saveUIFlag = 1;
		}

		//UI elements last (Mouse counts as UI)
		gui_draw_hud();

		//Save UI
		if (saveUIFlag == 1) {
			//Saved Game
			gf2d_sprite_draw(
				saveMessage,
				vector2d(900, 650),
				&msgScale,
				NULL,
				NULL,
				NULL,
				NULL,
				0);
			saveUITimer += 0.01;
			if (saveUITimer >= 1) {
				saveUITimer = 0;
				saveUIFlag = 0;
			}
		}
		//Mouse
		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			&mouseScale,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			0);

		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition (SDL SCANCODE = Input.GetKey())

			//slog("Rendering at %f FPS", gf2d_graphics_get_frames_per_second()); //Display framerate
	}

	gf2d_sound_clear_all();

	slog("---==== END ====---");
	return 0;
}
///*eol@eof*/
