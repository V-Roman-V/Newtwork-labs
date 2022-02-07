#ifndef SEND_READ_H
#define SEND_READ_H

#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

void Send(int sock, char *str) {
	send(sock , str , strlen(str) , 0 );
	printf("send msg: \"%s\"\n", str);
}

void Read(int sock, char* str) {
	if (str == NULL){
		char buffer[1024] = {0};
		read( sock , buffer, 1024);
		printf("read msg: \"%s\"\n",buffer );
	} else {
		read( sock , str, 1024);
		printf("read msg: \"%s\"\n",str );
	}
}

#endif // SEND_READ_H
