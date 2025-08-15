#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef BASE_H
#define BASE_H

#define SCREEN_WIDTH 800
#define SCREEN_HIGHT 500
#define SCREEN_TITLE "DeathRow"
#define FPS_TARGET 60
#define TIME_PER_FRAME 1000.0/FPS_TARGET

typedef struct Node{
	char data;
	struct Node *next;
} Node;

Node *appendto(Node *head, char data);
void printll(Node *head);
void destroyll(Node *head);

#endif

