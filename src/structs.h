typedef struct Texture Texture;
typedef struct Entity Entity;
typedef struct Spawner Spawner;

typedef struct
{
	int score;
	int level;
	char playerName[MAX_NAME_LENGTH];
} Scoreboard;

typedef struct
{
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

struct Texture
{
	char name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	Texture textureHead, *textureTail;
	int level;
	int stored_level;
	int score;
	char playerName[MAX_NAME_LENGTH];
} App;

struct Entity
{
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
	float value;
	int timer;
	SDL_Texture *texture;
	void (*tick)(void);
	void (*touch)(Entity *other);
	int flags;
	int orientation;
	Entity *next;
	Spawner *spawner;
};

struct Spawner
{
	float x;
	float y;
	int w;
	int h;
	int health;
	int timer;
	SDL_Texture *texture;
	Spawner *next;
	int nbMonster;
};

typedef struct
{
	SDL_Point camera;
	int map[MAP_WIDTH][MAP_HEIGHT];
	Entity entityHead, *entityTail;
	Entity fireHead, *fireTail;
	Spawner spawnerHead, *spawnerTail;
	Entity monsterHead, *monsterTail;
	int hasKey;
} Stage;