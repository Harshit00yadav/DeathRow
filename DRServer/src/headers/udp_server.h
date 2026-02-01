#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "response_parser.h"
#include <signal.h>

#define PORT 8008
#define BUFFER_SIZE 1024

#ifndef UDPSERVER_H
#define UDPSERVER_H

typedef struct player {
	int id;
	float x;
	float y;
	bool orientaion;
	char state;
	float speed_x;
	float speed_y;
	float x_padding;
	float y_padding;
} Player;

void player_update(Player *p, Controller *c);

#endif
