#include <stdio.h>
int n;
int main () {
    printf("Enter the number of processes:");
    scanf("%d",&n);
    int p[n],at[n],bt[n],ct[n],tat[n],wt[n];
    for(int i=0;i<n;i++) {
        p[i]=i+1;
    	printf("Arrival Time:");
    	scanf("%d",&at[i]);
    	printf("Burst Time:");
    	scanf("%d",&bt[i]);
    	printf("processor %d values has been taken succesfully..... \n",i+1);
      }
    	
    	int time=0;
    	for(int j=0;j<n;j++) {
    	
        if(time < at[j]) {
        time = at[j];
        }
    	
    	ct[j] = time + bt[j];
    	time = ct[j];
    	tat[j] = ct[j] - at[j];
    	wt[j] = tat[j] - bt[j];
      }
      
      printf("Enter the FCFS of the process are....\n");
      printf("\tPID\tAT\tBT\tCT\tTAT\tWT\t\n");
      for(int k=0;k<n;k++) {
         printf("\t%d\t%d\t%d\t%d\t%d\t%d\n",p[k],at[k],bt[k],ct[k],tat[k],wt[k]);
      }
      return 0;
    }
