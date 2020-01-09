﻿#include <stdio.h>
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

                fp = fopen("accesos_memoria.txt", "r");
                mkfifo("/tmp/myFIFO", 0666);
                pipe = open("/tmp/myFIFO", O_WRONLY);
                pid = fork();
                if(pid==0){

                char *args[] = {"pb",0};
                char *env[] = {0};
                execve("tlb",args,env);

                }else{

                if (fp == NULL){
                    printf("Could not open file %s","accesos_memoria.txt");
                    return 1;
                }else{
                    //printf("file opened succesfully");
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
