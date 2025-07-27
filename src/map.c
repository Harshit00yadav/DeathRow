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
	Node *ptr = app->map;
	int tile_size = 10;
	int x=0, y=0;
	SDL_Rect sprite_rect = {0, 0, tile_size, tile_size};
	while (ptr != NULL){
		sprite_rect.x = x*tile_size;
		sprite_rect.y = y*tile_size;
		switch (ptr->data){
			case '#':
				SDL_RenderCopy(app->renderer, app->textures[0], NULL, &sprite_rect);
				break;
			case '.':
				SDL_RenderCopy(app->renderer, app->textures[1], NULL, &sprite_rect);
				break;
			case '\n':
				x = -1;
				y++;
				break;
		}
		x++;
		ptr = ptr->next;
	}
}
