#include "common.h"

extern void doCamera(void);
extern void doEntities(void);
extern void doSpawner(void);
extern void doPlayer(void);
extern void doFire(void);
extern void doMonsters(void);
extern void fireBullet(void);
extern void drawFire(void);
extern void drawEntities(void);
extern void drawMonster(void);
extern void drawSpawner(void);
extern void drawMap(void);
extern void initEntities(void);
extern void initMap(void);
extern void initPlayer(void);
extern void initMonster(void);
extern void initSpawner(void);
extern void readScoreboard(const char *filename, Scoreboard tab[]);

extern void drawText(int x, int y, int r, int g, int b, int align, char *format, ...);

extern App app;
extern Stage stage;
extern Entity *player;
