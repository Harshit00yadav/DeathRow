#include "datastructures.h"
#include <stdlib.h>

LLNode *player_ll_insertfront(LLNode *head, Player *p){
	LLNode *n = malloc(sizeof(LLNode));
	n->data = p;
	n->next = head;
	return n;
}

void player_ll_destroy(LLNode *head){
	if (head == NULL){
		return;
	}
	player_ll_destroy(head->next);
	free(head->data);
	free(head);
}

void player_ll_print(LLNode *head){
	LLNode *ptr = head;
	while (ptr != NULL){
		Player *p = ptr->data;
		printf("%d:%.0f:%.0f:%c -> ", p->id, p->x, p->y, p->state);
		ptr = ptr->next;
	}
	printf("NULL\n");
}
