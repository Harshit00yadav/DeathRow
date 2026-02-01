#include "headers/client.h"

int socket_initialization(UDPcon *conn){
	conn->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (conn->sockfd < 0){
		fprintf(stderr, "Socket Creation Failed.\n");
		return EXIT_FAILURE;
	}
	memset(&conn->server_addr, 0, sizeof(conn->server_addr));
	conn->server_addr.sin_family = AF_INET;
	conn->server_addr.sin_port = htons(SERVER_PORT);
	conn->server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	conn->addr_len = sizeof(conn->server_addr);
	return EXIT_SUCCESS;
}

void destroy_socket(UDPcon *conn){
	close(conn->sockfd);
}

void send_data(UDPcon *conn, const char *msg){
	sendto(conn->sockfd, msg, strlen(msg), 0, (struct sockaddr *)&conn->server_addr, conn->addr_len);
}

void recv_data(UDPcon *conn, char *buffer){
	int n = recvfrom(
		conn->sockfd,
		buffer,
		BUFFER_SIZE,
		0,
		(struct sockaddr *)&conn->server_addr,
		&conn->addr_len
	);
	if (n < 0){
		fprintf(stderr, "recvfrom failed.\n");
		return;
	}
	buffer[n] = '\0';
}
