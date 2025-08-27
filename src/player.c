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

Player *player_initialize(SDL_Renderer *renderer, int id, int x, int y, SDL_Texture *spritesheet, int tile_size){
	Player *p = malloc(sizeof(Player));
	p->id = id;
	p->x = x;
	p->y = y;
	// orientation false -> facing right 
	// orientation true -> facing left
	p->orientation = false;
	p->tile_size = tile_size;
	p->state = 'i';
	p->state_change = false;
	p->frame_index = 0;
	p->frame_count = 2;
	p->animation_index = 0;
	p->cumilative_delta = 0.0;
	p->spritesheet = spritesheet;
	return p;
}

void player_destroy(Player *player){
	free(player);
}

void player_update(Player *player, double delta){
	if (player->state_change)
		player->frame_index = 0;
	switch(player->state){
		case 'i':
			player->animation_index = 0;
			player->frame_count = 2;
			break;
		case 'r':
			player->animation_index = 1;
			player->frame_count = 4;
			break;
		default:
			break;
	}
	player->cumilative_delta += delta;
	if (player->cumilative_delta > 100){
		player->frame_index ++;
		player->frame_index %= player->frame_count;
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
	int zoom = 2;
	int tsize = player->tile_size * zoom;
	SDL_Rect dest_rect = {
		player->x - tsize/2 - (int)cam.x + (int)cam.offsetx,
		player->y - tsize - (int)cam.y + (int)cam.offsety,
		tsize,
		tsize
	};
	if (player->orientation == 1){
		SDL_RenderCopyEx(renderer, player->spritesheet, &src_rect, &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	} else {
		SDL_RenderCopy(renderer, player->spritesheet, &src_rect, &dest_rect);
	}
	player->isrendered = true;
}

void player_parse_response(SDL_Renderer *renderer, SDL_Texture **textures, char *buffer, Playerll *pll, double delta){
	bool newplayer;
	Playerll *ptr;
	int i, id, x, y;
	bool isneg = false;
	int orientation;
	char state;
	i=0;
	do {
		id = 0;
		x = 0;
		y = 0;
		if (buffer[i] == '-'){
			isneg = true;
			i++;
		} else {
			isneg = false;
		}
		for (;buffer[i] != ':'; i++){
			id *= 10;
			id += buffer[i] - '0';
		}
		if (isneg){
			id = -id;
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
		orientation = buffer[i++] - '0';
		i++;
		state = buffer[i];
		i++;
		ptr = pll;
		newplayer = true;
		printf("%d:%d:%d ", id, x, y);
		while(ptr != NULL){
			Player *p = ptr->player;
			if (p->id == id){
				p->x = x;
				p->y = y;
				if (state != p->state){
					p->state_change = true;
				} else {
					p->state_change = false;
				}
				p->state = state;
				p->orientation = orientation;
				newplayer = false;
				player_update(ptr->player, delta);
				break;
			}
			ptr = ptr->next;
		}
		if (newplayer){
			pll = playerll_insert(pll, player_initialize(renderer, id, x, y, textures[2], 32));
		}	
	} while(buffer[++i] != '#');
}
