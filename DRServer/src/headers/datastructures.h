#include "udp_server.h"

#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

typedef struct NodeLL {
	void *data;
	struct NodeLL *next;
} NodeLL;

typedef struct linkedlist {
	NodeLL *head;
	size_t size;
} LinkedList;

void ll_insertfront(LinkedList *list, void *item);
void ll_teardown(LinkedList *list);
void ll_print(LinkedList *list);

#endif
