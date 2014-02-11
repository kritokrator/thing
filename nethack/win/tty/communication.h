#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#define MAP_PORT "3490"
#define MENU_PORT "3491"
#define MESSAGE_PORT "3492"
#define TEXT_PORT "3493"
#define STATUS_PORT "3494"

#define BACKLOG 10
#define NUM_THREADS 5

/*
int map_socket;
int menu_socket;
int message_socket;
int text_socket;
int status_socket;
*/

int sockets[NUM_THREADS];
char ports[] = { "3490","3491", "3492", "3493" ,"3494"};



typedef struct _socket_connection_data
{
	struct addrinfo hints, *servinfo,*p;
	struct sockaddr_storage their_addr; // connector's address info
	socklen_t sin_size;
	struct sigaction sa;
	char s[INET6_ADDRSTRLEN];
	int client_socket;
}socket_connection_data;

typedef struct _thread_data_t
{
	int tid;
	struct socket_connection_data socket_data;
}thread_data_t;


pthread_t thr[NUM_THREADS];
thread_data_t thr_data[NUM_THREADS]

void *socket_init(int window_socket,struct socket_connection_data data, char* port_number);
void threads_init();

#endif
