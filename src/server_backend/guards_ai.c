#include "guards_ai.h"

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
	char buffer[1024];
	bool left=false, right=true, up=false, down=false;
	int orientation = 0;
	char state = 'i';
	while (true){
		for (LLNode *ptr=players; ptr!=NULL; ptr=ptr->next){
			if (ptr->data->id < 0){
				snprintf(
					buffer,
					sizeof(buffer),
					"%d:%b:%b:%b:%b:%b:%c",
					ptr->data->id,
					right,
					left,
					up,
					down,
					orientation,
					state
				);
				Controller c;
				parse_response(buffer, &c);
				player_update(ptr->data, &c);
			}
		}
		msleep(1000/30);
	}
	pthread_exit(NULL);
}
