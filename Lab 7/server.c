#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "server.h"

#define PORT	 8080
int main() {
	struct sockaddr_in servaddr, cliaddr;
	
	int sock = createServer(&servaddr, &cliaddr, PORT);
	
  Read(sock, &cliaddr, NULL);
  Send(sock, &cliaddr, "Hello client");
  
	return 0;
}

