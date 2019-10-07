#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CLOSE_FREE_ALL free(l2); free(l1); fclose(f1); fclose(f2);


int main(int argc, char *argv[]){
	if(argc != 3) {
		fprintf(stderr, "ERR: La cantidad de parametros es incorrecta\n");
		return -1;
	}
	
	size_t capacidad = 0;
	FILE *f1, *f2;
	f1 = fopen(argv[1], "rt");
	f2 = fopen(argv[2], "rt");
	char *l1=NULL, *l2=NULL;
	size_t cant1;
	cant1 = getline(&l1, &capacidad, f1);
	while (cant1 != -1){
		if (getline(&l2, &capacidad, f2)){
			size_t cant2 = strlen(l2);
			if (l1[cant1-1] == '\n'){
				l1[cant1-1] = '\t';
			}
			else{
				char* aux = realloc(l1,cant1+2);
				l1 = aux;
				l1[cant1] = '\t';
			}
			
			if(l2[cant2-1] == '\n'){
				fprintf(stdout,"%s%s",l1,l2);
			}
			else{
				fprintf(stdout,"%s%s\n",l1,l2);
			}
		}
		else{
			fprintf(stderr,"El segundo archivo no tenia tantas lineas como el primero\n");
			CLOSE_FREE_ALL;
			return -1;
		}
		cant1 = getline(&l1, &capacidad, f1);
	}


	if (getline(&l2, &capacidad, f2) != -1){
			fprintf(stderr,"El primer archivo no tenia tantas lineas como el segundo\n");
			CLOSE_FREE_ALL;
			return -1;
	}
	
	CLOSE_FREE_ALL;
	return 0;
}

			
			