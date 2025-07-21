#include "tcp_server.h"

int main(){
	int sockfd;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		perror("[ ERROR ] Socket Creation Failed.");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr, 0, sizeof(server_addr));
	memset(&client_addr, 0, sizeof(client_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("[ ERROR ] Bind Failed.");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	printf("UDP server listening on port: %d \n", PORT);
	while (true){
		int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
		if (n < 0){
			perror("[ ERROR ] recvfrom error.");
			continue;
		}
		buffer[n] = '\0';
		printf("Client: %s\n", buffer);

		const char *reply = "Message recieved!";
		sendto(sockfd, reply, strlen(reply), 0, (const struct sockaddr *)&client_addr, addr_len);
	}
	close(sockfd);
	return 0;
}
