#include "stage.h"

static void logic(void);
static void draw(void);
static void drawHud(void);
static void drawScoreboard(void);

// Init d'un niveau
void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));

	// Tableau des entités / boules de feu / monstres
	stage.entityTail = &stage.entityHead;
	stage.fireTail = &stage.fireHead;
	stage.spawnerTail = &stage.spawnerHead;
	stage.monsterTail = &stage.monsterHead;

	stage.hasKey = FALSE;

	// Init des entités
	initEntities();

	initPlayer();

	//initSpawner();

	// Init de la map
	initMap();
}

static void logic(void)
{
	doPlayer();

	doEntities();

	doSpawner();

	doMonsters();

	doFire();

	doCamera();
}

static void draw(void)
{
	SDL_SetRenderDrawColor(app.renderer, 128, 192, 255, 255);
	SDL_RenderFillRect(app.renderer, NULL);

	drawMap();

	drawEntities();

	drawSpawner();

	drawMonster();

	drawFire();

	if (app.level == 0)
	{
		drawScoreboard();
	}
	else
	{
		drawHud();
	}
}

static void drawHud(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);

	drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "PLAYER: %s    LEVEL: %d    SCORE: %d    HEALTH: %d", app.playerName, app.level, app.score, player->health);
}

static void drawScoreboard(void)
{
	SDL_Rect r;
	int i, diff = 40;
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT;

	Scoreboard tab[10];
	readScoreboard("data/scoreboard.dat", tab);

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
	for (i = 0; i < 10; i++)
	{
		drawText(SCREEN_WIDTH - 20, 30 + (diff * i), 255, 255, 255, TEXT_RIGHT, "PLAYER: %s          LEVEL: %d          SCORE: %d", tab[i].playerName, tab[i].level, tab[i].score);
	}

	drawText(SCREEN_WIDTH - 20, 30 + (diff * 15), 255, 255, 255, TEXT_RIGHT, "VOTRE SCORE :          LEVEL: %d          SCORE: %d", app.stored_level, app.score);
}
