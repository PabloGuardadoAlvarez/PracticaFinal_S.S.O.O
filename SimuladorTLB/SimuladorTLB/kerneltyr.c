#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_LINE 100

int main(){
 printf("hola");
	int pipe;
	char line[MAX_LINE];

int c;
FILE *file;
file = fopen("accesos_memoria.txt", "r");
if (file) {
    while ((c = getc(file)) != EOF)
        printf(c);
    fclose(file);
    }
return 0;
}   
