#include "common.h"

extern SDL_Texture *loadTexture(char *filename);
extern void playSound(int id, int channel);
extern void initMonster(Spawner *spawner);
extern void doMonsters(void);
extern void doSpawner(void);

extern Entity *player;
extern Spawner *selfSpawner;
extern Stage stage;