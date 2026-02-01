#include "udp_server.h"

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct llnode {
	Player *data;
	struct llnode *next;
} LLNode;

LLNode *player_ll_insertfront(LLNode *head, Player *p);
void player_ll_destroy(LLNode *head);
void player_ll_print(LLNode *head);

#endif
