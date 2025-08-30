#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#ifndef ASTARTPATHFINDER_H
#define ASTARTPATHFINDER_H

typedef struct A_CELL {
	char ch;
	double f;
	double g;
	double h;
	int row;
	int col;
	int n_neighbours;
	struct A_CELL **neighbours;
	struct A_CELL *previous;
} A_Cell;

typedef struct A_GRID {
	A_Cell **grid; // grid[i][j] : i->row|y, j->col|x
	int width;
	int hight;
} A_Grid;

typedef struct A_LIST {
	A_Cell *data;
	struct A_LIST *next;
} A_List;

A_List *A_List_insert(A_List *head, A_Cell *cellptr);
A_List *A_List_remove(A_List *head, A_Cell *cellptr);
void A_List_destroy(A_List *head);
bool A_List_contains(A_List *head, A_Cell *cellptr);
A_Cell *least_f(A_List *head);
A_Grid *load_a_map(const char *path);
double heuristic_cost(int startx, int starty, int endx, int endy);
void printgrid(A_Grid *grid);
A_Grid *generate_route(A_Grid *grid, int startrow, int startcol, int endrow, int endcol);
void destroy_grid(A_Grid *grid);
#endif
