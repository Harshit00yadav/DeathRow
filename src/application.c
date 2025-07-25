#include "headers/map.h"

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
	app->map = load_map("./assets/map01.txt");
	app->ntextures = 2;
	char *paths[] = {"./assets/wallfront.png", "./assets/grass01.png"};
	app->textures = load_textures(app->renderer, app->ntextures, paths);
	if (!app->textures){
		fprintf(stderr, "Unable to load images.\n");
		return EXIT_FAILURE;
	}
	app->player = player_initialize(app->renderer, 20, 40, "./assets/player_spritesheet.png", 64);
	if (!app->player){
		fprintf(stderr, "Unable to load images.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void app_cleanup(App *app, int exit_status){
	player_destroy(app->player);
	map_destroy_textures(app->textures, app->ntextures);
	destroyll(app->map);
	free(app->server_response);
	destroy_socket(&app->conn);
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
	printf("--[ FINISHED ]--\n");
	exit(exit_status);
}

void update(App *app){
	char data[50];
	snprintf(data, sizeof(data), "x: %d, y: %d", app->player->x, app->player->y);
	send_data(&app->conn, data);
	recv_data(&app->conn, app->server_response);
	player_update(app->player);
	// printf("%s\n", app->server_response);
	SDL_Delay(128);
}

void render(App *app){
	SDL_SetRenderDrawColor(app->renderer, 15, 15, 15, 255);
	SDL_RenderClear(app->renderer);
	map_render(app);
	player_render(app->renderer, app->player);
	SDL_RenderPresent(app->renderer);
}
