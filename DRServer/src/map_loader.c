#include "headers/map_loader.h"

mapObject *load_map(const char *path){
	mapObject *obj = malloc(sizeof(mapObject));
	FILE *m = fopen(path, "r");
	obj->array = calloc(MAPBUFFER, sizeof(char));
	obj->width = -1;
	obj->hight = -1;
	obj->tilesize = 32;
	char c;
	int i = 0;
	while ((c = fgetc(m)) != EOF){
		obj->array[i++] = c;
		if (obj->width == -1 && c == '\n'){
			obj->width = i;
		}
	}
	obj->hight = i / obj->width;
	fclose(m);
	return obj;
}

void destroy_map(mapObject *map){
	free(map->array);
	free(map);
}
