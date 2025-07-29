#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HIGHT 500
#define SCREEN_TITLE "DeathRow"

#ifndef BASE_H
#define BASE_H

typedef struct Node{
	char data;
	struct Node *next;
} Node;

Node *appendto(Node *head, char data);
void printll(Node *head);
void destroyll(Node *head);

#endif

