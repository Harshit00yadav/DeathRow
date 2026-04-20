#include "datastructures.h"

#define MAPBUFFER 2048

#ifndef MAPLOADER_H
#define MAPLOADER_H

#define TILE_SIZE 32
typedef struct mapObject{
	int tilesize;
	int width;
	int hight;
	char *array;
} mapObject;

mapObject *load_map(const char *path);
int get_map_cordinate_x(int cellx);
int get_map_cordinate_y(int celly);
void destroy_map(mapObject *map);

#endif
