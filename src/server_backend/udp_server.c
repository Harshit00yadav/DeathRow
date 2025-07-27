#include "udp_server.h"
#include "datastructures.h"

void player_update(Player *p, Controller *c){
	if (c->right && !c->left){
		p->x += c->speed;
	} else if (c->left && !c->right){
		p->x -= c->speed;
	}
	if (c->down && !c->up){
		p->y += c->speed;
	} else if (c->up && !c->down){
		p->y -= c->speed;
	}
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
		snprintf(b, sizeof(b), "%d:%d:%d:%c ", ptr->data->id, ptr->data->x, ptr->data->y, ptr->data->state);
		strcat(buff, b);
		ptr = ptr->next;
	}
	strcat(buff, "#");
}

int main(){
	int sockfd;
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
			np->x = 0;
			np->y = 0;
			np->state = '.';
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
	close(sockfd);
	return 0;
}
