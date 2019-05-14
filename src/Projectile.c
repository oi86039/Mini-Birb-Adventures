#include "Projectile.h"
#include "simple_logger.h"
#include "gui.h"
#include "gf2d_audio.h"

void projectile_update(Entity* self, Space* space);

int projectile_bodyTouch(struct Body_S* self, struct Body_S* other, Collision* collision);
int projectile_worldTouch(struct Body_S* self, Collision* collision);

static int projectile_count = 0; /**Total count of projectiles*/
static int melee_count = 0; /*count of melee projectiles*/
static int long_count = 0; /*count of long shot projectiles*/
static int spread_count = 0; /*count of spread shot projectiles*/
static int rapid_count = 0; /*count of rapid fire projectiles*/

Entity* projectile_new(Proj_Type type, Vector2D velocity, Entity* shooter, Space* space)
{
	//Don't spawn if >projectile_count
	if (projectile_count > 30) return NULL; //Only 10 projectiles allowed

	Entity* projectile = NULL;
	projectile = entity_new();
	if (!projectile) {
		slog("failed to allocate new projectile entity");
		return NULL;
	}

	//Determine type (Don't spawn if >type_count is)
	if (type == MELEE && melee_count < 1) {
		projectile->spriteSheet = gf2d_sprite_load_image("images/melee.png");
		projectile->colorShift = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
		projectile->scale = vector2d(.03, .03);
		projectile->velocity = velocity;
		projectile->sound = gf2d_sound_load("audio/hit-01.wav", 0.5, 2);
		projectile->hitBox = gf2d_shape_circle(projectile->position.x, projectile->position.y, 500 * projectile->scale.x);
		projectile->offset = vector2d(10, 10);
		projectile->timeLimit = 0.15;
		melee_count++;
	}
	else if (type == LONG && long_count < 3) {
		projectile->spriteSheet = gf2d_sprite_load_image("images/Long.png");
		projectile->colorShift = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
		projectile->scale = vector2d(.05, .05);
		projectile->velocity = velocity;
		projectile->sound = gf2d_sound_load("audio/shoot-02.wav", 0.5, 2);
		projectile->hitBox = gf2d_shape_circle(projectile->position.x, projectile->position.y, 212 * projectile->scale.x);
		projectile->offset = vector2d(10, 10);
		projectile->timeLimit = 1;
		long_count++;
	}
	else if (type == SPREAD && spread_count < 3) {
		projectile->spriteSheet = gf2d_sprite_load_image("images/Spread.jpg");
		projectile->colorShift = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
		projectile->scale = vector2d(.02, .02);
		projectile->velocity = velocity;
		projectile->sound = gf2d_sound_load("audio/shoot-01.wav", 0.5, 2);
		projectile->hitBox = gf2d_shape_circle(projectile->position.x, projectile->position.y, 238 * projectile->scale.x);
		projectile->offset = vector2d(5, 5);
		projectile->timeLimit = 0.50;
		spread_count++;
	}
	else if (type == RAPID && rapid_count < 10) {
		projectile->spriteSheet = gf2d_sprite_load_image("images/Rapid.png");
		projectile->colorShift = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
		projectile->scale = vector2d(.02, .02);
		projectile->velocity = velocity;
		projectile->sound = gf2d_sound_load("audio/hit-01.wav", 0.5, 2);
		projectile->hitBox = gf2d_shape_circle(projectile->position.x, projectile->position.y, 439 * projectile->scale.x);
		projectile->offset = vector2d(10, 10);
		projectile->timeLimit = 0.07;
		rapid_count++;
		//projectile id
	}
	else if (type == ENEMY_LONG) {
		projectile->spriteSheet = gf2d_sprite_load_image("images/Long.png");
		projectile->colorShift = gf2d_color_to_vector4(gf2d_color(1, 0.5, 0.5, 1));
		projectile->scale = vector2d(.05, .05);
		projectile->velocity = velocity;
		projectile->sound = gf2d_sound_load("audio/hit-01.wav", 0.5, 2);
		projectile->hitBox = gf2d_shape_circle(projectile->position.x, projectile->position.y, 212 * projectile->scale.x);
		projectile->offset = vector2d(10, 10);
		projectile->timeLimit = 1;
		//long_count++;
	}
	else {
		gf2d_sound_free(projectile->sound); //Free sound memory
		entity_free(projectile);
		return NULL;
	}
	//If projectile is made
	projectile_count++;
	projectile->type = type;

	vector2d_copy(projectile->position, shooter->position);
	projectile->lastDir = shooter->lastDir;
	projectile->flip = vector2d(projectile->lastDir, 0); //Facing Right
	projectile->timer = 0; //Initiailize timer for duration

	if (projectile->lastDir == 1) //Change dir if shooter facing left
		projectile->velocity.x *= -1;

	gf2d_body_set(&projectile->body,
		"projectile",
		0,
		0,
		projectile->position,
		projectile->velocity,
		1,
		1,
		1,
		&projectile->hitBox,
		projectile,
		projectile_bodyTouch,
		projectile_worldTouch);

	gf2d_space_add_body(space, &projectile->body);
	//slog("projectile body Added to space");

	projectile->projectile_update = projectile_update;//Function pointer!

	gf2d_sound_play(projectile->sound, 0, 0.5, 2, 2);//Play sound ounce

	return projectile;
}

//Register hit and move projectile
void projectile_update(Entity * self, Space * space) {

	self->timer += 0.01; //Increment timer
	//if (shooter->hitBox.id == 0)
	//gui_set_energy(self->timer / self->timeLimit);

	Collision staticHit = gf2d_space_shape_test(space, self->hitBox);
	Collision bodyHit;
	ClipFilter filter; filter.layer = 1; filter.team = 1;

	gf2d_space_body_collision_test_filter(space, self->hitBox, &bodyHit, filter);

	vector2d_add(self->position, self->position, self->velocity);
	self->hitBox.s.c.x = self->position.x + self->offset.x;
	self->hitBox.s.c.y = self->position.y + self->offset.y;

	//if (staticHit.collided >= 1) { //If projectile touches something, destroy the projectile
	if (self->timer >= self->timeLimit) {
		if (self->type == MELEE)
			melee_count--;
		else if (self->type == LONG)
			long_count--;
		else if (self->type == SPREAD)
			spread_count--;
		else if (self->type == RAPID)
			rapid_count--;
		projectile_free(space, self);
	}
}

int projectile_bodyTouch(struct Body_S* self, struct Body_S* other, Collision * collision) {
	if (collision->collided == 1) {
		slog("Body touch successful");
		return 1;
	}
	else return 0;
}
int projectile_worldTouch(struct Body_S* self, Collision * collision) {
	if (collision->collided == 1) {
		slog("World touch successful");
		return 1;
	}
	else return 0;
}
void projectile_free(Space * space, Entity * self) {
	projectile_count--;
	gf2d_space_remove_body(space, &self->body);
	gf2d_sound_free(self->sound); //Free sound memory
	//gui_set_energy(1);
	entity_free(self);
}


