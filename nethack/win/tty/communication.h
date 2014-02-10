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

#define MAP_PORT "3490"
#define MENU_PORT "3491"
#define MESSAGE_PORT "3492"
#define TEXT_PORT "3493"
#define STATUS_PORT "3494"

#define BACKLOG 10

int map_socket;
int menu_socket;
int message_socket;
int text_socket;
int status_socket;


struct socket_connection_data
{
	struct addrinfo hints, *servinfo,*p;
	struct sockaddr_storage their_addr; // connector's address info
	socklen_t sin_size;
	struct sigaction sa;
	char s[INET6_ADDRSTRLEN];
	int client_socket;
};
void socket_init();
void threads_init();

#endif
