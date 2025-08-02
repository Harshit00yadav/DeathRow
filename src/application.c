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
	char *paths[] = {"./assets/neo_zero_tileset_02.png", "./assets/neo_zero_props_02_free.png"};
	app->textures = load_textures(app->renderer, app->ntextures, paths);
	if (!app->textures){
		fprintf(stderr, "\n[ ERROR ] Unable to load images.\n");
		return EXIT_FAILURE;
	}
	char buf[100];
	send_data(&app->conn, "connect");
	recv_data(&app->conn, buf);
	app->ID = atoi(buf);
	printf("ID assigned: %d\n", app->ID);
	app->allplayers = NULL;
	app->allplayers = playerll_insert(app->allplayers, player_initialize(app->renderer, app->ID, 20, 40, "./assets/player_spritesheet.png", 64));
	if (!app->allplayers->player){
		fprintf(stderr, "Unable to load images.\n");
		return EXIT_FAILURE;
	}
	app->controller.right = false;
	app->controller.left = false;
	app->controller.up = false;
	app->controller.down = false;
	app->controller.x = 0;
	app->controller.y = 0;
	app->cam.x = 0;
	app->cam.y = 0;
	app->cam.offsetx = (float)SCREEN_WIDTH / 2;
	app->cam.offsety = (float)SCREEN_HIGHT / 2;
	app->cam.zoom = 1;
	return EXIT_SUCCESS;
}

void app_cleanup(App *app, int exit_status){
	playerll_destroy(app->allplayers);
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

void update(App *app, double delta){
	char data[50];
	Player *p = app->allplayers->player;
	snprintf(
		data,
		sizeof(data),
		"%d:%b:%b:%b:%b:%c",
		app->ID,
		app->controller.right,
		app->controller.left,
		app->controller.up,
		app->controller.down,
		p->state
	);
	send_data(&app->conn, data);
	recv_data(&app->conn, app->server_response);
	player_parse_response(app->renderer, app->server_response, app->allplayers, delta);
	camera_follow_target(&app->cam, p->x, p->y);
	SDL_Delay(32);
}

void render(App *app){
	SDL_SetRenderDrawColor(app->renderer, 15, 15, 15, 255);
	SDL_RenderClear(app->renderer);
	map_render(app);
	SDL_RenderPresent(app->renderer);
}
