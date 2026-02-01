#include "headers/response_parser.h"
#include "headers/udp_server.h"

void parse_response(char *buffer, Controller *c){
	c->id = 0;
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
	c->orientation = buffer[i++] - '0';
	i++;
	c->state = buffer[i];
	c->pathgrid = NULL;
	c->genpath = false;
}
