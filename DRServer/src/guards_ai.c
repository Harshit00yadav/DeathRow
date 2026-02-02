#include "headers/guards_ai.h"
#include "headers/a_star_pathfinder.h"

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

void guards_init(size_t n, LinkedList *players){
	for (int i=0; i<n; i++){
		Player *new_player = malloc(sizeof(Player));
		new_player->id = -1 * (i+1);
		new_player->x = 150 + 100 * i;
		new_player->y = 250;
		new_player->x_padding = 10;
		new_player->y_padding = 10;
		new_player->speed_x = 0;
		new_player->speed_y = 0;
		new_player->state = '.';
		new_player->orientaion = false;
		ll_insertfront(players, (void *)new_player);
	}
}

void *guards_thread_function(void *args){
	LinkedList *players = (LinkedList *)args;
	size_t count;
	count = players->size;
	Controller *cntrls = calloc(count, sizeof(*cntrls));
	if (!cntrls) {
		pthread_exit(NULL);
	}
	// Controller cntrls[players->size];
	for (NodeLL *ptr=players->head; ptr!=NULL; ptr=ptr->next){
		int tmp_id = ((Player *)ptr->data)->id;
		int indx = (tmp_id * -1) - 1;
		cntrls[indx].left = false;
		cntrls[indx].right = false;
		cntrls[indx].up = false;
		cntrls[indx].down = false;
		cntrls[indx].orientation = false;
		cntrls[indx].id = ((Player *)ptr->data)->id;
		cntrls[indx].orientation = 0;
		cntrls[indx].state = '.';
		cntrls[indx].pathgrid = load_a_map("../assets/map01.txt");
		cntrls[indx].genpath = true;
	}
	// ------
	int row, col;
	A_Cell *cur_cell = NULL, *target_cell = NULL;
	// target_cell = &cntrls[1].pathgrid->grid[1][1];
	msleep(3000);
	Player *ptr_data;
	while (true){
		for (NodeLL *ptr=players->head; ptr!=NULL; ptr=ptr->next){
			ptr_data = ptr->data;
			int indx = (ptr_data->id * -1) - 1;
			if (ptr_data->id < 0){
				row = (ptr_data->y / 32);
				col = (ptr_data->x / 32);
				cur_cell = &cntrls[indx].pathgrid->grid[row][col];
				if (cntrls[indx].genpath){
					cntrls[indx].pathgrid = generate_route(
						cntrls[indx].pathgrid,
						row,
						col,
						18,
						53
					);
					target_cell = cur_cell->previous;
					cntrls[indx].genpath = false;
				};
				// DONE: makes the guard follow the path
				if (target_cell){
					if (cur_cell == target_cell){
						target_cell =  cur_cell->previous;
					} else {
						if (ptr_data->x - ptr_data->x_padding < target_cell->col * 32){
							cntrls[indx].right = true;
							cntrls[indx].left = false;
						} else if (ptr_data->x + ptr_data->x_padding > target_cell->col * 32 + 32){
							cntrls[indx].left = true;
							cntrls[indx].right = false;
						} else {
							cntrls[indx].right = false;
							cntrls[indx].left = false;
						}
						if (ptr_data->y - ptr_data->y_padding < target_cell->row * 32){
							cntrls[indx].down = true;
							cntrls[indx].up = false;
						} else if (ptr_data->y + ptr_data->y_padding > target_cell->row * 32 + 32){
							cntrls[indx].up = true;
							cntrls[indx].down = false;
						} else {
							cntrls[indx].up = false;
							cntrls[indx].down = false;
						}
					}
				} else {
					cntrls[indx].right = false;
					cntrls[indx].left = false;
					cntrls[indx].up = false;
					cntrls[indx].down = false;
				}
				player_update(ptr_data, &cntrls[indx]);
			}
		}
		msleep(1000/60);
	}
	pthread_exit(NULL);
}
