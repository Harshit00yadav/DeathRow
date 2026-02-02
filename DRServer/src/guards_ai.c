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

bool guards_follow_target(A_Cell **target, A_Cell *current, Player *guard, Controller *guard_controller){
	if (*target){
		if (current == *target){
			*target = current->previous;
		} else {
			if (guard->x - guard->x_padding < (*target)->col * 32){
				guard_controller->right = true;
				guard_controller->left = false;
			} else if (guard->x + guard->x_padding > (*target)->col * 32 + 32){
				guard_controller->left = true;
				guard_controller->right = false;
			} else {
				guard_controller->right = false;
				guard_controller->left = false;
			}
			if (guard->y - guard->y_padding < (*target)->row * 32){
				guard_controller->down = true;
				guard_controller->up = false;
			} else if (guard->y + guard->y_padding > (*target)->row * 32 + 32){
				guard_controller->up = true;
				guard_controller->down = false;
			} else {
				guard_controller->up = false;
				guard_controller->down = false;
			}
		}
		return false;
	} else {
		guard_controller->right = false;
		guard_controller->left = false;
		guard_controller->up = false;
		guard_controller->down = false;
		return true;
	}
}

void *guards_thread_function(void *args){
	LinkedList *players = (LinkedList *)args;
	size_t count;
	count = players->size;
	Controller *cntrls = calloc(count, sizeof(*cntrls));
	AI_Behaviour_Attributes *ai_ba = calloc(count, sizeof(*ai_ba));
	if (!cntrls || !ai_ba) {
		pthread_exit(NULL);
	}
	for (NodeLL *ptr=players->head; ptr!=NULL; ptr=ptr->next){
		int tmp_id = ((Player *)ptr->data)->id;
		int indx = (tmp_id * -1) - 1;

		ai_ba[indx].mode = AI_STAY_MODE;
		ai_ba[indx].t_row = 2;
		ai_ba[indx].t_col = 54;
		ai_ba[indx].find_path = true;
		ai_ba[indx].state_inertia = DEFAULT_STATE_INERTIA;

		cntrls[indx].left = false;
		cntrls[indx].right = false;
		cntrls[indx].up = false;
		cntrls[indx].down = false;
		cntrls[indx].orientation = false;
		cntrls[indx].id = ((Player *)ptr->data)->id;
		cntrls[indx].orientation = 0;
		cntrls[indx].state = '.';
		cntrls[indx].pathgrid = load_a_map("../assets/map01.txt");
	}

	bool reached;
	int row, col;
	A_Cell *cur_cell = NULL, *target_cell = NULL;
	Player *ptr_data;
	while (true){
		for (NodeLL *ptr=players->head; ptr!=NULL; ptr=ptr->next){
			ptr_data = ptr->data;
			int indx = (ptr_data->id * -1) - 1;
			if (ptr_data->id < 0){
				row = (ptr_data->y / 32);
				col = (ptr_data->x / 32);
				cur_cell = &cntrls[indx].pathgrid->grid[row][col];
				if (ai_ba[indx].find_path){
					cntrls[indx].pathgrid = generate_route(
						cntrls[indx].pathgrid,
						row,
						col,
						ai_ba[indx].t_row,
						ai_ba[indx].t_col
					);
					ai_ba[indx].find_path = false;
					target_cell = cur_cell->previous;
				};
				switch (ai_ba[indx].mode){
					case AI_STAY_MODE:
						ai_ba[indx].state_inertia--;
						if (ai_ba[indx].state_inertia < 0){
							ai_ba[indx].state_inertia = DEFAULT_STATE_INERTIA;
							ai_ba[indx].mode = AI_PATROL_MODE;
							ai_ba[indx].find_path = true;
							printf("switched to Patrol\n");
						}
						break;
					case AI_PATROL_MODE:
						reached = guards_follow_target(&target_cell, cur_cell, ptr_data, &cntrls[indx]);
						if (reached){
							ai_ba[indx].mode = AI_STAY_MODE;
							printf("switched to Stay\n");
							// TODO: find random target cells to patrol to
						}
						break;
				}
				player_update(ptr_data, &cntrls[indx]);
			}
		}
		msleep(1000/60);
	}
	pthread_exit(NULL);
}
