#include "a_star_pathfinder.h"
#include <time.h>
#include <errno.h>

/*

Compile and test:
gcc a_star_pathfinder.c -o test_feature -Wall -lm -g;./test_feature;rm ./test_feature 


int msleep(long msec){
    struct timespec ts;
    int res;
    if (msec < 0){
        errno = EINVAL;
        return -1;
    }
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
    return res;
}
*/

bool A_List_contains(A_List *head, A_Cell *cellptr){
	A_List *ptr = head;
	while (ptr){
		if (ptr->data == cellptr){
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

A_List *A_List_insert(A_List *head, A_Cell *cellptr){
	A_List *node = (A_List *)malloc(sizeof(A_List));
	node->data = cellptr;
	node->next = head;
	return node;
}

A_List *A_List_remove(A_List *head, A_Cell *cellptr){
	A_List *ptr = head;
	A_List *nextptr;
	if (ptr->data == cellptr){
		return ptr->next;
	}
	while (ptr && ptr->next){
		nextptr = ptr->next;
		if (nextptr->data == cellptr){
			ptr->next = ptr->next->next;
			free(nextptr);
		}
		ptr = ptr->next;
	}
	return head;
}

void A_List_destroy(A_List *head){
	A_List *ptr = head;
	A_List *nextptr;
	while (ptr){
		nextptr = ptr->next;
		free(ptr);
		ptr = nextptr;
	}
}

A_Grid *load_a_map(const char *path){
	FILE *fd = fopen(path, "r");
	char c;
	char buffer[2048];
	int i=0;
	int width=0, w=0;
	int hight=0;
	while ((c = fgetc(fd)) != EOF){
		if (c == '\n'){
			w=-1;
			hight++;
			continue;
		}
		w++;
		if (w>width){
			width = w;
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	fclose(fd);
	A_Grid *grid = malloc(sizeof(A_Grid));
	grid->width = width;
	grid->hight = hight;
	grid->grid = (A_Cell **)malloc(sizeof(A_Cell*) * hight);
	A_Cell *cell;
	for (int i=0; i<hight; i++){
		grid->grid[i] = (A_Cell *)malloc(sizeof(A_Cell) * width);
		for (int j=0; j<width; j++){
			cell = &grid->grid[i][j]; 
			cell->ch = buffer[j+i*width];
			cell->f = 0;
			cell->g = 0;
			cell->h = 0;
			cell->row = i;
			cell->col = j;
			cell->n_neighbours = 4;
			cell->neighbours = (A_Cell **)malloc(sizeof(A_Cell *) * cell->n_neighbours);
			cell->previous = NULL;
		}
	}
	for (int i=0; i<hight; i++){
		for (int j=0; j<width; j++){
			cell = &grid->grid[i][j];
			cell->neighbours[0] = (i<0)?NULL:&grid->grid[i-1][j];
			cell->neighbours[2] = (i>=hight)?NULL:&grid->grid[i+1][j];
			cell->neighbours[1] = (j>=width)?NULL:&grid->grid[i][j+1];
			cell->neighbours[3] = (j<0)?NULL:&grid->grid[i][j-1];
		}
	}
	return grid;
}

void destroy_grid(A_Grid *grid){
	A_Cell *cell;
	for (int i=0; i<grid->hight; i++){
		for (int j=0; j<grid->width; j++){
			cell = &grid->grid[i][j]; 
			free(cell->neighbours);
		}
		free(grid->grid[i]);
	}
	free(grid->grid);
	free(grid);
}

void printgrid(A_Grid *grid){
	for (int i=0; i<grid->hight; i++){
		for (int j=0; j<grid->width; j++){
			printf("%c", grid->grid[i][j].ch);
		}
		printf("\n");
	}
}

A_Cell *least_f(A_List *head){
	A_List *ptr = head;
	A_Cell *cellptr = NULL;
	while (ptr){
		if (cellptr == NULL || ptr->data->f < cellptr->f){
			cellptr = ptr->data;
		}
		ptr = ptr->next;
	}
	return cellptr;
}

double heuristic_cost(int startx, int starty, int endx, int endy){
	double res;
	res = sqrt(pow(endx - startx, 2) + pow(endy - starty, 2));
	return res;
}

A_Grid *generate_route(A_Grid *grid, int startrow, int startcol, int endrow, int endcol){
	bool path_found = false;
	A_Cell *end = &grid->grid[startrow][startcol];
	A_Cell *ptr = end;
	A_List *openlist = NULL;
	A_List *closedlist = NULL;
	openlist = A_List_insert(openlist, &grid->grid[endrow][endcol]);

	while (openlist != NULL){
		A_Cell *current = least_f(openlist);
		if (current == end){
			path_found = true;
			printf("Done!\n");
			break;
		}

		// check neighbours
		for (int i=0; i<current->n_neighbours; i++){
			A_Cell *neighbour = current->neighbours[i];
			if (!neighbour || neighbour->ch != '.'){
				continue;
			}
			if (A_List_contains(closedlist, neighbour)){
				continue;
			}
			double tempG = current->g + 1;
			if (!A_List_contains(openlist, neighbour)){
				openlist = A_List_insert(openlist, neighbour);
			} else if (neighbour->g <= tempG){
				continue;
			}
			neighbour->previous = current;
			neighbour->g = tempG;
			neighbour->h = heuristic_cost(neighbour->col, neighbour->row, end->col, end->row);
			neighbour->f = neighbour->g + neighbour->h;
		}
		
		closedlist = A_List_insert(closedlist, current);
		openlist = A_List_remove(openlist, current);
	}
	A_List_destroy(openlist);
	A_List_destroy(closedlist);
	if (path_found){
		while (ptr->previous){
			ptr->ch = '*';
			ptr = ptr->previous;
		}
		printf("Path Found!\nGrid:%p cell:%p: (%d, %d)\n", grid, end, end->col, end->row);
	} else {
		printf("Path NOT Found!\n");
	}
	return grid;
}

//int main(){
//	A_Grid *grid = load_a_map("../../assets/map01.txt");
//	A_Cell *cur = &grid->grid[2][2];
//	printgrid(grid);
//	printf("\n%p\n", cur->previous);
//	msleep(100);
//	grid = generate_route(grid, 2, 2, 28, 48);
//	while (cur->previous){
//		cur->ch = '@';
//		printgrid(grid);
//		printf("\n%p\n", cur->previous);
//		cur->ch = '+';
//		cur = cur->previous;
//		msleep(100);
//	}
//	destroy_grid(grid);
//	return 0;
//}
