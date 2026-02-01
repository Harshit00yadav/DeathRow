#include "headers/camera.h"

void camera_follow_target(Camera *cam, int x, int y, float follow_strength){
	cam->x += (x - cam->x) * follow_strength;
	cam->y += (y - cam->y) * follow_strength;
}
