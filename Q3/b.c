
#include<stdio.h>   // Standard I/O functions
#include<stdlib.h>  // For malloc


// Structure to represent a process
typedef struct process {
    int Id;     // Process ID
    int AT;     // Arrival Time
    int BT;     // Burst Time (remaining)
    int CT;     // Completion Time
    int TAT;    // Turnaround Time
    int WT;     // Waiting Time
    int flag;   // Flag to indicate if process is added to queue
} pro;

pro p[15]; // Array to store processes


// Swap two process structures
void swap(pro *a, pro *b) {
    pro temp = *a;
    *a = *b;
    *b = temp;
    return; 
}


// Sort processes by Arrival Time using Bubble Sort
void sort(int n) {
    for(int i = 0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].AT > p[j+1].AT) {
                swap(&p[j], &p[j+1]);
            }
        }
    }
}


void main() {
    int n;                  // Number of processes
    int tempBT[15];         // Store original burst times
    int total_WT=0;         // Total waiting time
    int total_TAT=0;        // Total turnaround time
    int quantum;            // Time quantum for RR
    float avg_WT=0, avg_TAT=0; // Average waiting and turnaround times

    // Input number of processes
    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    // Input arrival and burst times
    printf("\nEnter the arrival time and burst time of the process:\n");
    printf("AT BT\n");
    for(int i=0; i<n; i++) {
        p[i].Id = (i+1); // Assign process ID
        scanf("%d%d", &p[i].AT, &p[i].BT);
        tempBT[i] = p[i].BT; // Store original burst time
        p[i].flag = 0;       // Mark as not added to queue
    } 

    // Input time quantum
    printf("\nEnter the time quantum:\n");
    scanf("%d", &quantum);

    // Sort processes by arrival time
    sort(n);

    // Initialize queue for RR scheduling
    int completed = 0;           // Number of completed processes
    int curIndex;                // Current process index
    int curTime = p[0].AT;       // Current time (starts at first arrival)
    int *waitQueue;              // Queue to hold process indices
    int front = 0, rear = 0;     // Queue pointers
    waitQueue = (int *)malloc(n*sizeof(int)); // Allocate queue
    waitQueue[rear] = 0;         // Add first process to queue
    p[0].flag = 1;               // Mark first process as added

    // Main RR scheduling loop
    while (completed != n) {
        // If queue is empty, find next process arrival and show idle time
        if (front > rear) {
            int nextArrival = -1;
            // Find next process that has not arrived yet
            for (int i = 0; i < n; i++) {
                if (p[i].flag == 0 && p[i].BT > 0) {
                    if (nextArrival == -1 || p[i].AT < p[nextArrival].AT) {
                        nextArrival = i;
                    }
                }
            }
            // If found, advance time and show idle
            if (nextArrival != -1 && p[nextArrival].AT > curTime) {
                printf("| Idle(%d) %d", p[nextArrival].AT - curTime, p[nextArrival].AT);
                curTime = p[nextArrival].AT;
                rear = (rear+1) % n;
                waitQueue[rear] = nextArrival;
                p[nextArrival].flag = 1;
            }
        }
        // If still no process to run, continue
        if (front > rear) continue; // No process to run

        // Get next process from queue
        curIndex = waitQueue[front];
        front = (front+1) % n;

        // Execute process for time quantum or remaining burst time
        if(p[curIndex].BT > quantum) {
            p[curIndex].BT -= quantum;      // Reduce burst time
            curTime += quantum;             // Advance time
            printf("| P%d(%d) %d", p[curIndex].Id, quantum, curTime); // Print execution
        } else {
            curTime += p[curIndex].BT;      // Advance time by remaining burst
            printf("| P%d(%d) %d", p[curIndex].Id, p[curIndex].BT, curTime); // Print execution
            p[curIndex].BT = 0;             // Mark process as finished
            p[curIndex].CT = curTime;       // Set completion time
            p[curIndex].TAT = p[curIndex].CT - p[curIndex].AT; // Calculate TAT
            total_TAT += p[curIndex].TAT;   // Add to total TAT
            p[curIndex].WT = p[curIndex].TAT - tempBT[p[curIndex].Id-1]; // Calculate WT
            total_WT += p[curIndex].WT;     // Add to total WT
        }

        // Add newly arrived processes to queue
        for(int i=0; i<n && p[i].AT <= curTime; i++) {
            if(i == curIndex || p[i].flag == 1 || p[i].BT == 0) 
                continue; // Skip if already in queue or finished
            rear = (rear+1) % n;
            p[i].flag = 1;           // Mark as added
            waitQueue[rear] = i;     // Add to queue
        }

        // If current process not finished, re-add to queue
        if(p[curIndex].BT > 0) {
            rear = (rear+1)%n;
            waitQueue[rear] = curIndex;
        } else {
            completed++; // Mark as completed
        }
    }

    // Calculate averages
    avg_TAT = (float)total_TAT/n;
    avg_WT = (float)total_WT/n;

    // Print process table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].AT, tempBT[i], p[i].CT, p[i].TAT, p[i].WT);
    }

    // Print averages
    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);
}



/*
Sample Input/Output:

gcc rr.c
./a.out
Enter the number of processes:
5

Enter the arrival time and burst time of the process:
AT BT
0 5
1 3
2 1
3 2
4 3

Enter the time quantum:
2
| P1(2) 2| P2(2) 4| P3(1) 5| P1(2) 7| P4(2) 9| P5(2) 11| P2(1) 12| P1(1) 13| P5(1) 14
PID	AT	BT	CT	TAT	WT
1	0	5	13	13	8
2	1	3	12	11	8
3	2	1	5	3	2
4	3	2	9	6	4
5	4	3	14	10	7

Average TAT = 8.60
Average WT = 5.80
*/
