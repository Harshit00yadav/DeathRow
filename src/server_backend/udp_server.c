#include "udp_server.h"
#include "guards_ai.h"
#include "datastructures.h"
#include "map_loader.h"

mapObject *map;
int sockfd;


void keyboardInterrupt(int sig){
	printf("Closing Server ...\n");
	close(sockfd);
	destroy_map(map);
	printf("--[ FINISHED ]--\n");
	exit(0);
}

void player_check_collision(Player *p, char ch){
	int indx = (int)(p->x/map->tilesize) + (int)(p->y/map->tilesize) * map->width;
	int x_ = indx % map->width;
	int y_ = (indx - x_) / map->width;
	if (map->array[indx + 1] == ch && p->speed_x > 0){
		if (p->x + p->x_padding + p->speed_x > ((x_ + 1) * map->tilesize) - 0.01){
			p->x = ((x_ + 1) * map->tilesize) - p->x_padding;
			p->speed_x = 0;
		}
	} else if (map->array[indx - 1] == ch && p->speed_x < 0){
		if (p->x - p->x_padding + p->speed_x < (x_ * map->tilesize) + 0.01){
			p->x = (x_ * map->tilesize) + p->x_padding;
			p->speed_x = 0;
		}
	}
	if (map->array[indx + map->width] == ch && p->speed_y > 0){
		if (p->y + p->y_padding + p->speed_y > ((y_ + 1) * map->tilesize) - 0.01){
			p->y = ((y_ + 1) * map->tilesize) - p->y_padding;
			p->speed_y = 0;
		}
	} else if (map->array[indx - map->width] == ch && p->speed_y < 0){
		if (p->y - p->y_padding + p->speed_y < (y_ * map->tilesize) + 0.01){
			p->y = (y_ * map->tilesize) + p->y_padding;
			p->speed_y = 0;
		}
	}
}

void player_update(Player *p, Controller *c){
	float interpolation = 0.08;
	float speedx, speedy;
	c->speed = 5;

	if (c->right && !c->left){
		c->orientation = false;
		speedx = c->speed;
	} else if (c->left && !c->right){
		c->orientation = true;
		speedx = -c->speed;
	} else {
		speedx = 0;
	}
	if (c->down && !c->up){
		speedy = c->speed;
	} else if (c->up && !c->down){
		speedy = -c->speed;
	} else {
		speedy = 0;
	}
	
	if (speedx || speedy){
		c->state = 'r';
	} else {
		c->state = 'i';
	}

	p->speed_x += (speedx - p->speed_x) * interpolation;
	p->speed_y += (speedy - p->speed_y) * interpolation;

	player_check_collision(p, '#');

	p->x += p->speed_x;
	p->y += p->speed_y;
	p->orientaion = c->orientation;
	p->state = c->state;
}

void generate_send_buffer(char *buff, LLNode *head, Controller *c){
	LLNode *ptr = head;
	char b[100];
	strcpy(buff, "");
	while (ptr != NULL){
		if (ptr->data->id == c->id){
			player_update(ptr->data, c);
		}
		snprintf(
			b,
			sizeof(b),
			"%d:%.0f:%0.f:%b:%c ",
			ptr->data->id,
			ptr->data->x,
			ptr->data->y,
			ptr->data->orientaion,
			ptr->data->state
		);
		strcat(buff, b);
		ptr = ptr->next;
	}
	strcat(buff, "#");
}

int main(){
	map = load_map("./assets/map01.txt");
	signal(SIGINT, keyboardInterrupt);
	char buffer[BUFFER_SIZE];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		perror("[ ERROR ] Socket Creation Failed.");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("[ ERROR ] Bind Failed.");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	printf("UDP server listening on port: %d \n", PORT);

	LLNode *players = NULL;
	int ID = 0;
	players = guards_init(1, players);
	pthread_t guard_tread_id;
	pthread_create(&guard_tread_id, NULL, guards_thread_function, (void *)players);
	while (true){
		int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
		if (n < 0){
			perror("[ ERROR ] recvfrom error.");
			continue;
		}
		buffer[n] = '\0';
		char reply[500];
		if (strcmp(buffer, "connect") == 0){
			Player *np = malloc(sizeof(Player));
			np->id = ID;
			np->x = 150;
			np->y = 150;
			np->x_padding = 10;
			np->y_padding = 10;
			np->speed_x = 0;
			np->speed_y = 0;
			np->state = '.';
			np->orientaion = false;
			players = player_ll_insertfront(players, np);
			player_ll_print(players);
			snprintf(reply, sizeof(reply), "%d", ID++);
		} else {
			Controller c;
			parse_response(buffer, &c);
			generate_send_buffer(reply, players, &c);
		}
		sendto(sockfd, reply, strlen(reply), 0, (const struct sockaddr *)&client_addr, addr_len);
	}
	return 0;
}
