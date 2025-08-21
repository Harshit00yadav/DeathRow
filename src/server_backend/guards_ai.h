#include "udp_server.h"
#include "datastructures.h"
#include <pthread.h>
#include <time.h>
#include <errno.h>    

LLNode *guards_init(size_t n, LLNode *players);
void *guards_thread_function(void *args);
int msleep(long msec);
