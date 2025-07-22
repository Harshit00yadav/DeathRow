#include "headers/base.h"

Node *appendto(Node *head, char data){
	Node *n = malloc(sizeof(Node));
	Node *ptr = head;
	n->data = data;
	n->next = NULL;
	if (ptr == NULL){
		return n;
	}
	while (ptr->next != NULL){
		ptr = ptr->next;
	}
	ptr->next = n;
	return head;
}

void printll(Node *head){
	Node *ptr = head;
	while (ptr != NULL){
		printf("%c", ptr->data);
		ptr = ptr->next;
	}
}

void destroyll(Node *head){
	if (head == NULL){
		return;
	} else if (head->next == NULL){
		free(head);
		return;
	}
	destroyll(head->next);
}
