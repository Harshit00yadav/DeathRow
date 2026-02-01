#include "datastructures.h"

#define MAPBUFFER 2048

#ifndef MAPLOADER_H
#define MAPLOADER_H

typedef struct mapObject{
	int tilesize;
	int width;
	int hight;
	char *array;
} mapObject;

mapObject *load_map(const char *path);
void destroy_map(mapObject *map);

#endif
