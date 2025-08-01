#include "client.h"
#include "player.h"
#include "camera.h"

#ifndef APPLICATION_H
#define APPLICATION_H

typedef struct App {
	int ID;
	SDL_Window *window;
	SDL_Renderer *renderer;
	char *server_response;
	UDPcon conn;
	pthread_t listener_thread_id;
	int mouseX;
	int mouseY;
	Node *map;
	SDL_Texture **textures;
	int ntextures;
	Playerll *allplayers;
	Controller controller;
	Camera cam;
} App;

int sdl_init(App *app);
void app_cleanup(App *app, int exit_status);
void update(App *app, double delta);
void render(App *app);

#endif
