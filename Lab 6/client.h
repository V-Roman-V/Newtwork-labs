#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "send_read.h"

#define MAXATT 20

int createClient(struct sockaddr_in *serv_addr, char *ip, int port){
	// server address setting
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(port);
	inet_pton(AF_INET, ip, &serv_addr->sin_addr);

	// Creating socket file descriptor
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	// Trying to connect
	for(int i = 0; i<MAXATT + 1; i++){
		if (i == MAXATT){
			printf("No connection\n");	
			return 0;	
		}

		printf("Trying to connect to %s:%d  %d/%d attemp\n",ip,port,i,MAXATT);
		if (connect(sock, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) >= 0) {
			printf("connection is success\n");
			break;
		}
		
		printf("Connection Failed. Sleep 2 sec.\n\n");
		sleep(2);
	}
	return sock;
}

#endif // CLIENT_H
