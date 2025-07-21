#include "base.h"

#ifdef _WIN32
#include <winsock2.h>

#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#endif

#ifndef CLIENTHEADER_H
#define CLIENTHEADER_H
typedef struct UDPcon {
	int sockfd;
	struct sockaddr_in server_addr;
	socklen_t addr_len;
} UDPcon;

typedef struct recv_args{
	UDPcon *conn;
	char *buffer;
} recv_args;

#endif

#define SERVER_PORT 8008
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"

int socket_initialization(UDPcon *conn);
void send_data(UDPcon *conn, const char *msg);
void recv_data(UDPcon *conn, char *buffer);
void destroy_socket(UDPcon *conn);
