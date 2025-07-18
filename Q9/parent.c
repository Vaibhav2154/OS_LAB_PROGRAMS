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
  int shmid;

  shmid = shmget((key_t)1122,4096,0666 | IPC_CREAT);
  void *ptr = shmat(shmid,NULL,0666);

  pid_t pid;

  pid = fork();

  if(pid == 0){
    execlp("./fib","fib",argv[1],NULL);
  }else{
    wait(NULL);
    printf("This is parent printing the fibonacci numbers \n");
    printf("%s",(char *)ptr);
    shmdt(ptr);
  }
  return 0;
}