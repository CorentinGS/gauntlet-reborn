#include "entities.h"

static void move(Entity *e);
static void push(Entity *e, float dx, float dy);
static void moveToWorld(Entity *e, float dx, float dy);
static void moveToEntities(Entity *e, float dx, float dy);
static void loadEnts(const char *filename);
static void addEntFromLine(char *line);

// Initialisation des entités
void initEntities(void)
{
	int level = app.level;
	switch (level)
	{
	case 1:
		loadEnts("data/ents01.dat");
		break;
	case 2:
		loadEnts("data/ents02.dat");
		break;
	case 3:
		loadEnts("data/ents03.dat");
		break;
	}
}

// Action des entités
void doEntities(void)
{
	Entity *e, *prev;

	prev = &stage.entityHead;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		self = e;

		if (e->tick)
		{
			e->tick();
		}

		move(e);

		if (e->health <= 0)
		{
			if (e == stage.entityTail)
			{
				stage.entityTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

// Action des monstres
void doMonsters(void)
{
	Entity *e, *prev;
	int distance;

	prev = &stage.monsterHead;

	for (e = stage.monsterHead.next; e != NULL; e = e->next)
	{
		self = e;
		distance = sqrt(((int)(e->x - player->x) ^ 2) + ((int)(e->y - player->y) ^ 2));

		int direction = f_get_rand(0, 4);

		if (distance < 10 && e->flags == E_DEMON)
		{
			e->dx = 0;
			e->dy = 0;

			if (e->x - player->x < 0)
			{
				e->dx = 1.5;
			}
			if (e->x - player->x > 0)
			{
				e->dx = -1.5;
			}
			if (e->y - player->y > 0)
			{
				e->dy = -1.5;
			}
			if (e->y - player->y < 0)
			{
				e->dy = 1.5;
			}
			e->timer--;
		}
		else if (e->timer > 0)
		{
			e->timer--;
		}
		else
		{
			e->dx = 0;
			e->dy = 0;
			e->timer = 20;
			switch (direction)
			{
			case 0:
				e->dx = 2;
				break;
			case 1:
				e->dx = -2;
				break;
			case 2:
				e->dy = 2;
				break;
			case 3:
				e->dy = -2;
				break;
			}
		}

		move(e);

		if (e->health <= 0)
		{
			if (e == stage.monsterTail)
			{
				stage.monsterTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}
		prev = e;
	}
}

// Déplacement d'une entité
static void move(Entity *e)
{

	e->x += e->dx;
	push(e, e->dx, 0);

	e->y += e->dy;
	push(e, 0, e->dy);
}

static void push(Entity *e, float dx, float dy)
{
	moveToWorld(e, dx, dy); // Déplacement sur la map
	moveToEntities(e, dx, dy); // Collision des entités
}

static void moveToWorld(Entity *e, float dx, float dy)
{
	int mx, my, hit, adj;

	// Déplacement en x
	if (dx != 0)
	{
		mx = dx > 0 ? (e->x + e->w) : e->x;
		mx /= TILE_SIZE;

		my = (e->y / TILE_SIZE);

		hit = 0;

		if (!isInsideMap(mx, my) || (stage.map[mx][my] != 0 && e->flags != E_GHOST))
		{
			hit = 1;
		}

		my = (e->y + e->h - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || (stage.map[mx][my] != 0 && e->flags != E_GHOST))
		{
			hit = 1;
		}

		if (hit)
		{
			adj = dx > 0 ? -e->w : TILE_SIZE;

			e->x = (mx * TILE_SIZE) + adj;

			e->dx = 0;
		}
	}

	// Déplacement en y
	if (dy != 0)
	{
		my = dy > 0 ? (e->y + e->h) : e->y;
		my /= TILE_SIZE;

		mx = e->x / TILE_SIZE;

		hit = 0;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0)
		{
			hit = 1;
		}

		mx = (e->x + e->w - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0)
		{
			hit = 1;
		}

		if (hit)
		{
			adj = dy > 0 ? -e->h : TILE_SIZE;

			e->y = (my * TILE_SIZE) + adj;

			e->dy = 0;
		}
	}
}

static void moveToEntities(Entity *e, float dx, float dy)
{
	Entity *other;

	for (other = stage.entityHead.next; other != NULL; other = other->next)
	{
		if (other != e && collision(e->x, e->y, e->w, e->h, other->x, other->y, other->w, other->h))
		{
			if (e->touch)
			{
				e->touch(other);
			}

			if (other->flags == 0 && e->flags > 3 && e->reload <= 0)
			{
				other->health -= 5;
				e->reload = 10;
			}
			else
			{
				e->reload--;
			}
		}
	}
}

// Dessin des entités
void drawEntities(void)
{
	Entity *e;

	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
	}
}

// Dessin des boules de feu
void drawFire(void)
{
	Entity *e;

	for (e = stage.fireHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
	}
}

void drawSpawner(void)
{
	Spawner *e;

	for (e = stage.spawnerHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
	}
}

// Dessin des monstres
void drawMonster(void)
{
	Entity *e;

	for (e = stage.monsterHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
	}
}

// Chargement des entités depuis un fichier
static void loadEnts(const char *filename)
{
	char line[MAX_LINE_LENGTH];
	char *data, *p;
	int n;

	data = readFile(filename);

	p = data;

	n = 0;

	memset(line, '\0', MAX_LINE_LENGTH);

	while (*p)
	{
		if (*p == '\n')
		{
			addEntFromLine(line);
			memset(line, '\0', MAX_LINE_LENGTH);
			n = 0;
		}
		else
		{
			line[n++] = *p;
		}

		p++;
	}

	free(data);
}

static void addEntFromLine(char *line)
{
	char name[MAX_NAME_LENGTH];

	sscanf(line, "%s", name);

	if (strcmp(name, "PIZZA") == 0)
	{
		initPizza(line);
	}
	else if (strcmp(name, "SPAWNER") == 0)
	{
		initSpawner(line);
	}
	else if (strcmp(name, "CHEST") == 0)
	{
		initChest(line);
	}
	else if (strcmp(name, "REGEN") == 0)
	{
		initPotionRegen(line);
	}
	else if (strcmp(name, "HEAL") == 0)
	{
		initPotionHeal(line);
	}
	else if (strcmp(name, "KEY") == 0)
	{
		initKey(line);
	}
	else if (strcmp(name, "PORTE") == 0)
	{
		initDoor(line);
	}
	else
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Unknown entity '%s'", line);
	}
}