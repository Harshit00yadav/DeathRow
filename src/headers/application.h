#include "base.h"
#ifndef APPLICATION_H
#define APPLICATION_H
typedef struct App {
	SDL_Window *window;
	SDL_Renderer *renderer;
	int mouseX;
	int mouseY;
} App;
#endif
bool sdl_init(App *app);
void app_cleanup(App *app, int exit_status);
void update(App *app);
void render(App *app);
