#include <stdbool.h>

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
	int speed;
} Controller;

void parse_response(char *buffer, Controller *c);

#endif
