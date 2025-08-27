#include <stdio.h>
#include <stdlib.h>

#ifndef ASTARTPATHFINDER_H
#define ASTARTPATHFINDER_H

typedef struct A_CELL {
	char ch;
	int f;
	int g;
	int h;
} A_Cell;

typedef struct A_GRID {
	A_Cell **grid; // grid[i][j] : i->row|y, j->col|x
	int width;
	int hight;
} A_Grid;

A_Grid *load_map(const char *path);
void printgrid(A_Grid *grid);
#endif
