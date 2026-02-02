#include "udp_server.h"
#include "datastructures.h"
#include <pthread.h>
#include <time.h>
#include <errno.h>

void guards_init(size_t n, LinkedList *players);
void *guards_thread_function(void *args);
int msleep(long msec);
