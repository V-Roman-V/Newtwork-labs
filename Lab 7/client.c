#include <string.h>
#include <arpa/inet.h>
#include "client.h"

int main(int argc, char const *argv[])
{
	char *ip = "10.91.53.159";
	int port = 8080; 
	struct sockaddr_in serv_addr;	
	int sock = createClient(&serv_addr, ip, port);
	
	Send(sock, "Hello server!");
	Read(sock, NULL);
	return 0;
}
