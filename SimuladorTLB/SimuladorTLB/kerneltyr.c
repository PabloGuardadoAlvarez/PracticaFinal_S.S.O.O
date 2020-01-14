#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE 100

int main(){
	FILE *fp;
	int pipe ,aux;
	char line[MAX_LINE];
	pid_t pid;

                fp = fopen("accesos_memoria.txt", "r");
                mkfifo("/tmp/myFIFO", 0666);
                pipe = open("/tmp/myFIFO", O_WRONLY);
                pid = fork();
                if(pid==0){
                  char *args[] = {"pb",0};
                  char *env[] = {0};
                  execve("tlb",args,env);
                }else{
                  printf("kerneltyr, mi pid es %d y la de tlb es %d\n",
                  getppid(),getpid());
                  if (fp == NULL){
                        printf("Could not open file %s","accesos_memoria.txt");
                        return 1;
                  }else{
                        //printf("file opened succesfully");
                  }
                  while (fgets(line,MAX_LINE,fp)){
                        sscanf(line,"%X",&aux);
                        sprintf(line,"%04X",aux);
                        write(pipe,line,strlen(line));
                        sleep(2);
                  }
                 fclose(fp);
                 close(pipe);
                }
return 0;
}
