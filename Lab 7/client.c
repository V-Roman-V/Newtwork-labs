#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "client.h"

#define ip "192.168.166.254"
#define PORT 8080

struct sockaddr_in srvaddr;
int sock;

void * read_thread(){
	char str[1024] = {0};
	while(1){
		fgets(str, 1024, stdin);
		str[strlen(str)-1]=0;
	  Send(sock, &srvaddr, str);
	}
	return 0;
}

void * send_thread(){
	while(1){
  	Read(sock, &srvaddr, NULL);
  }
	return 0;
}


int main() {
 	sock = createClient(&srvaddr, ip, PORT);
  pthread_t thread_read;
  pthread_t thread_send;
  pthread_create(&thread_read, NULL, read_thread, NULL);
  pthread_create(&thread_send, NULL, send_thread, NULL);
  pthread_join(thread_read, NULL);
  pthread_join(thread_send, NULL);
}

