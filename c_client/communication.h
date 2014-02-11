#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthreads.h>

#define MAXDATASIZE 512
#define NUM_THREADS 5

int sockets[NUM_THREADS]
char ports[] = {"3490","3491","3492","3493","3494"};

typedef struct _socket_connection_data
{
	struct addrinfo hints,*servinfo,*p;
	struct sockaddr_storage
	struct buf[MAXDATASIZE];
	char s[INET6_ADDRSTRLEN];
	int numbytes;
}socket_connection_data;

typedef struct _thread_data_t
{
	int tid;
	struct socket_connection_data socket_data;
}thread_data_t;

pthread_t thr[NUM_THREADS];
thread_data_t thr_data[NUM_THREADS];

#endif
