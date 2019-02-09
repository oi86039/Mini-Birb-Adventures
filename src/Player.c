#include "Player.h"

void player_update(Entity*self);

Entity *player_new(Vector2D position)
{

	Entity *player = NULL;

	player = entity_new();
	if (!player)
	{
		slog("failed to allocate new player entity");
		return NULL;
	}

	vector2d_copy(player->position, position);
	player->spriteSheet = gf2d_sprite_load_all("images/Birb_Flapping.png", 371, 395, 5);
	player->currFrame = 1;

	//player->update = player_update;//Function pointer!

	//player->position = vector2d(200, 310);
	player->scale = vector2d(0.5, 0.5);
	player->velocity = vector2d(0, 0);
	player->frameLimit = 11;
	player->scale.x = 0.25;
	player->scale.y = 0.25;

}


void player_update(Entity*player)
{
	Uint8 *keys;
	//do stuff
	keys = SDL_GetKeyboardState(NULL);
	//Movement (Fly)
	if (keys[SDL_SCANCODE_W]) {
		vector2d_add(player->position, player->position, vector2d(0, -4));
	}

	if (keys[SDL_SCANCODE_A]) {
		vector2d_add(player->position, player->position, vector2d(-4, 0));
	}

	if (keys[SDL_SCANCODE_S]) {
		vector2d_add(player->position, player->position, vector2d(0, 4));
	}

	if (keys[SDL_SCANCODE_D]) {
		vector2d_add(player->position, player->position, vector2d(4, 0));
	}
}

//eol