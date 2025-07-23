#include "headers/player.h"
#include "headers/base.h"

Player *player_initialize(SDL_Renderer *renderer, int x, int y, const char *spritesheetpath, int tile_size){
	Player *p = malloc(sizeof(Player));
	p->x = x;
	p->y = y;
	p->tile_size = tile_size;
	p->state = "idle";
	SDL_Surface *surface = IMG_Load(spritesheetpath);
	p->spritesheet = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!p->spritesheet) {
		fprintf(stderr, "[ ERROR ] Unable to load player sprite sheet\n");
		return NULL;
	}
	return p;
}

void player_destroy(Player *player){
	SDL_DestroyTexture(player->spritesheet);
	free(player);
}

void player_render(SDL_Renderer *renderer, Player *player){
	SDL_Rect src_rect = {0, 0, player->tile_size, player->tile_size};
	SDL_Rect dest_rect = {player->x, player->y, player->tile_size, player->tile_size};
	SDL_RenderCopy(renderer, player->spritesheet, &src_rect, &dest_rect);
}

void player_update(Player *player){
	player->x++;
}
