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
  int k = 0,n3;
  void * ptr;
  n3 = -1;
  int shmid = shmget(1122,4096,0666);
  ptr = shmat(shmid,NULL,0666);
  int i = atoi(argv[1]);

  while(i!=k){
    n3 +=2;
    sprintf(ptr,"%d ",n3);
    ptr +=strlen(ptr);
    k++;
  }
  ptr +=strlen(ptr);
  shmctl(shmid,IPC_RMID,NULL);
  return 0;

}