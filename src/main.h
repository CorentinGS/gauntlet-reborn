#include "common.h"

extern void cleanup(void);
extern void doInput(void);
extern void initGame(void);
void startLevel(void);
extern void initSDL(void);
extern void initStage(void);
extern void prepareScene(void);
extern void presentScene(void);
extern int menuprincipal(int *level);


App app;
Entity *player;
Entity *fire;
Entity *monster;
Entity *self;
Spawner *selfSpawner;
Stage stage;
