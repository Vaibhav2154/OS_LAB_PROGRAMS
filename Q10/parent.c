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
  int shmfd;
  
  pid_t pid;
  
  pid = fork();
  
  if(pid == 0){
    execlp("./fib","fib",argv[1],argv[2],NULL);
  }else{
    wait(NULL);
      shmfd = shm_open("Vss",O_RDONLY,0666);
      void *ptr = mmap(0,4096,PROT_READ,MAP_SHARED,shmfd,0);
    printf("This is parent printing the fibonacci numbers \n");
    printf("%s",(char *)ptr);
    printf("\n");
    shm_unlink("Vss");
  }
  return 0;
}