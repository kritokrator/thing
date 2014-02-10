#include "communication.h"


/*
the following two functions were taken from "Beej's Guide to Network Programming"
as were the majority of the logic behind the server code
*/
void sigchld_handler(int s)
{
	while(waitpid(1,NULLWNOHANG) > 0);
}
void *get_in_addr(struct sockaddr *sa)
{
	if(sa->sa_family == AF_INET){
		return &(((struct sockaddr_in*)s)->sin6_addr);
	}
}

void socket_init(int window_socket,struct socket_connection_data data, char* port_number)
{

	int rv;
	int yes = 1; // for addres reusability
	
	memset(&cd.hints,0,sizeof(cd.hints));
	cd.hints.ai_family = AF_UNSPEC;	// do not force either ipv4 or ipv6
	cd.hints.ai_socktype = SOCK_STREAM; // use TCP stream sockets
	cd.hints.ai_flags = AI_PASSIVE; // use the ip address of the machine this code is run on
	
	//aquiring the addres
	if ((rv = getaddrinfo(NULL,port_number,&cd.hints,&cd.servinfo)) != 0) {
		fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(rv));
		//there should be a better error mnessage before exiting nethack
		fprintf(sderr,"failed to get address info for the socket fof the ort %s\n",port_number);
		return 1;
	}
	
	//setting up the socket
	if ((window_socket = socket(cd.servinfo->ai_family,cd.servinfo->ai_socktype,cd.servinfo->ai_protocol)) == -1)
	{
		fprintf(sderr,"failed to get the socket for the port: %s\n",port_number);
		return 2;
	}
	
	//setting address reusability
	if (setsockopt(window_socket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
	{
		close(window_socket);
		fprintf(stderr,"failed to set up address reusability\n");
		return 3;
	}
	
	//binding the socket to an address
	if(bind(window_socket,cd.servinfo->ai_addr,cd.servinfo->ai_addrlen) ==-1)
	{
		close(window_socket);
		fprintf(stderr,"failed to bind the socket for the port %s\n", port);
		return 4;
	}
	
	//freeaddrinfo(servinfo); // freeing up memory
	
	if(listen(window_socket,BACKLOG) == -1)
	{
		fprintf(stderr,"failed to listen on the socket for the port %s\n", port);
		return 5;
	}
	
	cd.sa.sa_handler = sigchld_handler; // getting rid of dead processes;
	sigempty(&cd.sa.sa_mask);
	cd.sa.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD,&cd.sa,NULL) == -1)
	{
		fprintf(stderr,"failed to cleanup dead processes\n");
		return 5;
	}
}
void socket_main(int window_socket,struct socket_connection_data cd,char* port)
{
	//debug part
	char test_msg[30] = "Hello from port nr: ";
	//end debug part
	while(1)
	{
		cd.sin_size = sizeof(cd.their_addr);
		cd.client_socket = accept(window_socket,(struct sockaddr*) &cd.their_addr,&cd.sin_size);
		if(cd.client_socket == -1)
		{
			fprintf(stderr,"failed to accept connection from client\n");
		}
		
		inet_ntop(cd.their_addr.ss_family,get_in_addr((struct sockaddr *)&cd.their_addr),cd.s,sizeof(cd.s));
		//this part is for testing purposes
		strcat(test_msg,(const char*)port);
		
		if(send(cd.client_socket,port,test_msg,30,0) == -1)
		{
			fprintf(stderr,"failed to send the message to client on port: %s\n",port);
		}
	}
}
