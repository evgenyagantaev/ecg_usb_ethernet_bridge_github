#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <string.h>

int udp_send_thread_parameter = 0;

void pause(void)
{
	int i;
	int x, y = 5;
	for(i=0; i<100; i++)
		x = y;
}

void one_usec_delay(void)
{
	volatile int i = 0;
	for(i=0; i<33; i++)
	{
		i++;
		i--;
	}
}



// end functions ********************************************************


//*****************************
//*****************************
//*****************************
//*****************************
//*****************************

int main(int argc, char *argv)
{


	struct timespec sleep_interval, long_sleep_interval, short_sleep_interval;


	short_sleep_interval.tv_sec = 0;
	short_sleep_interval.tv_nsec = 500000;   // 
	sleep_interval.tv_sec = 0;
	sleep_interval.tv_nsec = 24000000;	// 25 mSec
	long_sleep_interval.tv_sec = 0;
	long_sleep_interval.tv_nsec = 100000000;	// 100 mSec


	pthread_t udpSendThread;
	int threadId;


// local variables
//****************************
	int i, j, k, l;


// end of local variables block
//************************************

		
	// start a thread which will send sensors data via udp through specifyed interval                     	
	//pthread_create(&udpSendThread, NULL, udp_send_thread, (void *)(&udp_send_thread_parameter));        	
                                                                                                          
	int sock;
	struct sockaddr_in addr;

	i = 1;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		printf("\r\nsocket failure ******************\r\n");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(51112);
	addr.sin_addr.s_addr = inet_addr("192.168.1.1");
                                                                                                          
	FILE *output_file;                                                                                    	
                                                                                                          
                                                                                                          
	char in_data[128];                                                                                    	
	int doJob = 1;                                                                                        	
	int counter = 0;                                                                                      	
	while(doJob)                                                                                          	
	{                                                                                                     	
		                                                                                                  	
		//output_file = fopen("trash.txt", "a");                                                            	
		scanf("%s\r\n", in_data);                                                                         	
		// send data via udp socket ***************************************************
		sendto(sock, (char *)in_data, strlen(in_data), 0, (struct sockaddr *)&addr, sizeof(addr));
		//fprintf(output_file, "%s\r\n", in_data);
		//fclose(output_file);                                                                              	
                                                                                                          
		counter++;                                                                                        	
		//sleep(2);                                                                                       	
                                                                                                          
	}// end while (main loop)                                                                             	
                                                                                                          
	return 0;                                                                                             

}// end main

//***************************************************
//***************************************************
//***************************************************
//***************************************************
//***************************************************

