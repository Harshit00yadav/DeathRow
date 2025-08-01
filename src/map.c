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
	Node *ptr = app->map;
	int tile_size = 32;
	int x=0, y=0;
	SDL_Rect sprite_rect = {0, 0, tile_size, tile_size};
	SDL_Rect src_rect = {0, 0, 16, 16};
	while (ptr != NULL){
		sprite_rect.x = x*tile_size - app->cam.x + app->cam.offsetx;
		sprite_rect.y = y*tile_size - app->cam.y + app->cam.offsety;
		src_rect.x = src_rect.w * 0;
		src_rect.y = src_rect.h * 10;
		SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
		switch (ptr->data){
			case '\n':
				src_rect.x = src_rect.w * 14;
				src_rect.y = src_rect.h * 5;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				x = -1;
				y++;
				break;
			case '^':
				src_rect.x = src_rect.w * 14;
				src_rect.y = src_rect.h * 5;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '*':
				src_rect.x = src_rect.w * 16;
				src_rect.y = src_rect.h * 5;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '+':
				src_rect.x = src_rect.w * 10;
				src_rect.y = src_rect.h * 4;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '0':
				src_rect.x = src_rect.w * 2;
				src_rect.y = src_rect.h * 11;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '1':
				src_rect.x = src_rect.w * 3;
				src_rect.y = src_rect.h * 10;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '_':
				src_rect.x = src_rect.w * 2;
				src_rect.y = src_rect.h * 3;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '-':
				src_rect.x = src_rect.w * 1;
				src_rect.y = src_rect.h * 7;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				src_rect.x = src_rect.w * 2;
				src_rect.y = src_rect.h * 1;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '/':
				src_rect.x = src_rect.w * 3;
				src_rect.y = src_rect.h * 2;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '\\':
				src_rect.x = src_rect.w * 1;
				src_rect.y = src_rect.h * 2;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '7':
				src_rect.x = src_rect.w * 9;
				src_rect.y = src_rect.h * 4;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '5':
				src_rect.x = src_rect.w * 10;
				src_rect.y = src_rect.h * 4;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case '6':
				src_rect.x = src_rect.w * 11;
				src_rect.y = src_rect.h * 4;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case 'l':
				src_rect.x = src_rect.w * 6;
				src_rect.y = src_rect.h * 8;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				src_rect.x = src_rect.w * 9;
				src_rect.y = src_rect.h * 3;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case 'L':
				src_rect.x = src_rect.w * 7;
				src_rect.y = src_rect.h * 8;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				src_rect.x = src_rect.w * 10;
				src_rect.y = src_rect.h * 3;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case 'M':
				src_rect.x = src_rect.w * 7;
				src_rect.y = src_rect.h * 8;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				src_rect.x = src_rect.w * 11;
				src_rect.y = src_rect.h * 3;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
			case 'H':
				src_rect.x = src_rect.w * 1;
				src_rect.y = src_rect.h * 7;
				SDL_RenderCopy(app->renderer, app->textures[0], &src_rect, &sprite_rect);
				break;
		}
		x++;
		ptr = ptr->next;
	}
}
