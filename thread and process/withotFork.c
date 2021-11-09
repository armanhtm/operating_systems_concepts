
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
int main(int argc, char const *argv[])
{
	int hist[25];
	for (int i = 0; i < 25; ++i)
	{
		hist[i]=0;
	}

	int number;
	scanf("%d",&number);
	srand(time(0));
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	for (int i = 0; i<number ; ++i)
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
	int sum=0;
	for (int i = 0; i < 25; ++i)
	{
		sum+=hist[i];
	}
	printf("\n%d\n",sum );
	return 0;
}
