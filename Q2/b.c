#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
        int pid;
        int arrivalTime;
        int burstTime;
        int priority;
        int startTime;
        int finishTime;
        int waitTime;
        int TATime;
        int remainingTime;
        int completed;
} Process;

void calculate_time(Process *processes, int n)
{
        int currTime = 0, completed_processes = 0, prev = -1;
        printf("\nGantt Chart:\n");

        while (completed_processes < n)
        {
                int hpi = -1, hp = INT_MIN; // highest priority index and highest priority

                for (int i = 0; i < n; i++)
                {
                        if (processes[i].arrivalTime <= currTime && !processes[i].completed)
                        {
                                if (processes[i].priority > hp)
                                {
                                        hp = processes[i].priority;
                                        hpi = i;
                                }
                                else if (processes[i].priority == hp)
                                {
                                        if (processes[i].arrivalTime < processes[hpi].arrivalTime)
                                        {
                                                hpi = i;
                                        }
                                }
                        }
                }

                if (hpi == -1)
                        currTime++;
                else
                {
                        if (prev != hpi)
                        {
                                processes[hpi].startTime = (processes[hpi].startTime == -1) ? currTime : processes[hpi].startTime;
                                prev = hpi;
                        }
                        processes[hpi].remainingTime--;
                        currTime++;
                        if (processes[hpi].remainingTime == 0)
                        {
                                processes[hpi].finishTime = currTime;
                                processes[hpi].waitTime = processes[hpi].finishTime - processes[hpi].burstTime - processes[hpi].arrivalTime;
                                processes[hpi].TATime = processes[hpi].finishTime - processes[hpi].arrivalTime;
                                processes[hpi].completed = 1;
                                completed_processes++;
                        }
                        printf("| (%d) P%d (%d) ", currTime - 1, processes[hpi].pid, currTime);
                }
        }
        printf("|\n");
}

void printInfo(Process *processes, int n)
{
        float avgWT = 0;
        float avgTAT = 0;
        int totWT = 0;
        int totTAT = 0;
        printf("\n\nObservation Table:\nPID\tAT\tBT\tPriority\tST\tFT\tWT\tTAT\n");
        for (int i = 0; i < n; i++)
        {
                printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority, processes[i].startTime, processes[i].finishTime, processes[i].waitTime, processes[i].TATime);
                totTAT += processes[i].TATime;
                totWT += processes[i].waitTime;
        }
        avgTAT = (float)totTAT / n;
        avgWT = (float)totWT / n;
        printf("\nAverage Waiting Time: %.2f\n", avgWT);
        printf("\nAverage Turn Around Time: %.2f\n", avgTAT);
}

void main()
{
        int n;
        printf("Enter no. of processes:");
        scanf("%d", &n);
        Process *processes = (Process *)malloc(n * sizeof(Process));
        for (int i = 0; i < n; i++)
        {
                printf("Enter arrival time, burst time and priority for process %d : ", i + 1);
                processes[i].pid = i + 1;
                processes[i].completed = 0;
                processes[i].startTime = -1;
                scanf("%d%d%d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
                processes[i].remainingTime = processes[i].burstTime;
        }
        printf("\nNote: Higher priority number means higher priority\n");
        calculate_time(processes, n);
        printInfo(processes, n);
        free(processes);
}