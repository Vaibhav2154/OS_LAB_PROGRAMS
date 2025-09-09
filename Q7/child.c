#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<string.h>
#include<fcntl.h>

int main(int argc,char *argv[]){
  // Child process to generate Fibonacci sequence and write to shared memory
  int k = 2, n1, n2, n3;
  void *ptr;
  // Get the shared memory segment with key 1122
  int shmid = shmget(1122, 4096, 0666);
  // Attach the shared memory segment
  ptr = shmat(shmid, NULL, 0666);
  // Convert the argument to integer (number of Fibonacci terms)
  int i = atoi(argv[1]);
  n1 = 0;
  n2 = 1;
  // Write the first Fibonacci number to shared memory
  sprintf(ptr, "%d ", n1);
  ptr += strlen(ptr);
  // Write the second Fibonacci number to shared memory
  sprintf(ptr, "%d ", n2);
  ptr += strlen(ptr);
  // Generate and write remaining Fibonacci numbers
  while (i != k) {
    n3 = n1 + n2;
    sprintf(ptr, "%d ", n3);
    ptr += strlen(ptr);
    n1 = n2;
    n2 = n3;
    k++;
  }
  // Move pointer to end (not strictly needed)
  ptr += strlen(ptr);
  // Remove the shared memory segment
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
  }