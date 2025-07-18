#include<stdio.h>
#include<stdlib.h>

typedef struct{
  int pid, aT, cT, wT, bT, tAT;
}process;


void fcfs(process p[],int n){
  int eT = p[0].aT;
  int tTAT;
  for(int i=0;i<n;i++){
    if(eT < p[i].aT) eT = p[i].aT;
    p[i].wT = eT - p[i].aT;
    eT +=p[i].bT;
    p[i].cT = eT - p[i].aT;
    p[i].tAT = p[i].cT - p[i].aT;
    printf("| (%d) P%d (%d) ", eT - p[i].bT, p[i].pid, eT);
  }
  printf("|\n");
        printf("\nObservation Table:\nPID\tAT\tBT\tCT\tTAT\tWT\n");
        for (int i = 0; i < n; i++)
        {
                process t = p[i];
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", t.pid, t.aT, t.bT, t.cT, t.tAT, t.wT);
                      
        }
}


int main()
{
        int n;
        printf("Enter the number of p: ");
        scanf("%d", &n);
        process *p = (process *)malloc(n * sizeof(process));
        for (int i = 0; i < n; i++)
        {
                printf("\nProcess %d\n", i + 1);
                printf("Enter arrival time: ");
                scanf("%d", &p[i].aT);
                printf("Enter burst time: ");
                scanf("%d", &p[i].bT);
                p[i].pid = i + 1;
                printf("\n");
        }
        for (int i = 0; i < n - 1; i++)
        {
                for (int j = 0; j < n - i - 1; j++)
                {
                        if (p[j].aT > p[j + 1].aT)
                        {
                                process temp = p[j];
                                p[j] = p[j + 1];
                                p[j + 1] = temp;
                        }
                }
        }
        fcfs(p, n);
        free(p);
        return 0;
}