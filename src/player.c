#include "headers/player.h"
#include "headers/base.h"

Playerll *playerll_insert(Playerll *head, Player *p){
	Playerll *n = malloc(sizeof(Playerll));
	Playerll *ptr = head;
	n->player = p;
	n->next = NULL;
	while (ptr != NULL && ptr->next != NULL){
		ptr = ptr->next;
	}
	if (ptr == NULL){
		return n;
	}
	ptr->next = n;
	return head;
}

void playerll_destroy(Playerll *head){
	if (head == NULL){
		return;
	}
	playerll_destroy(head->next);
	player_destroy(head->player);
	free(head);
}

Player *player_initialize(SDL_Renderer *renderer, int id, int x, int y, const char *spritesheetpath, int tile_size){
	Player *p = malloc(sizeof(Player));
	p->id = id;
	p->x = x;
	p->y = y;
	p->tile_size = tile_size;
	p->state = 'i';
	p->frame_index = 0;
	p->animation_index = 0;
	p->cumilative_delta = 0.0;
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

void player_update(Player *player, double delta){
	player->cumilative_delta += delta;
	if (player->cumilative_delta > 100){
		player->frame_index ++;
		player->frame_index %= 5;
		player->cumilative_delta = 0.0;
	}
	player->isrendered = false;
}

void player_render(SDL_Renderer *renderer, Player *player, Camera cam){
	SDL_Rect src_rect = {
		(int)(player->frame_index) * player->tile_size,
		player->animation_index * player->tile_size,
		player->tile_size,
		player->tile_size
	};
	SDL_Rect dest_rect = {
		player->x - player->tile_size/2 - (int)cam.x + (int)cam.offsetx,
		player->y - player->tile_size/2 - (int)cam.y + (int)cam.offsety,
		player->tile_size,
		player->tile_size
	};
	// SDL_RenderCopy(renderer, player->spritesheet, &src_rect, &dest_rect);
	SDL_RenderCopyEx(renderer, player->spritesheet, &src_rect, &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	player->isrendered = true;
}

void player_parse_response(SDL_Renderer *renderer, char *buffer, Playerll *pll, double delta){
	bool newplayer;
	Playerll *ptr;
	int i, id, x, y;
	char state;
	i=0;
	do {
		id = 0;
		x = 0;
		y = 0;
		for (;buffer[i] != ':'; i++){
			id *= 10;
			id += buffer[i] - '0';
		}
		i++;
		for (;buffer[i] != ':'; i++){
			x *= 10;
			x += buffer[i] - '0';
		}
		i++;
		for (;buffer[i] != ':'; i++){
			y *= 10;
			y += buffer[i] - '0';
		}
		i++;
		state = buffer[i];
		i++;
		ptr = pll;
		newplayer = true;
		while(ptr != NULL){
			Player *p = ptr->player;
			if (p->id == id){
				p->x = x;
				p->y = y;
				p->state = state;
				newplayer = false;
				player_update(ptr->player, delta);
				break;
			}
			ptr = ptr->next;
		}
		if (newplayer){
			pll = playerll_insert(pll, player_initialize(renderer, id, x, y, "./assets/player_spritesheet.png", 64));
		}	
	} while(buffer[++i] != '#');
}
