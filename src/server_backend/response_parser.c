#include "response_parser.h"
#include "udp_server.h"

void parse_response(char *buffer, Controller *c){
	c->id = 0;
	c->state = '.';
	int i=0;
	for (;buffer[i] != ':'; i++){
		c->id *= 10;
		c->id += buffer[i] - '0';
	}
	i++;
	c->right = buffer[i++] - '0';
	i++;
	c->left = buffer[i++] - '0';
	i++;
	c->up = buffer[i++] - '0';
	i++;
	c->down = buffer[i++] - '0';
	i++;
	c->state = buffer[i];
	c->speed = 10;
}
