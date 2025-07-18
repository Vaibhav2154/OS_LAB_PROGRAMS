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

int isPrime(int n){
  for(int i=2;i<=(n/2);i++){
    if(n%i==0) return 1;
  }
  return 0;
}

int main(int argc,char *argv[]){
  int n1,n2;
  void * ptr;
  int shmfd = shm_open("Vss",O_CREAT | O_RDWR,0666);
  ftruncate(shmfd,4096);
  ptr = mmap(0,4096,PROT_WRITE,MAP_SHARED,shmfd,0);
  n1 = atoi(argv[1]);
  n2 = atoi(argv[2]);
  printf("%d",n1);
  for(int i=n1;i<=n2;i++){
    if(!isPrime(i)){
      sprintf(ptr,"%d ",i);
      ptr +=strlen(ptr);
    }
  }
  ptr +=strlen(ptr);
  return 0;

}