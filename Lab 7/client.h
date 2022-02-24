#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "send_read.h"


int createClient(struct sockaddr_in *srvaddr, char *ip, int port){
	// server address setting
	memset(srvaddr, 0, sizeof(*srvaddr));
	srvaddr->sin_family = AF_INET;
	srvaddr->sin_port = htons(port);
	inet_pton(AF_INET, ip, &srvaddr->sin_addr);

	// Creating socket file descriptor
	return socket(AF_INET, SOCK_DGRAM, 0);
}

#endif // CLIENT_H
