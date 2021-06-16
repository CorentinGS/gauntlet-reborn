#include "player.h"

static SDL_Texture *mage[4];
static SDL_Texture *fireTexture[4];
static SDL_Texture *monsterTexture;

// Création du joueur
void initPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;
	int level = app.level;

	switch (level)
	{
	case 1:
		player->x = 118;
		player->y = 76;
		player->health = 100;
		break;
	case 2:
		player->x = 1076;
		player->y = 873;
		player->health = 110;
		break;
	case 3:
		player->x = 790;
		player->y = 100;
		player->health = 120;
		break;
	case 0:
		player->x = 1000;
		player->y = 1000;
		break;
	}

	mage[0] = loadTexture("gfx/mage_gauche.png");
	mage[1] = loadTexture("gfx/mage_droite.png");
	mage[2] = loadTexture("gfx/mage.png");
	mage[3] = loadTexture("gfx/mage_dos.png");

	fireTexture[0] = loadTexture("gfx/fire_droite.png");
	fireTexture[1] = loadTexture("gfx/fire_gauche.png");
	fireTexture[2] = loadTexture("gfx/fire_haut.png");
	fireTexture[3] = loadTexture("gfx/fire_bas.png");

	player->texture = mage[3];
	player->flags = 0;

	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

// Création d'un monstre
void initMonster(Spawner *spawner)
{
	monster = malloc(sizeof(Entity));
	memset(monster, 0, sizeof(Entity));
	stage.monsterTail->next = monster;
	stage.monsterTail = monster;

	monster->health = 20;
	monster->x = spawner->x;
	monster->y = spawner->y;
	monster->timer = 30;
	monster->spawner = spawner;

	int type = f_get_rand(0, 2);

	switch (type)
	{
	case 0:
		monster->flags = E_GHOST;
		monsterTexture = loadTexture("gfx/fantome.png");
		break;
	case 1:
		monster->flags = E_DEMON;
		monsterTexture = loadTexture("gfx/demon.png");
		break;
	}

	monster->texture = monsterTexture;

	SDL_QueryTexture(monster->texture, NULL, NULL, &monster->w, &monster->h);
}

// Création d'une boule de feu
void fireBullet(void)
{
	Entity *fire;

	fire = malloc(sizeof(Entity));
	memset(fire, 0, sizeof(Entity));
	stage.fireTail->next = fire;
	stage.fireTail = fire;

	fire->x = player->x;
	fire->y = player->y;
	fire->dx = player->dx * 1.5;
	fire->dy = player->dy * 1.5;
	fire->health = 1;
	if (fire->dx > 0 || player->orientation == DROITE)
	{
		fire->texture = fireTexture[0];
		fire->dx = PLAYER_MOVE_SPEED * 1.5;
	}
	else if (fire->dx < 0 || player->orientation == GAUCHE)
	{
		fire->texture = fireTexture[1];
		fire->dx = -PLAYER_MOVE_SPEED * 1.5;
	}
	else if ((fire->dy > 0 && fire->dx == 0) || player->orientation == BAS)
	{
		fire->texture = fireTexture[3];
		fire->dy = PLAYER_MOVE_SPEED * 1.5;
	}
	else if ((fire->dy < 0 && fire->dx == 0) || (player->orientation == HAUT))
	{
		fire->texture = fireTexture[2];
		fire->dy = -PLAYER_MOVE_SPEED * 1.5;
	}
	SDL_QueryTexture(fire->texture, NULL, NULL, &fire->w, &fire->h);

	fire->y += (player->h / 2) - (fire->h / 2);
}

// Action du joueur
void doPlayer(void)
{
	if ((player->health <= 0 && app.level > 0) || app.level > MAX_LEVEL)
	{

		writeScoreboard("data/scoreboard.dat");
		app.stored_level = app.level;
		app.level = 0;
	}

	if (player->health > 150)
	{
		player->health = 150;
	}

	player->dx = 0;
	player->dy = 0;

	// Cooldown sur les boules de feu
	if (player->reload > 0)
	{
		player->reload--;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		player->dx = -PLAYER_MOVE_SPEED;
		player->texture = mage[0];
		player->orientation = GAUCHE;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		player->dx = PLAYER_MOVE_SPEED;
		player->texture = mage[1];
		player->orientation = DROITE;
	}

	if (app.keyboard[SDL_SCANCODE_W])
	{
		player->dy = -PLAYER_MOVE_SPEED;
		player->texture = mage[3];
		player->orientation = HAUT;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		player->dy = PLAYER_MOVE_SPEED;
		player->texture = mage[2];
		player->orientation = BAS;
	}

	if (app.keyboard[SDL_SCANCODE_Q])
	{
		// Pour debug uniquement
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Position :  %f | %f", player->x, player->y);
		app.keyboard[SDL_SCANCODE_Q] = 0;
	}

	if (app.keyboard[SDL_SCANCODE_SPACE] && player->reload <= 0)
	{
		fireBullet();
		player->reload = 25;
		app.keyboard[SDL_SCANCODE_SPACE] = 0;
	}
}

// Collision d'une boule de feu et d'une entité
static int fireHitMonster(Entity *fire)
{
	Spawner *e;
	Entity *monster;

	for (e = stage.spawnerHead.next; e != NULL; e = e->next)
	{
		if (collision(fire->x, fire->y, fire->w, fire->h, e->x, e->y, e->w, e->h))
		{
			fire->health = 0;
			e->health = 0;
			app.score += 10;
			return 1;
		}
	}

	for (monster = stage.monsterHead.next; monster != NULL; monster = monster->next)
	{
		if (collision(fire->x, fire->y, fire->w, fire->h, monster->x, monster->y, monster->w, monster->h))
		{
			fire->health = 0;
			monster->health = 0;
			monster->spawner->nbMonster--;
			app.score += 5;
			return 1;
		}
	}

	return 0;
}

// Action d'une boule de feu
void doFire(void)
{
	Entity *b, *prev;
	int mx, my;

	prev = &stage.fireHead;

	for (b = stage.fireHead.next; b != NULL; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		mx = b->dx > 0 ? (b->x + b->w) : b->x;
		mx /= TILE_SIZE;

		my = (b->y / TILE_SIZE);

		if (fireHitMonster(b) || b->x > MAP_WIDTH * SCREEN_WIDTH / MAP_RENDER_WIDTH || b->y > MAP_HEIGHT * SCREEN_HEIGHT / MAP_RENDER_HEIGHT || b->x < 0 || b->y < 0 || stage.map[mx][my] != 0)
		{
			if (b == stage.fireTail)
			{
				stage.fireTail = prev;
			}

			prev->next = b->next;
			free(b);
			b = prev;
		}

		prev = b;
	}
}