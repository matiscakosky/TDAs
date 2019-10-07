#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TAM 8


void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp){
	heap_t* heap = heap_crear(cmp);
	void** arreglo = malloc(sizeof(void*) * k);
	
	//Lleno un heap de k elementos (si k es mayor a tam_datos cortara la iteracion una vez llenados los primeros datos)
	for(int i = 0; i<k && i<tam_datos; i++){
		printf("dato a encolar %d\n",*(int*)datos[i]);
		heap_encolar(heap,datos[i]);
	}
	for(size_t i = k; i < tam_datos;i++){
		if(cmp(heap_ver_max(heap),datos[i]) > 0){
			heap_desencolar(heap);
			heap_encolar(heap,datos[i]);
		}
	}
	for(int i=0; i<k;i++){
		if(!heap_esta_vacio(heap)){
			arreglo[i] = heap_desencolar(heap);
			continue;
		}
		arreglo[i] = NULL;
	}
	heap_destruir(heap,NULL);
	return arreglo;
	
	
	
}