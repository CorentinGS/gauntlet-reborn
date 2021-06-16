#include "spawner.h"

void initSpawner(char *line)
{
    Spawner *e;

    e = malloc(sizeof(Spawner));
    memset(e, 0, sizeof(Spawner));
    stage.spawnerTail->next = e;
    stage.spawnerTail = e;

    sscanf(line, "%*s %f %f", &e->x, &e->y);

    e->health = 1;
    e->nbMonster = 0;
    e->timer = 30;

    e->texture = loadTexture("gfx/porte.png");
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
}

// Contact avec joueur
void doSpawner(void)
{

    Spawner *e, *prev;

    prev = &stage.spawnerHead;

    for (e = stage.spawnerHead.next; e != NULL; e = e->next)
    {
        selfSpawner = e;

        if (e->health <= 0)
        {
            if (e == stage.spawnerTail)
            {
                stage.spawnerTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }

        if (e->nbMonster < MAX_MONSTER_SPAWNER && e->timer <= 0)
        {
            initMonster(e);
            e->nbMonster++;
            e->timer = 50;
        }
        else
        {
            e->timer--;
        }

        prev = e;
    }
}
