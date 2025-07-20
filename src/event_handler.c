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
					default:
						break;
				}
				break;
		}
	}
}
