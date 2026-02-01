#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "camera.h"

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Controller{
	bool right;
	bool left;
	bool up;
	bool down;
	bool orientation;
	int x;
	int y;
} Controller;

typedef struct Player {
	int id;
	int x;
	int y;
	char state;
	bool state_change;
	int tile_size;
	int frame_index;
	int frame_count;
	int animation_index;
	int orientation;
	double cumilative_delta;
	SDL_Texture *spritesheet;
	bool isrendered;
} Player;

typedef struct playerll {
	Player *player;
	struct playerll *next;
} Playerll;

Playerll *playerll_insert(Playerll *head, Player *p);
void playerll_destroy(Playerll *head);
Player *player_initialize(SDL_Renderer *renderer, int id, int x, int y, SDL_Texture *spritesheet, int tile_size);
void player_destroy(Player *player);
void player_update(Player *player, double delta);
void player_render(SDL_Renderer *renderer, Player *player, Camera cam);
void player_parse_response(SDL_Renderer *renderer, SDL_Texture **textures, char *buffer, Playerll *pll, double delta);

#endif
