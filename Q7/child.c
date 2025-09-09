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
  int k = 2, n1,n2,n3;
  void * ptr;
  int shmid = shmget(1122,4096,0666);
  ptr = shmat(shmid,NULL,0666);
  int i = atoi(argv[1]);
  n1 = 0;
  n2 = 1;
  sprintf(ptr,"%d ",n1);
  ptr +=strlen(ptr);
  sprintf(ptr,"%d ",n2);
  ptr +=strlen(ptr);
  while(i!=k){
    n3 = n1+n2;
    sprintf(ptr,"%d ",n3);
    ptr +=strlen(ptr);
    n1 = n2;
    n2 = n3;
    k++;
  }
  ptr +=strlen(ptr);
  shmctl(shmid,IPC_RMID,NULL);
  return 0;
  
}