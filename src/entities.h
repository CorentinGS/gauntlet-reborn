#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern int f_get_rand(const int min, const int max);

extern void initPizza(char *line);
extern void initSpawner(char *line);
extern void initKey(char *line);
extern void initChest(char *line);
extern void initPotionRegen(char *line);
extern void initPotionHeal(char *line);
extern void initDoor(char *line);
extern int isInsideMap(int x, int y);
extern char *readFile(const char *filename);
extern void writeScoreboard(const char *filename);

extern Entity *self;
extern Stage stage;
extern App app;
extern Entity *player;
