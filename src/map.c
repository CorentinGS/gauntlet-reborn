#include "map.h"

static void loadTiles(void);
static void loadMap(const char *filename);
int isInsideMap(int x, int y);

static SDL_Texture *tiles[MAX_TILES];

// Init de la map
void initMap(void)
{
	memset(&stage.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
	loadTiles();

	int level = app.level;
	switch (level)
	{
	case 1:
		loadMap("data/map01.dat");
		break;
	case 2:
		loadMap("data/map02.dat");
		break;
	case 3:
		loadMap("data/map03.dat");
		break;
	default:
		loadMap("data/map00.dat");
	}
}

// Dessin de la map
void drawMap(void)
{
	int x, y, n, x1, x2, y1, y2, mx, my;

	x1 = (stage.camera.x % TILE_SIZE) * -1;
	x2 = x1 + MAP_RENDER_WIDTH * TILE_SIZE + (x1 == 0 ? 0 : TILE_SIZE);

	y1 = (stage.camera.y % TILE_SIZE) * -1;
	y2 = y1 + MAP_RENDER_HEIGHT * TILE_SIZE + (y1 == 0 ? 0 : TILE_SIZE);

	mx = stage.camera.x / TILE_SIZE;
	my = stage.camera.y / TILE_SIZE;

	for (y = y1; y < y2; y += TILE_SIZE)
	{
		for (x = x1; x < x2; x += TILE_SIZE)
		{
			if (isInsideMap(mx, my))
			{
				n = stage.map[mx][my];

				blit(tiles[n], x, y, 0);
			}

			mx++;
		}

		mx = stage.camera.x / TILE_SIZE;

		my++;
	}
}

// Chargement des tiles de la map
static void loadTiles(void)
{
	int i;
	char filename[MAX_FILENAME_LENGTH];

	for (i = 0; i < MAX_TILES; i++)
	{
		sprintf(filename, "gfx/tile%d.png", i);

		tiles[i] = loadTexture(filename);
	}
}

// Chargement de la map
static void loadMap(const char *filename)
{
	char *data, *p;
	int x, y;

	data = readFile(filename);
	p = data;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			sscanf(p, "%d", &stage.map[x][y]);

			do
			{
				p++;
			} while (*p != ' ' && *p != '\n');
		}
	}

	free(data);
}

int isInsideMap(int x, int y)
{
	return x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT;
}
