#include "headers/event_handler.h"

void event_handler(App *app){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				app_cleanup(app, EXIT_SUCCESS);
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode){
					case SDL_SCANCODE_ESCAPE:
						app_cleanup(app, EXIT_SUCCESS);
						break;
					case SDL_SCANCODE_W:
						app->controller.up = true;
						break;
					case SDL_SCANCODE_S:
						app->controller.down = true;
						break;
					case SDL_SCANCODE_A:
						app->controller.left = true;
						break;
					case SDL_SCANCODE_D:
						app->controller.right = true;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode){
					case SDL_SCANCODE_W:
						app->controller.up = false;
						break;
					case SDL_SCANCODE_S:
						app->controller.down = false;
						break;
					case SDL_SCANCODE_A:
						app->controller.left = false;
						break;
					case SDL_SCANCODE_D:
						app->controller.right = false;
						break;
					default:
						break;
				}
				break;
		}
	}
}
