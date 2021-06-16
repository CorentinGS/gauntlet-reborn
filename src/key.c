#include "key.h"

static void tick(void);
static void touch(Entity *other);

void initKey(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;
	e->flags = E_KEY;

	e->texture = loadTexture("gfx/key.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->tick = tick;
	e->touch = touch;
}

// Effet de mouvement
static void tick(void)
{
	self->value += 0.1;

	self->y += sin(self->value);
}

// Contact avec joueur
static void touch(Entity *other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;
		stage.hasKey = TRUE;

		playSound(SND_PIZZA, CH_PIZZA);
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "GOT KEY");
	}
}
