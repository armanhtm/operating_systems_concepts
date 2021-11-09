#include <stdio.h>
// Function to find the waiting time for all processes
int waitingtime(int proc[], int n,
int burst_time[], int wait_time[]) {
   // waiting time for first process is 0
   wait_time[0] = 0;
   int i;
   // calculating waiting time
   for (i = 1; i < n ; i++ )
   wait_time[i] = burst_time[i-1] + wait_time[i-1] ;
   return 0;
}
// Function to calculate turn around time
int turnaroundtime( int proc[], int n,
int burst_time[], int wait_time[], int tat[]) {
   // calculating turnaround time by adding
   // burst_time[i] + wait_time[i]
   int i;
   for ( i = 0; i < n ; i++)
   tat[i] = burst_time[i] + wait_time[i];
   return 0;
}
//Function to calculate average time
int avgtime( int proc[], int n, int burst_time[]) {
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   int i;
   //Function to find waiting time of all processes
   waitingtime(proc, n, burst_time, wait_time);
   //Function to find turn around time for all processes
   turnaroundtime(proc, n, burst_time, wait_time, tat);
   //Display processes along with all details
   printf("Processes  Burst   Waiting Turn around \n");
   // Calculate total waiting time and total turn
   // around time
   for ( i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      printf(" %d\t  %d\t\t %d \t%d\n", i+1, burst_time[i], wait_time[i], tat[i]);
   }
   printf("Average waiting time = %f\n", (float)total_wt / (float)n);
   printf("Average turn around time = %f\n", (float)total_tat / (float)n);
   return 0;
}
// main function
int main() {
   //process id's
   int pros_number;
   printf("please enter number of processes: ");
   scanf("%d",&pros_number);
   int proc[pros_number];
   for (int i = 0; i < pros_number; ++i)
   {
      proc[i] = i+1;
   }
   int n = sizeof proc / sizeof proc[0];
   //Burst time of all processes
   int burst_time[pros_number];
   for (int i = 0; i < pros_number; ++i)
   {  
      int burst;
      printf("please enter burst time of process%d: ",i+1 );
      scanf("%d",&burst);
      burst_time[i] = burst;
   }
   avgtime(proc, n, burst_time);
   return 0;
}
