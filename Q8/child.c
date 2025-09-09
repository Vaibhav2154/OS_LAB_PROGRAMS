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
  // Child process to generate Fibonacci sequence and write to POSIX shared memory
  int k = 2, n1, n2, n3;
  void *ptr;
  // Create and open a POSIX shared memory object named "Vss"
  int shmfd = shm_open("Vss", O_CREAT | O_RDWR, 0666);
  // Set the size of the shared memory object
  ftruncate(shmfd, 4096);
  // Map the shared memory object into the process's address space
  ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shmfd, 0);
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
  return 0;
}