#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], priority[n];
    int ct[n], tat[n], wt[n];
    int completed[n];

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess P%d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &priority[i]);
    }

    //FCFS
    int time = 0;
    float total_wt = 0;

    printf("\n\n\t FCFS \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        if(time < at[i])
            time = at[i];

        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        time = ct[i];
        total_wt += wt[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Average Waiting Time (FCFS): %.2f\n", total_wt/n);


    // SJF
    time = 0;
    int done = 0;
    float sjf_total = 0;

    for(int i=0;i<n;i++)
        completed[i] = 0;

    while(done < n) {

        int shortest = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(shortest == -1 || bt[i] < bt[shortest])
                    shortest = i;
            }
        }

        if(shortest == -1)
            time++;
        else {
            ct[shortest] = time + bt[shortest];
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            time = ct[shortest];
            completed[shortest] = 1;
            done++;
        }
    }

    printf("\n\tSJF \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++) {
        sjf_total += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Average Waiting Time (SJF): %.2f\n", sjf_total/n);


    // Priority
    time = 0;
    done = 0;
    float pr_total = 0;

    for(int i=0;i<n;i++)
        completed[i] = 0;

    while(done < n) {

        int highest = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(highest == -1 || priority[i] < priority[highest])
                    highest = i;
            }
        }

        if(highest == -1)
            time++;
        else {
            ct[highest] = time + bt[highest];
            tat[highest] = ct[highest] - at[highest];
            wt[highest] = tat[highest] - bt[highest];

            time = ct[highest];
            completed[highest] = 1;
            done++;
        }
    }

    printf("\n\tPriority \n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++) {
        pr_total += wt[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }

    printf("Average Waiting Time (Priority): %.2f\n", pr_total/n);


// Round Robin
    int quantum;
    printf("\nEnter Time Quantum for Round Robin: ");
    scanf("%d", &quantum);

    int rt[n];
    for(int i=0;i<n;i++) {
        rt[i] = bt[i];
        completed[i] = 0;
    }

    time = 0;
    done = 0;
    float rr_total = 0;

    while(done < n) {
        int executed = 0;

        for(int i=0;i<n;i++) {

            if(at[i] <= time && rt[i] > 0) {

                executed = 1;

                if(rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    time += rt[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    rr_total += wt[i];
                    rt[i] = 0;
                    done++;
                }
            }
        }

        if(!executed)
            time++;
    }

    printf("\n\tRound Robin \n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Average Waiting Time (Round Robin): %.2f\n", rr_total/n);

    return 0;
}
