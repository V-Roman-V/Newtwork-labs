#include <stdio.h>
#include <arpa/inet.h>
#include "server.h"

int main(int argc, char const *argv[]) {
	int port = 8080;
	
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
  
  int sock = createServer(&address, port);

	while(1){
		int cl_sock = waitClient(sock, &address, &addrlen);
		
		Read(cl_sock,NULL);
		Send(cl_sock,"Hello client!");
		
		//close(cl_sock);
		//printf("communication completed\n\n");
	}
	return 0;
}

