#include "headers/camera.h"
#include <stdio.h>

void camera_follow_target(Camera *cam, int x, int y){
	cam->x += (x - cam->x) * 0.1;
	cam->y += (y - cam->y) * 0.1;
}
