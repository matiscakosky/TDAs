#define _POSIX_C_SOURCE 200809L

#include "hash.h"
#include "strutil.h"
#include "cola.h"
#include "pila.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MODO_LECTURA "r"
#define MODO_1 "-1"
#define MODO_2 "-2"
#define UNO 
#define ENDFILE -1

hash_t* colocar_en_hash(hash_t* hash, char* archivo, bool es_primer_arch,int *en_uno,int *en_ambos);
void imprimir(hash_t* hash, int* cant_archivos); 

int comm(int cant_parametros, char* entrada[]){
	hash_t* hash = hash_crear(NULL);
	if (hash == NULL) return -1;
	int* en_uno = malloc(sizeof(int));
	*en_uno = 1;
	int* en_ambos = malloc(sizeof(int));
	*en_ambos = 2;
	
	if (cant_parametros == 3){			
		hash = colocar_en_hash(hash, entrada[1], true, en_uno, en_ambos);
		hash = colocar_en_hash(hash, entrada[2], false, en_uno, en_ambos);	
		imprimir(hash, en_ambos);
	}	

	if(cant_parametros == 4){		
		if(strcmp(entrada[3],MODO_1) == 0){
			hash = colocar_en_hash(hash, entrada[1], true, en_uno, en_ambos);
			hash = colocar_en_hash(hash, entrada[2], false, en_uno, en_ambos);
			imprimir(hash, en_uno);
				
		} else if (strcmp(entrada[3],MODO_2) == 0){
			hash = colocar_en_hash(hash, entrada[2], true, en_uno, en_ambos);
			hash = colocar_en_hash(hash, entrada[1], false, en_uno, en_ambos);
			imprimir(hash, en_uno);
		}
	}
	free(en_uno);
	free(en_ambos);
	hash_destruir(hash);
	return 0;	
}



hash_t* colocar_en_hash(hash_t* hash, char* entrada,bool es_primer_arch,int* en_uno,int* en_ambos){
	 
	FILE *archivo = fopen(entrada, MODO_LECTURA);
	if (archivo == NULL) NULL;
	
	size_t capacidad = 0;
	char* linea = NULL;
	
	size_t largo = getline(&linea, &capacidad, archivo);
	
	while (largo != ENDFILE){
		linea[largo-1] = '\0';
		if (!strcmp(linea,"\n")) continue;
		if (es_primer_arch){
			hash_guardar(hash, linea, en_uno);
		}
		else {
			int* apariciones = hash_obtener(hash,linea);
			if(apariciones){ //Modifica el valor sólo de los que estan en ambos archivos.
				hash_guardar(hash, linea, en_ambos);
			}
		}
		largo = getline(&linea, &capacidad, archivo);
	}
	if (linea != NULL){
		free(linea);
		fclose(archivo);
	}	
	return hash;
}	

void imprimir(hash_t* hash, int* cant_archivos){
//cant_archivos es la variable que determina la hora de imprimir, 
//si se desea que las lineas estén en un solo archivo o en ambos.	
	hash_iter_t* iter = hash_iter_crear(hash);
	while(!hash_iter_al_final(iter)){
		const char* linea = hash_iter_ver_actual(iter);
		if (*(int*)hash_obtener(hash, linea) == *cant_archivos){
			fprintf(stdout, "%s \n", linea);
		}
		hash_iter_avanzar(iter);
	}
	hash_iter_destruir(iter);
}
		
int main(int argc, char* argv[]){
	return comm(argc, argv);
}