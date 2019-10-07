#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define CLOSE_FREE_ALL free(linea); fclose(f1);

int main(int argc, char *argv[]){
	if(argc != 3) {
		fprintf(stderr, "ERR: La cantidad de parametros es incorrecta\n");
		return -1;
	}
	
	if(!isdigit((int)argv[2][0])){
      fprintf(stderr, "ERR: Por favor ingrese un numero entero de lineas para leer\n");
		return -1;
	}
	char *p, *linea=NULL;
	size_t cant=0;
	size_t capacidad = 0;
	int numero =(int) strtol(argv[2], &p, 10);
	FILE *f1;
	f1 = fopen(argv[1], "rt");
	
	//Imprimir las lineas pasadas por parametro
	for (int i=0; i<numero; i++){
		cant = getline(&linea,&capacidad,f1);
		if ((int)cant == -1) break;
		if (linea[cant-1] != '\n'){
			fprintf(stdout,"%s\n",linea);
			break;
		}
		fprintf(stdout,"%s",linea);
	}

	//Imprimir las lineas que siguen
	while (getchar()){
		cant = getline(&linea,&capacidad,f1);
		if ((int)cant == -1) break;
		if (linea[cant-1] != '\n'){
			fprintf(stdout,"%s\n",linea);
			break;
		}
		fprintf(stdout,"%s",linea);
	}
	CLOSE_FREE_ALL;
	return 0;
}