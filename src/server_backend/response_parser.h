#include <stdbool.h>
#include "a_star_pathfinder.h"

#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

typedef struct Controller {
	int id;
	bool right;
	bool left;
	bool up;
	bool down;
	bool orientation;
	char state;
	float speed;
	A_Grid *pathgrid;
	bool genpath;
} Controller;

void parse_response(char *buffer, Controller *c);

#endif
