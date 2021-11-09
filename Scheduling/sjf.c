#include <stdio.h>
  
int main() 
{
      int limit;
      printf("Enter the Total Number of Processes:");
      scanf("%d", &limit); 
      int arrival_time[limit], burst_time[limit+1], temp[limit];
      int wait_time[limit],turnaround_time[limit];
      int i, smallest, count = 0, time;
      double total_wait_time = 0, total_turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
 
      printf("Enter Details of %d Processes\n", limit);
      for(i = 0; i < limit; i++)
      {     printf(".......prosess %d....... : \n",i);
            printf("Enter Arrival Time:");
            scanf("%d", &arrival_time[i]);
            printf("Enter Burst Time:");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
            
      }
      burst_time[limit] = 9999;  
      for(time = 0; count != limit; time++)
      {
            smallest = limit;
            for(i = 0; i < limit; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time[smallest] = end - arrival_time[smallest] - temp[smallest];
                  turnaround_time[smallest] = end - arrival_time[smallest];
                  total_wait_time += wait_time[smallest];
                  total_turnaround_time += turnaround_time[smallest];
            }
      }
      for (int i = 0; i < limit; ++i)
      {
            printf("Process %d : waiting time=%d , turnaround time=%d\n",
                              i, wait_time[i],turnaround_time[i] );
      }
      average_waiting_time = total_wait_time / limit; 
      average_turnaround_time = total_turnaround_time / limit;
      printf("\nAverage Waiting Time:\t%lf\n", average_waiting_time);
      printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);
      return 0;
}
