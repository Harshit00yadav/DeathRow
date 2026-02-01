#ifndef CAMERA_H
#define CAMERA_H

typedef struct Camera{
	float x;
	float y;
	float offsetx;
	float offsety;
	float zoom;
} Camera;

void camera_follow_target(Camera *cam, int x, int y, float follow_strength);

#endif
