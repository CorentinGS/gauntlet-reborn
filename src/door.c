#include "door.h"

static void touch(Entity *other);

void initDoor(char *line)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.entityTail->next = e;
    stage.entityTail = e;

    sscanf(line, "%*s %f %f", &e->x, &e->y);

    e->health = 1;
    e->flags = E_DOOR;

    e->texture = loadTexture("gfx/door_close.png");
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->touch = touch;
}

// Contact avec joueur
static void touch(Entity *other)
{
    if (self->health > 0 && other == player && stage.hasKey == TRUE)
    {

        playSound(SND_PIZZA, CH_PIZZA);
        app.score += 50;
        app.level++;
        stage.hasKey = FALSE;
    }
}
