#include "headers/application.h"

int sdl_init(App *app){
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error Initializing SDL: %s\n", SDL_GetError());
		return true;
	}
	app->window = SDL_CreateWindow(
		SCREEN_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HIGHT,
		0
	);
	if (!app->window){
		fprintf(stderr, "Error Creating Window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	app->renderer = SDL_CreateRenderer(app->window, -1, 0);
	if (!app->renderer){
		fprintf(stderr, "Error Creating Renderer: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	if (socket_initialization(&app->conn)){
		return EXIT_FAILURE;
	}
	app->server_response = malloc(sizeof(char) * BUFFER_SIZE);
	if (app->server_response == NULL){
		fprintf(stderr, "Unable to allocate memory.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void app_cleanup(App *app, int exit_status){
	free(app->server_response);
	destroy_socket(&app->conn);
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
	printf("--[ FINISHED ]--\n");
	exit(exit_status);
}

void update(App *app){
	send_data(&app->conn, "faltu data 2");
	recv_data(&app->conn, app->server_response);
	printf("%s\n", app->server_response);
	SDL_Delay(128);
}

void render(App *app){
	SDL_SetRenderDrawColor(app->renderer, 15, 15, 15, 255);
	SDL_RenderClear(app->renderer);
	SDL_RenderPresent(app->renderer);
}
