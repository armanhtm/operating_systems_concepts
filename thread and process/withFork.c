#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <wait.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{	int pId;
	int segment_id;
	int segment_id_variable;
    int* shared_memory;
    int* shared_memory_variable;
    int shared_segment_size = 25*sizeof(int);
    int shared_segment_size_variabble=sizeof(int);
    key_t key = ftok("shmfile",65);
    key_t keyVariable = ftok("shVariabble",65);
    segment_id = shmget(key, shared_segment_size,0666|IPC_CREAT);
    segment_id_variable = 
    	shmget(keyVariable, shared_segment_size_variabble,0666|IPC_CREAT);

	int* hist = (int*)shmat(segment_id,NULL,0);
	int*  variable = (int*)shmat(segment_id_variable,NULL,0);
	*variable =0;
	srand(time(0));

	for (int i = 0; i < 25; ++i)
	{
		hist[i]=0;
	}

	int number;
	scanf("%d",&number);

	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	
	//printf("%d\n",*variable );
	for (int j = 0; j < 100; ++j)
	{
		pId = fork();
		if(pId==0){

			for (int i = 0; i<number/100 ; ++i)
			{
				int counter=12;
				for (int i = 0; i < 12; ++i)
				{
					int random = rand()%100;

					if(random>=49)
						counter+=1;
					else
						counter-=1;
				}
			
		
				hist[counter] +=1;
		 	
			}
			//printf("%s\n","here" );
			exit(0);
		}
		if(pId<0)
			{printf("%s\n", "error"); j--;}
	}
	int status=0;
	pid_t wpid;
	while((wpid=wait(&status))>0);
	//printf("%d\n", *variable);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	printf("it took %lu milli seconds\n",((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000) / 1000);
	for (int i = 0; i < 25; ++i)
	{
		printf("%d : %d --> ",i-12,hist[i] );
		for (int j = 0; j < hist[i]/(number/100); ++j)
		{
			printf("%s","*" );
		}
		printf("%s\n","" );
	}

	
	
	return 0;
}
