#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void main() {

    pid_t pid;

    pid = fork();

    if (pid == -1) {
        printf("Fork Failed\n"); 
        exit(1);
    }
    if (pid == 0) {
        printf("[CHILD]    pid: %d    parent_pid: %d\n", getpid(), getppid());
        printf("Child exiting...\n");
        exit(0);
    } else {
        printf("[PARENT]    pid: %d    parent_pid: %d    child_pid: %d\n", getpid(), getppid(), pid);
        printf("[PARENT]    run ```ps aux | grep Z``` or ```ps -l | grep <child_pid>``` in another terminal\n");
        sleep(20);
        printf("[PARENT]    Terminating zombie process\n");
        wait(NULL);
        printf("Parent exiting...");
    }
}