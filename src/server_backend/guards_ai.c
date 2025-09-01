#include "guards_ai.h"
#include "a_star_pathfinder.h"

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

LLNode *guards_init(size_t n, LLNode *players){
	for (int i=0; i<n; i++){
		Player *np = malloc(sizeof(Player));
		np->id = -1 * (i+1);
		np->x = 150 + 100 * i;
		np->y = 250;
		np->x_padding = 10;
		np->y_padding = 10;
		np->speed_x = 0;
		np->speed_y = 0;
		np->state = '.';
		np->orientaion = false;
		players = player_ll_insertfront(players, np);
	}
	return players;
}

void *guards_thread_function(void *args){
	LLNode *players = (LLNode *)args;

	// --- controllers ---
	int count = 0;
	for (LLNode *ptr=players; ptr!=NULL; ptr=ptr->next){
		count++;
	}
	Controller cntrls[count];
	int i = 0;
	for (LLNode *ptr=players; ptr!=NULL; ptr=ptr->next, i++){
		cntrls[i].left = false;
		cntrls[i].right = false;
		cntrls[i].up = false;
		cntrls[i].down = false;
		cntrls[i].orientation = false;
		cntrls[i].id = ptr->data->id;
		cntrls[i].orientation = 0;
		cntrls[i].state = '.';
		cntrls[i].pathgrid = load_a_map("./assets/map01.txt");
		cntrls[i].genpath = true;
	}
	// ------
	int row, col;
	A_Cell *cur_cell = NULL, *target_cell = NULL;
	// target_cell = &cntrls[1].pathgrid->grid[1][1];
	msleep(3000);
	while (true){
		i = 0;
		for (LLNode *ptr=players; ptr!=NULL; ptr=ptr->next, i++){
			if (ptr->data->id < 0){
				row = (ptr->data->y / 32);
				col = (ptr->data->x / 32);
				cur_cell = &cntrls[i].pathgrid->grid[row][col];
				if (cntrls[i].genpath){
					cntrls[i].pathgrid = generate_route(
						cntrls[i].pathgrid,
						row,
						col,
						18,
						53
					);
					target_cell = cur_cell->previous;
					cntrls[i].genpath = false;
				};
				// DONE: makes the guard follow the path
				if (target_cell){
					if (cur_cell == target_cell){
						target_cell =  cur_cell->previous;
					} else {
						if (ptr->data->x - ptr->data->x_padding < target_cell->col * 32){
							cntrls[i].right = true;
							cntrls[i].left = false;
						} else if (ptr->data->x + ptr->data->x_padding > target_cell->col * 32 + 32){
							cntrls[i].left = true;
							cntrls[i].right = false;
						} else {
							cntrls[i].right = false;
							cntrls[i].left = false;
						}
						if (ptr->data->y - ptr->data->y_padding < target_cell->row * 32){
							cntrls[i].down = true;
							cntrls[i].up = false;
						} else if (ptr->data->y + ptr->data->y_padding > target_cell->row * 32 + 32){
							cntrls[i].up = true;
							cntrls[i].down = false;
						} else {
							cntrls[i].up = false;
							cntrls[i].down = false;
						}
					}
				} else {
					cntrls[i].right = false;
					cntrls[i].left = false;
					cntrls[i].up = false;
					cntrls[i].down = false;
				}
				player_update(ptr->data, &cntrls[i]);
			}
		}
		msleep(1000/60);
	}
	pthread_exit(NULL);
}
