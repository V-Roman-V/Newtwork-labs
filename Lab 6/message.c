#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "server.h"
#include "client.h"

#define IP "192.168.166.254"
#define PORT 8080

void my_itoa(int num, char *str)
{
}

sem_t mutex;
char msg[1024];

void *server_thread(){
	//create server
	struct sockaddr_in srv_addr;
	socklen_t srv_addrlen = sizeof(srv_addr);
  int srv_sock = createServer(&srv_addr, PORT);

	int client = waitClient(srv_sock, &srv_addr, &srv_addrlen);

	while(1){
		Read(client, msg);
    sem_post(&mutex);
	}
  return 0;
}

void *client_thread(){
	// create client
	struct sockaddr_in cl_addr;	
	int cl_sock = createClient(&cl_addr, IP, PORT);
	

  while(1){
		sem_wait(&mutex);

		int number = atoi(msg)-1;
		char newMsg[1024];
    sprintf(newMsg, "%d", number);

		if (number<0) break;
		Send(cl_sock, newMsg);
		//sleep(1);
	}
  return 0;
}

int main(int argc, char const *argv[]) {
	sem_init(&mutex, 0, 0);
  pthread_t thread_server;
  pthread_t thread_client;
  pthread_create(&thread_server, NULL, server_thread, NULL);
  pthread_create(&thread_client, NULL, client_thread, NULL);
	pthread_join(thread_server, NULL);
	pthread_join(thread_client, NULL);
	return 0;
}

