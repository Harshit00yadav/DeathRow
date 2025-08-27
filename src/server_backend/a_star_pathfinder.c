#include "a_star_pathfinder.h"

/*

Compile and test:
gcc a_star_pathfinder.c -o test_feature;./test_feature;rm ./test_feature 

*/

A_Grid *load_map(const char *path){
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
		}
	}
	return grid;
}

void printgrid(A_Grid *grid){
	system("clear");
	for (int i=0; i<grid->hight; i++){
		for (int j=0; j<grid->width; j++){
			printf("%c", grid->grid[i][j].ch);
		}
		printf("\n");
	}
}

int main(){
	A_Grid *grid = load_map("../../assets/map01.txt");
	grid->grid[1][1].ch = '@';
	grid->grid[17][10].ch = '#';
	printgrid(grid);
	return 0;
}
