#include "headers/map.h"

Node *load_map(const char *path){
	Node *n = NULL;
	FILE *m = fopen(path, "r");
	char c;
	while ((c = fgetc(m)) != EOF){
		n = appendto(n, c);
	}
	fclose(m);
	return n;
}

SDL_Texture **load_textures(SDL_Renderer *renderer, int n, char **paths){
	SDL_Texture **textures = malloc(sizeof(SDL_Texture *) * n);
	SDL_Surface *surface;
	for (int i=0; i<n; i++){
		surface = IMG_Load(paths[i]);
		if (!surface){
			fprintf(stderr, "[ ERROR ] Unable to load png");
			return NULL;
		}
		textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (!textures[i]){
			fprintf(stderr, "[ ERROR ] Unable to create texture");
			return NULL;
		}
		SDL_SetTextureBlendMode(textures[i], SDL_BLENDMODE_BLEND);
	}
	return textures;
}

void map_destroy_textures(SDL_Texture **textures, int size){
	for (int i=0; i<size; i++){
		SDL_DestroyTexture(textures[i]);
		textures[i] = NULL;
	}
}

void map_render(App *app){
	Playerll *pptr;
	int tile_size = 32;
	int x=0, y=0;
	SDL_Rect sprite_rect = {0, 0, tile_size, tile_size};
	SDL_Rect dest_texture2 = {0, 0, tile_size, tile_size};
	SDL_Rect src_rect = {0, 0, 16, 16};
	SDL_Rect src_texture2 = {0, 0, 16, 16};
	Node *ptr = app->map;
	while (ptr != NULL){
		sprite_rect.x = x*tile_size - app->cam.x + app->cam.offsetx;
		sprite_rect.y = y*tile_size - app->cam.y + app->cam.offsety;
		dest_texture2.x = x*tile_size - app->cam.x + app->cam.offsetx;
		dest_texture2.y = y*tile_size - app->cam.y + app->cam.offsety;
		switch (ptr->data){
			case '\n':
				x = -1;
				y++;
				break;
			case '.':
				src_rect.x = src_rect.w * 0;
				src_rect.y = src_rect.h * 10;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case 'T':
				src_rect.x = src_rect.w * 0;
				src_rect.y = src_rect.h * 10;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				src_texture2.x = 11 * 16;
				src_texture2.y = 0;
				src_texture2.w = 16;
				src_texture2.h = 48;
				dest_texture2.h = tile_size * 3;
				dest_texture2.y -= tile_size * 2;
				SDL_RenderCopy(app->renderer, app->textures[1], &src_texture2, &dest_texture2);
				break;
			case 'A':
				src_rect.x = src_rect.w * 0;
				src_rect.y = src_rect.h * 10;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				src_texture2.x = 10 * 16;
				src_texture2.y = 0;
				src_texture2.w = 16;
				src_texture2.h = 48;
				dest_texture2.h = tile_size * 3;
				dest_texture2.y -= tile_size * 2;
				SDL_RenderCopy(app->renderer, app->textures[1], &src_texture2, &dest_texture2);
				break;
			case '#':
				src_rect.x = src_rect.w * 1;
				src_rect.y = src_rect.h * 7;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
		}
		x++;
		ptr = ptr->next;
	}
	pptr = app->allplayers;
	while (pptr != NULL){
		if (pptr->player->isrendered == false && (pptr->player->y) < y * tile_size){
			player_render(app->renderer, pptr->player, app->cam);
		}
		// printf("%d %d\n", pptr->player->y, sprite_rect.y);
		pptr = pptr->next;
	}
	x=0;
	y=0;
	ptr = app->map;
	while (ptr != NULL){
		sprite_rect.x = x*tile_size - app->cam.x + app->cam.offsetx;
		sprite_rect.y = y*tile_size - app->cam.y + app->cam.offsety;
		dest_texture2.x = x*tile_size - app->cam.x + app->cam.offsetx;
		dest_texture2.y = y*tile_size - app->cam.y + app->cam.offsety;
		switch (ptr->data){
			case '\n':
				x = -1;
				y++;
				break;
			case '#':
				src_rect.x = src_rect.w * 1;
				src_rect.y = src_rect.h * 6;
				dest_texture2.h = tile_size;
				dest_texture2.y -= tile_size;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &dest_texture2);
				break;
		}
		x++;
		ptr = ptr->next;
	}
}
