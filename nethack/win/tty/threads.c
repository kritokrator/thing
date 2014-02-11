#include "communication.h"


int init_threads()
{
	int i,rc;
	
	
	for(i=0;i<NUM_THREADS;i++)
	{
		thr_data[i].tid = i;
		if((rc = pthread_create(&thr[i],NULL,socket_init(sockets[i],thr_data.communication_data,ports[i]),thr_data[i])))
		{
			fprintf(stderr,"threads.c | init_threads | thread creation failed\n");
			return -1;
		}
	}
	return 0;	
}
//this'll be needed later for garbage collecting
void destroy_threads()
{
	int i;
	for(i=0;i<NUM_THREADS;i++)
	{
		pthread_join(thr[i],NULL);
	}
	return 0;
}
