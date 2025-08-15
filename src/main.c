#include "headers/application.h"
#include "headers/event_handler.h"

void initialize(App *app){
	if (sdl_init(app)){
		app_cleanup(app, EXIT_FAILURE);
	}
}

int main()
{
	Uint64 now, last;
	double delta=0, fps=0;
	now = SDL_GetPerformanceCounter();
	last = 0;
	App app;
	initialize(&app);
	while (true){
		last = now;
		now = SDL_GetPerformanceCounter();
		delta = (double)((now - last) * 1000) / SDL_GetPerformanceFrequency();  // miliseconds
		fps = 1000.0/delta;
		SDL_GetMouseState(&app.mouseX, &app.mouseY);
		event_handler(&app);
		update(&app, delta);
		render(&app);
		SDL_Delay(TIME_PER_FRAME);
		printf("FPS: %.2f\n", fps);
	}
	app_cleanup(&app, EXIT_SUCCESS);
	return 0;
}
