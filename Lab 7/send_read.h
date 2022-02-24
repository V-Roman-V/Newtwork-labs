#ifndef SEND_READ_H
#define SEND_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


void Send(int sock, struct sockaddr_in *srvaddr, const char *str){
	sendto(sock, str, strlen(str), MSG_CONFIRM, ( struct sockaddr *)srvaddr,sizeof(*srvaddr));
	printf("send msg: \"%s\"\n", str);
}

void Read(int sock, struct sockaddr_in *srvaddr, char* str) {
  static unsigned int len;
	if (str == NULL){
		char buffer[1024] = {0};
		int n = recvfrom(sock, buffer, 1024, MSG_WAITALL, (struct sockaddr *) srvaddr,	&len);
		buffer[n] = '\0';
		printf("read msg: \"%s\"\n",buffer);
	} else {
		int n = recvfrom(sock, str, 1024, MSG_WAITALL, (struct sockaddr *) srvaddr,	NULL);
		str[n] = '\0';
		printf("read msg: \"%s\"\n",str );
	}
}

#endif // SEND_READ_H
