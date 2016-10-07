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
	short_sleep_interval.tv_nsec = 3000000;   //3 msec 
	sleep_interval.tv_sec = 0;
	sleep_interval.tv_nsec = 25000000;	// 25 mSec
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
    time_t current_time;
	time(&current_time);
	char output_file_name[64];
	sprintf(output_file_name, "rzhdv_data/rzhdv_ecg_%ld.txt", current_time);
                                                                                                          
	char in_data[128];                                                                                    	
	in_data[1] = 's';
	in_data[2] = 0;
	int doJob = 1;                                                                                        	
	int counter = 0;                                                                                      	
	output_file = fopen(output_file_name, "a");                                                            	
	while(doJob)                                                                                          	
	{                                                                                                     	
		                                                                                                  	
		if(scanf("%s\r\n", in_data) > 0)
		{
			// send data via udp socket ***************************************************                   	
		    sendto(sock, (char *)in_data, strlen(in_data), 0, (struct sockaddr *)&addr, sizeof(addr));
		    fprintf(output_file, "%s\r\n", &(in_data[1]));
		    if(counter%250 == 0)
		    {
		    	fclose(output_file);                                                                          	
				nanosleep(&short_sleep_interval, NULL);
		    	output_file = fopen(output_file_name, "a");                                                        	
		    }
                                                                                                              
			counter++;                                                                                        
		}
		else
			nanosleep(&short_sleep_interval, NULL);
                                                                                                          
	}// end while (main loop)                                                                             	
                                                                                                          
	return 0;                                                                                             

}// end main

//***************************************************
//***************************************************
//***************************************************
//***************************************************
//***************************************************

