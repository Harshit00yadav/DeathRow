#include <SDL2/SDL_image.h>

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
	int x;
	int y;
	char *state;
	int tile_size;
	SDL_Texture *spritesheet;
} Player;

#endif

Player *player_initialize(SDL_Renderer *renderer, int x, int y, const char *spritesheetpath, int tile_size);
void player_destroy(Player *player);
void player_render(SDL_Renderer *renderer, Player *player);
void player_update(Player *player);
