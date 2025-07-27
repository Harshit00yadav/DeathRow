#include <SDL2/SDL_image.h>
#include <stdbool.h>

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Controller{
	bool right;
	bool left;
	bool up;
	bool down;
	int x;
	int y;
} Controller;

typedef struct Player {
	int id;
	int x;
	int y;
	char state;
	int tile_size;
	SDL_Texture *spritesheet;
} Player;

typedef struct playerll {
	Player *player;
	struct playerll *next;
} Playerll;

Playerll *playerll_insert(Playerll *head, Player *p);
void playerll_destroy(Playerll *head);
Player *player_initialize(SDL_Renderer *renderer, int id, int x, int y, const char *spritesheetpath, int tile_size);
void player_destroy(Player *player);
void player_render(SDL_Renderer *renderer, Player *player);
void player_parse_response(SDL_Renderer *renderer, char *buffer, Playerll *pll);

#endif
