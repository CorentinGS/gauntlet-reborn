#include "main.h"

static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[])
{

	int level = 1, score = 0;

	memset(&app, 0, sizeof(App));
	char name[MAX_NAME_LENGTH];

	printf("Enter your name ! (only MAJ)      ");
	fgets(name, sizeof(name), stdin);

	strcpy(app.playerName, name);

	while (menuprincipal(&level) != 1)
		;

	app.textureTail = &app.textureHead;
	app.level = level;
	app.score = score;

	// Chargement de la SDL
	initSDL();

	// Clean la SDL à la sortie
	atexit(cleanup);

	// Initialisation du jeu
	initGame();

	startLevel();

	return 0;
}

void startLevel(void)
{
	long then;
	float remainder;
	int level = app.level;
	int time1, time2 = 0;

	// Initialisation du niveau

	initStage();

	then = SDL_GetTicks();

	remainder = 0;

	// Boucle de jeu
	while (1)
	{
		// Préparation de la scène
		prepareScene();

		// Input
		doInput();

		// Logic ( déplacement, collisions etc...)
		app.delegate.logic();

		time1 = SDL_GetTicks();
		if (time1 - time2 > 2000)
		{
			player->health = player->health - 1;
			time2 = time1;
		}

		// Dessin des entités
		app.delegate.draw();

		// Affichage
		presentScene();

		// Limite de FPS
		capFrameRate(&then, &remainder);
		if (level != app.level)
		{
			break;
		}
	}
	startLevel();
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
