#include "headers/datastructures.h"
#include <stdlib.h>

void ll_insertfront(LinkedList *list, void *item)
{
	NodeLL *new_node = (NodeLL *)malloc(sizeof(NodeLL));
	new_node->data = item;
	new_node->next = list->head;
	list->head = new_node;
	list->size++;
}

void nodell_teardown(NodeLL *head)
{
	while (head){
		NodeLL *next = head->next;
		free(head);
		head = next;
	}
}

void ll_teardown(LinkedList *list)
{
	nodell_teardown(list->head);
	list->head = NULL;
	list->size = 0;
	free(list);
}

void ll_print(LinkedList *list)
{
	NodeLL *t_ptr = list->head;
	printf("size: %zu\n", list->size);
	while (t_ptr != NULL){
		printf("󱀝  ");
		t_ptr = t_ptr->next;
	}
	printf("null\n");
}
