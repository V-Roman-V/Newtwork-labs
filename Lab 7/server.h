#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "send_read.h"

void getIP( char *str){
	FILE *fpipe = popen("hostname -I | cut -d' ' -f1", "r");
	fgets(str, 128, fpipe);
	str[strlen(str)-1]=0; // delete enter
  pclose(fpipe);
}

int createServer(struct sockaddr_in *servaddr, struct sockaddr_in *cliaddr, int port){
	// getting own ip in local network
	char ip[128];
	getIP(ip); 

	// Filling server information
	memset(servaddr, 0, sizeof(*servaddr));
	memset(cliaddr, 0, sizeof(*cliaddr));
	servaddr->sin_family = AF_INET;
	servaddr->sin_addr.s_addr = INADDR_ANY;
	servaddr->sin_port = htons(port);
	
	// Creating socket file descriptor
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	// Bind the socket with the server address
	bind(sock, (const struct sockaddr *)servaddr,sizeof(*servaddr));

	printf("server is waiting clients on ");
	printf("ip: %s:%d\n", ip,(int)ntohs(servaddr->sin_port));

	return sock;
}

int waitClient(int sock, struct sockaddr_in *address, socklen_t *addrlen){
	struct sockaddr_in client_addr;
	socklen_t client_addrlen = sizeof(client_addr);

	listen(sock, 3);

	int cl_sock = accept(sock, (struct sockaddr *)address, addrlen);
	getsockname(cl_sock, (struct sockaddr*)&client_addr, &client_addrlen);

	printf("client %s is connected\n", inet_ntoa(client_addr.sin_addr));
	return cl_sock;
}

#endif // SERVER_H
