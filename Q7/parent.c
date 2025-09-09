#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<string.h>
#include<fcntl.h>

int main(int argc,char * argv[]){
  // Create/Get shared memory segment with key 1122
  int shmid;
  shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);
  // Attach the shared memory segment
  void *ptr = shmat(shmid, NULL, 0666);

  pid_t pid;
  // Fork a child process
  pid = fork();

  if (pid == 0) {
    // In child process: execute the Fibonacci generator program
    execlp("./fib", "fib", argv[1], NULL);
  } else {
    // In parent process: wait for child to finish
    wait(NULL);
    printf("This is parent printing the fibonacci numbers \n");
    // Print the Fibonacci sequence from shared memory
    printf("%s", (char *)ptr);
    // Detach shared memory
    shmdt(ptr);
  }
  return 0;
}