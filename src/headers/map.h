#include "application.h"

#ifndef MAPHEADER_H
#define MAPHEADER_H

#endif

Node *load_map(const char *path);
SDL_Texture **load_textures(SDL_Renderer *renderer, int n, char **paths);
void map_destroy_textures(SDL_Texture **textures, int size);
void map_render(App *app);
