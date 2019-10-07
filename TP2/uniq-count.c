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

hash_t* colocar_en_hash(hash_t* hash, char* archivo, bool es_primer_arch);

int uniq (int cant_parametros, char* entrada[]){
	if (cant_parametros != 2){
		fprintf(stderr, "La cantidad de parámetros no es válida \n");
		return -1;
	}
	
	hash_t* hash = hash_crear(NULL); 
	cola_t* cola = cola_crear();
	pila_t* referencias = pila_crear();
	int* repeticiones;
	int i = 0;
	
	FILE *archivo = fopen(entrada[1], MODO_LECTURA);
	if (!archivo){
		return 1;
	}
	
	size_t capacidad = 0;
	char* linea = NULL; 
	size_t longitud = getline(&linea, &capacidad, archivo);
	while (longitud != ENDFILE){
		linea[longitud-1] = '\0';
		if (strcmp(linea,"\n")==0) continue;
		i = 0;
		char** arreglo = split(linea, ' ');
		pila_apilar(referencias,arreglo);
		while (arreglo[i]){
			repeticiones = hash_obtener(hash, arreglo[i]);
			if(!repeticiones){
				int* prim = malloc(sizeof(int*));
				*prim = 1; 
				cola_encolar(cola, arreglo[i]);
				hash_guardar(hash, arreglo[i], prim);
			} else {
				*repeticiones = *repeticiones + 1;
				hash_guardar(hash, arreglo[i], repeticiones);
			}
			i++;
		}
		longitud = getline(&linea, &capacidad, archivo);
	}
	while (!cola_esta_vacia(cola)){
		char* palabra = cola_desencolar(cola);
		repeticiones = hash_obtener(hash, palabra);
		printf("%d %s \n",*repeticiones, palabra);
		free(repeticiones);
		
	}
	while(!pila_esta_vacia(referencias)){
		char** arreglo = pila_desapilar(referencias);
		free_strv(arreglo);
	}
	
	free(linea);
	pila_destruir(referencias);
	fclose(archivo);
	hash_destruir(hash);
	cola_destruir(cola,NULL);
	return 0;
}
					
int main(int argc, char* argv[]){
	uniq(argc, argv);
}