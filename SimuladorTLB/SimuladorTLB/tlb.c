#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE 100

typedef struct {
 short int pagina;
 short int marco;
 short int valida;
 int tiempo;
} T_TLB;

int main()
{
	char line[MAX_LINE];
	int pipe;

	if ((pipe = open("/tmp/myFIFO",O_RDONLY)) < 0)
	{
		printf("ERROR: Imposible abrir el pipe FIFOTLB\n");
		return -1;
	}else{
        //printf("Se a abierto el pipe FIFOTLB \n");
    }

	while(read(pipe, line, MAX_LINE))
	    printf("\n%s\n", line);
	close(pipe);
	return 0;
}
