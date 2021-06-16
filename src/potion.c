#include "potion.h"

static void tick(void);
static void touchRegen(Entity *other);
static void touchHeal(Entity *other);

void initPotionRegen(char *line)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    sscanf(line, "%*s %f %f", &e->x, &e->y);

    e->health = 1;
    e->flags = E_CONSUMMABLE;

    e->texture = loadTexture("gfx/regen_potion.png");
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->tick = tick;
    e->touch = touchRegen;
}

void initPotionHeal(char *line)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    sscanf(line, "%*s %f %f", &e->x, &e->y);

    e->health = 1;
    e->flags = E_CONSUMMABLE;

    e->texture = loadTexture("gfx/heal_potion.png");
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->tick = tick;
    e->touch = touchHeal;
}

// Effet de mouvement
static void tick(void)
{
    self->value += 0.1;
    self->y += sin(self->value);
}

// Contact avec joueur
static void touchRegen(Entity *other)
{
    if (self->health > 0 && other == player)
    {
        self->health = 0;

        other->health += 20;

        app.score += 5;

        playSound(SND_PIZZA, CH_PIZZA);
    }
}

static void touchHeal(Entity *other)
{
    if (self->health > 0 && other == player)
    {
        self->health = 0;

        other->health = 150;

        app.score += 5;

        playSound(SND_PIZZA, CH_PIZZA);
    }
}