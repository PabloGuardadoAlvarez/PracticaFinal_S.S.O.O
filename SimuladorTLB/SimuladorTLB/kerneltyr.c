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
	int pipe;
	char line[MAX_LINE];
  pid_t pid;
  char * myfifo = "/tmp/myfifo";

                fp = fopen("accesos_memoria.txt", "r");
                mkfifo(myfifo, 0666);
                pipe = open(myfifo, O_WRONLY);
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
                        printf("file opened succesfully");
                  }
                  while (fgets(line, MAX_LINE, (FILE*)fp) != NULL){
                        write(pipe, line, sizeof(line));
                        sleep(2);
                  }
                 fclose(fp);
                 close(pipe);
                }
return 0;
}
