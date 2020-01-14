#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE 100
#define FALLO 0
#define ACIERTO 1

typedef struct {
 short int pagina;
 short int marco;
 short int valida;
 int tiempo;
} T_TLB;

int tiempoglobal=0, numfallos=0, i;
T_TLB arrTlb [4];

void drawTabla(T_TLB arrTlb[]){
	    for(i =0;i<4;i++){
			printf("p:%X\tm:%d\tv:%d\tt:%d\n",arrTlb[i].pagina,arrTlb[i].marco,arrTlb[i].valida,arrTlb[i].tiempo);
		}
		printf("\n");
	}

int main()
{
	arrTlb[0].marco=2;
	arrTlb[1].marco=3;
	arrTlb[2].marco=0;
	arrTlb[3].marco=1;

	for(i=0;i<4;i++){
		arrTlb[i].pagina=255;
		arrTlb[i].valida = 0;
		arrTlb[i].tiempo = 0;
		}

	char line[MAX_LINE];
	int pipe, direcciones;


	if ((pipe = open("/tmp/myFIFO",O_RDONLY)) < 0)
	{
		printf("ERROR: Imposible abrir el pipe FIFOTLB\n");
		return -1;
	}else{
        printf("Se a abierto el pipe FIFOTLB \n");
    }
	drawTabla(arrTlb);
	while(read(pipe, line, MAX_LINE)){
    sscanf(line,"%X",&direcciones);
    //printf("tiempo global: %d\n",tiempoglobal);
    //printf("pagina: %d\n",arrTlb[0].pagina);
    //printf("soy tlb: %04X\n",direcciones);
    //arrTlb[i].pagina = (direcciones & 0xF000)>>12;
    int pagina = (direcciones & 0xF000)>>12;
	int offset = (direcciones & 0x0FFF);
	int estado = FALLO;
		for(i =0;i<4;i++){

			if(arrTlb[i].pagina != pagina){
					estado = FALLO;
				}else{
					estado = ACIERTO;
					break;
					}
		}
		int tiempo_min = 0;
		tiempoglobal++;
		if(estado == FALLO){
			tiempoglobal++;
			numfallos++;
			printf("Fallo de TLB %d, VADDR %04X pagina %X offset %04X\n",numfallos,direcciones,pagina, offset);
		int tiempo_actual=arrTlb[0].tiempo;
		for(i =0;i<4;i++){
			if(arrTlb[i].valida == 0){
				tiempo_min=i;
				break;
				}else if(arrTlb[i].tiempo < tiempo_actual ){
					tiempo_actual = arrTlb[i].tiempo;
					tiempo_min = i;
				}
		}
				arrTlb[tiempo_min].pagina = pagina;
				arrTlb[tiempo_min].valida = 1;

  }
  for(i=0;i<4;i++){
	  if(pagina == arrTlb[i].pagina){
		  arrTlb[i].tiempo = tiempoglobal;
		break;
		  }
	  }
printf("ACIERTO,VADDR %04X pagina %X offset %04X marco %d => PSYADDR %d%03X\n",direcciones,pagina, offset, arrTlb[i].marco, arrTlb[i].marco, offset);

  drawTabla(arrTlb);

}
close(pipe);
return 0;
}
