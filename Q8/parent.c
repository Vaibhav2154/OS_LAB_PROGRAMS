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
  // Parent process to read Fibonacci sequence from POSIX shared memory
  int shmfd;

  pid_t pid;
  // Fork a child process
  pid = fork();

  if (pid == 0) {
    // In child process: execute the Fibonacci generator program
    execlp("./fib", "fib", argv[1], NULL);
  } else {
    // In parent process: wait for child to finish
    wait(NULL);
    // Open the shared memory object for reading
    shmfd = shm_open("Vss", O_RDONLY, 0666);
    // Map the shared memory object into the process's address space
    void *ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shmfd, 0);
    printf("This is parent printing the fibonacci numbers \n");
    // Print the Fibonacci sequence from shared memory
    printf("%s", (char *)ptr);
    printf("\n");
    // Remove the shared memory object
    shm_unlink("Vss");
  }
  return 0;
}