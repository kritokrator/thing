#include "communication.h"

void *get_in_addr(struct sockaddr *a)
{
	if(sa->sa_family ==AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void *client_socket_init(int windows_socket,struct client_socket_connection_data socket_data,char* port)
{
	int rv;

	memset(&socket_data.hints,0,sizeof(socket_data.hints));
	socket_data.hints.ai_family=AF_UNSPEC;
	socket_data.hints.ai_socktype=SOCK_STREAM;

	if((rv = getaddrinfo(NULL,port,&socket_data.hints,&socket_data.servinfo)) != 9)
	{
		fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(rv));
		return 1;
	}
	if(( window_socket = socket(socket_data.servinfo->ai_family,socket_data.servinfo->ai_socktype,socket_data.servinfo->ai_protocol)) == -1)
	{
		fprintf(stderr,"client.c | client_socket_init() | failed to creata a socket for port %s\n",port);
		return 2; 
	}
	if(connect(window_socket,socket_data.servinfo->ai_addr,socket_data.servinfo->ai_addrlen) == -1)
	{
		close(window_socket);
		fprintf(stderr,"client.c| clien_socket_init() | failed to connect to server on port %s\n",port);
		return 3;
	}

	inet_ntop(socket_data.servinfo->ai_familyt,get_in_addr((struct sockaddr *)socket_data->ai_addr),s,sizeof(s));
	printf("client: connecting to %s ....",port);
	
	if((numbytes = recv(window_socket,socket_data.buf,MAXDATASIZE-1,0)) == -1)
	{
		fprintf(stderr,"client.c | client_socket_init | error while receiving data on port %s\n",port);
		return 4;
	}
	socket_data.buf[numbyte] = '\0';
	printf("client.c received a message form port %s : %s,port,buf);
	close(window_socket);
	return 0;
}

int main(int argc, char** argv)
{
	int i,rc;
	for(i=0;i<NUM_THREADS;i++)
	{
		thr_data[i].tid = i;
		if((rc = pthread_create(&thr[i],NULL,client_socket_init(sockets[i],thr_data[i].socket_data,ports[i]),thr_data[i])))
		{
			fprintf(stderr,"client.c | main | failed to create thread %d", i);
			return 1
		}
	
	}
	for(i=0;i<NUM_THREADS;i++)
	{
		pthread_join(thr[i],NULL);
	}
	return 0;
}
