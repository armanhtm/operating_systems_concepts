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


typedef int Semaphore;

void down(Semaphore* s);
void up(Semaphore* s);
void writer(Semaphore* s1,Semaphore* s2);
void reader(Semaphore* s1,Semaphore* s2,Semaphore* s3,Semaphore* s4);

int pid;
int number;
int main(){
//printf("1");
    printf("enter counter limit:" );
    scanf("%d",&number);
    int reader_number;
    printf("enter reader number:");
    scanf("%d",&reader_number);
    int writer_number;
    printf("enter writer number:");
    scanf("%d",&writer_number);
    int segment_id;
    int* shared_memory;
    int shared_segment_size = 4*sizeof(int);
    key_t key = ftok("shmfile",65);
    segment_id = shmget(key, shared_segment_size,0666|IPC_CREAT);
    int* hist = (int*)shmat(segment_id,NULL,0);

    //mutex = hist[0]
    //db = hist[1]
     //rc = hist [2]
    //counter = hist[3]
    for (int i = 0; i < 4; ++i)
    {
        if(i < 2)
            hist[i] = 1;
        else
            hist[i] = 0;
        }


        // pid = fork();
        // if(pid==0){
        //     pid = fork();
        //     if(pid<0)
        //         printf("error\n");
        //     if(pid==0){
        //         reader(&hist[1],&hist[3],&hist[0],&hist[2]);
        //         exit(0);
        //     }
        //     if(pid>0){
        //         writer(&hist[1],&hist[3]);
        //         exit(0);
        //     }
        // }
        // reader(&hist[1],&hist[3],&hist[0],&hist[2]);
        //writer(&hist[1],&hist[3]);






        for (int i = 0; i < reader_number; ++i)
        {
            pid = fork();
            if(pid == 0){
                reader(&hist[1],&hist[3],&hist[0],&hist[2]);
                //writer(&hist[1],&hist[3]);
                exit(0);
            }
            if(pid<0)
                printf("error\n");
            
                
            
        }
        for (int i = 0; i < writer_number; ++i)
        {
            pid = fork();
            if(pid==0){
                writer(&hist[1],&hist[3]);
                exit(0);        
            }    
        }
        
        //printf("%s\n","amir" );
        // for (int i = 0; i < writer_number; ++i)
        // {
        //     pid = fork();
        //     if(pid==0){
        //         writer(&hist[1],&hist[3]);
        //         exit(0);
        //     }
        //     if(pid<0)
        //         printf("error\n");
        // }
        
//        while()
        while(hist[3]<number);


        // pid = fork();
        // printf("%d\n",hist[3] );
        // if(pid == 0){
        //         printf("amirishrer\n");

        //         writer(&hist[1],&hist[3]);
            
        //         exit(0);
        // }
        // if(pid<0)
        //     printf("%s\n","error" );
        // if(pid>0){
        //     pid = fork();
        //     if(pid==0){
        //         reader(&hist[1],&hist[3],&hist[0],&hist[2]);
        //         exit(0);}
        //     if(pid>0)
        //         reader(&hist[1],&hist[3],&hist[0],&hist[2]);
        // }


        

        //reader(&hist[1],&hist[3],&hist[0],&hist[2]);
        //printf("%d",hist[3]);
        }
void down(Semaphore* s){
//printf("%d\n",*s);
    //printf("down\n");
    while(*s <= 0);
//printf("6\n");
    *s = *s - 1;
//printf("7\n");
}
void up(Semaphore* s){
    *s = *s + 1;
}
void writer(Semaphore* db,Semaphore* counter)
{
    pid_t pid_new;
    pid_new = getpid();
    while (*counter<number) {
    //printf("1:");
        
    //printf("%d\n",*s2 );
        //printf("db:%d\n",*db );
        down(db);
    //printf("2\n");
        *counter = *counter + 1;
         printf("pid :%d and ",pid_new);
        printf("counter: %d\n",*counter);
    //printf("3\n");
        up(db);
        sleep(1);
       
        
    //printf("4:");
    //printf("%d\n",*s2 );
    }
}
void reader(Semaphore* db,Semaphore* counter,Semaphore* mutex,Semaphore* rc)
{//printf("kjkjkljklj\n");
//printf("s2:%d\n",*counter );
    pid_t pid_new;
    pid_new = getpid();
    while (*counter<number) {
        //printf("s2:%d\n",*counter );
        //printf("1********");
        down(mutex);
        *rc = *rc + 1;
        if (*rc == 1)
            down(db);
        up(mutex);
        int temp = *counter;
        printf("process number : %d ,value of counter : %d\n",pid_new,temp);
        down(mutex);
        *rc = *rc - 1;
        if (*rc == 0)
            up(db);
        up(mutex);
        sleep(1);
        
    }
}