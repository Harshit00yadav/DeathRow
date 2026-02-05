#include "udp_server.h"
#include "datastructures.h"
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#ifndef GUARDSAI_H
#define GUARDSAI_H

#define AI_STAY_MODE 0
#define AI_PATROL_MODE 1
#define DEFAULT_STATE_INERTIA 60*3
#define DEFAULT_PATROL_MIN -2
#define DEFAULT_PATROL_MAX 2

typedef struct AI_Attributes {
	int t_row;
	int t_col;
	int state_inertia;
	bool find_path;
	bool reached;
	A_Cell *target;
	int mode;
} AI_Behaviour_Attributes;

void guards_init(size_t n, LinkedList *players);
bool guards_follow_target(A_Cell **target, A_Cell *current, Player *guard, Controller *guard_controller);
void *guards_thread_function(void *args);
int msleep(long msec);
#endif
