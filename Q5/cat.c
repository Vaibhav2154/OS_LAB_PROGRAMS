#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
DIR *dp;
struct dirent *dirp;
if(argc<2)
{
printf("\n You are not passing the directory\n");
exit(1);
}
if((dp=opendir(argv[1]))==NULL)
{
printf("\nCannot open it does't exist %s file!\n",argv[1]);
exit(1);
}
while((dirp=readdir(dp))!=NULL)
printf("%s\n",dirp->d_name);
closedir(dp);
}

// Simulation of "rm" command
#include<stdio.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
//char fn[10];
if (argc<2)
{
printf("Insufficient arguments");
exit(1);
}
if(unlink(argv[1])==0) //if(remove(argv[1])==0)
printf("File removed\n");
else
printf("File cannot be removed\n");
}

// Simulation of "grep" command
#include<stdio.h>
#include<string.h>
void main()
{
char fn[10],pat[10],temp[200];
FILE *fp;
printf("Enter file name\n");
scanf("%s",fn);
printf("Enter pattern to be searched\n");
scanf("%s",pat);
fp=fopen(fn,"r");
while(!feof(fp))
{
//fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string

pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-
of-file is reached, whichever comes first.

fgets(temp,100,fp);
if(strstr(temp,pat))//finds the first occurrence of the substring in the string
printf("%s",temp);
}
fclose(fp);
}

//simulate CAT cmd (VIEW only)
#include<stdio.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
FILE *fp;
char ch;
if(argc<2)
{
printf("File not entered");
exit(1);
}
fp=fopen(argv[1],"r");
if(fp==NULL)
{
printf("File does not exist\n");
exit(1);
}
while((ch=fgetc(fp))!=EOF)
printf("%c",ch);
fclose(fp);
printf("\n");
}

//simulate cat cmd (cat >> f1 f2)
#include<stdio.h>
#include<stdlib.h>
void main(int argc, char *argv[])
{
FILE *fp1,*fp2;
char ch;
if(argc<3)
{
printf("insufficient no. of arguments\n");
exit(1);
}
fp1=fopen(argv[1],"a");
fp2=fopen(argv[2],"r");
if(fp2==NULL)
{
printf("Error in opening file\n");
exit(1);
}
while((ch=fgetc(fp2))!=EOF)
fprintf(fp1,"%c",ch);
fclose(fp1);
fclose(fp2);
}