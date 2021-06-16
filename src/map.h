#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern SDL_Texture *loadTexture(char *filename);
extern char *readFile(const char *filename);

extern Stage stage;
extern App app;
