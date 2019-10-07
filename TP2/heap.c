#include "heap.h"
#include "vector_dinamico.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define TAM_I 8
#define REDIM 2


struct heap{
	size_t cant;
	cmp_func_t cmp;
	vector_t* arreglo;
};

void swap(vector_t* vector, size_t pos1, size_t pos2){
	void* aux1 = vector_obtener(vector,pos1);
	void* aux2 = vector_obtener(vector,pos2);
	vector_guardar(vector,pos1,aux2);
	vector_guardar(vector,pos2,aux1);
	return; 
	
}

void swap_arr(void *elementos[], size_t pos1, size_t pos2){
	void* aux = elementos[pos1];
	elementos[pos1] = elementos[pos2];
	elementos[pos2] = aux;
}

/*Funciones adicionales del TDA Heap*/
void heapify(vector_t* arreglo,size_t cant,cmp_func_t cmp);
void downheap(vector_t* arreglo, size_t pos, size_t cant,cmp_func_t cmp);
void upheap(vector_t* arreglo, size_t pos, size_t cant,cmp_func_t cmp);
void heap_sort_heapificado(vector_t* arreglo,size_t cant,cmp_func_t cmp);

/*Funciones adicionales para Heap_sort*/
void heapify_arr(void** a ,size_t cant,cmp_func_t cmp);
void downheap_arr(void** a, size_t pos, size_t cant,cmp_func_t cmp);


/* ******************************************************************
 *        		     		HEAP SORT
 * *****************************************************************/
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	if(cant-1 == 0) return;
	heapify_arr(elementos,cant,cmp);
	swap_arr(elementos,0,cant-1);
	heap_sort(elementos,cant-1,cmp);
}

/* ******************************************************************
 *             				TDA HEAP
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	heap->cant = 0;
	heap->cmp = cmp;
	vector_t* vector = vector_crear(TAM_I);
	heap->arreglo = vector;
	if (!heap->arreglo){
		free(heap);
		return NULL;
	}
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	heap->cant = n;
	heap->cmp = cmp;
	heap->arreglo = vector_crear(n);
	for (int i = 0;i<n;i++){
		vector_guardar(heap->arreglo,i,arreglo[i]);
	}
	heapify(heap->arreglo,n,cmp);
	return heap;
}

bool heap_encolar(heap_t *heap, void *elem){
	if(heap_esta_vacio(heap)){
		vector_guardar(heap->arreglo,0,elem);
		heap->cant++;
		return true;
	}
	if(heap->cant == vector_obtener_tamanio(heap->arreglo)){ 			
		vector_redimensionar(heap->arreglo, (heap->cant)*REDIM);
	}
	vector_guardar(heap->arreglo,heap->cant,elem);
	upheap(heap->arreglo, heap->cant, heap->cant,heap->cmp);
	heap->cant++;
	return true;
}

void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	void* dato = vector_obtener(heap->arreglo,0);
	swap(heap->arreglo,0,heap->cant-1);
	heap->cant--;
	downheap(heap->arreglo,0,heap->cant,heap->cmp);
	return dato;
}
	

	
size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
	return (heap->cant == 0);
}


void *heap_ver_max(const heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	return vector_obtener(heap->arreglo,0);
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if (destruir_elemento){
		for(int i = 0; i < heap->cant;i++){
			destruir_elemento(vector_obtener(heap->arreglo,i));
		}
	}
	vector_destruir(heap->arreglo);
	free(heap);	
}

/* ******************************************************************
 *             				FUNCIONES ADICIONALES
 * *****************************************************************/

void upheap(vector_t* arreglo, size_t pos, size_t cant,cmp_func_t cmp){
	if (pos == 0) return;
	size_t pos_padre = (pos-1)/2;
	if(cmp(vector_obtener(arreglo,pos),vector_obtener(arreglo,pos_padre)) > 0 ){
		swap(arreglo,pos,pos_padre);
		upheap(arreglo,pos_padre,cant,cmp);
	}

}



void downheap(vector_t* arreglo, size_t pos, size_t cant,cmp_func_t cmp){
	if (pos >= cant) return;
	size_t pos_h_izq = pos*2 + 1;
	size_t pos_h_der = pos*2 + 2;
	size_t pos_mayor = pos;
	if (pos_h_izq < cant && cmp(vector_obtener(arreglo,pos),vector_obtener(arreglo,pos_h_izq)) <= 0){
		pos_mayor = pos_h_izq;
	}
	if (pos_h_der < cant && cmp(vector_obtener(arreglo,pos_mayor),vector_obtener(arreglo,pos_h_der)) < 0){
		pos_mayor = pos_h_der;
	}
	if (pos_mayor != pos){
		swap(arreglo,pos,pos_mayor);
		downheap(arreglo,pos_mayor,cant,cmp);
	}
}

void heapify(vector_t* arreglo,size_t cant,cmp_func_t cmp){
	for(size_t i = (cant/2)-1; i != -1; i--){
		downheap(arreglo,i,cant,cmp);
	}
}


/*Funciones adicionales de Heap-sort*/


void heapify_arr(void** a,size_t cant,cmp_func_t cmp){
	for(size_t i = (cant/2)-1; i != -1; i--){
		downheap_arr(a,i,cant,cmp);
	}
	return;
}

void downheap_arr(void** a, size_t pos, size_t cant,cmp_func_t cmp){
	if (pos >= cant) return;
	size_t pos_h_izq = pos*2 + 1;
	size_t pos_h_der = pos*2 + 2;
	size_t pos_mayor = pos;
	if (pos_h_izq < cant && cmp(a[pos],a[pos_h_izq]) <= 0){
		pos_mayor = pos_h_izq;
	}
	if (pos_h_der < cant && cmp(a[pos_mayor],a[pos_h_der]) < 0){
		pos_mayor = pos_h_der;
	}
	if (pos_mayor != pos){
		swap_arr(a,pos,pos_mayor);
		downheap_arr(a,pos_mayor,cant,cmp);
	}
}



/*Funciones del TP2*/

void heap_actualizar_prioridad(heap_t* heap, void* dato){
	size_t cant = heap->cant;
	int i;
	for (i=0; i<cant; i++){
		if(vector_obtener(heap->arreglo,i) == dato){
			break;
		}
	}

	void* yo = vector_obtener(heap->arreglo,i);
	void* h_der = vector_obtener(heap->arreglo,i*2+2);
	void* h_izq = vector_obtener(heap->arreglo,i*2+1);
	void* padre = vector_obtener(heap->arreglo,(i-1)/2);
	//Pregunto por si es mayor que sus hijos
	if(h_der && h_izq){
		if(!(heap->cmp(yo,h_izq) > 0) || !(heap->cmp(yo,h_der) > 0)){
			downheap(heap->arreglo,i,heap->cant,heap->cmp);
		}
	}
	//Pregunto por si es menor que el padre
	if(padre){
		if (heap->cmp(yo,padre) > 0){
			upheap(heap->arreglo,i,heap->cant,heap->cmp);
		}
	}
	return;	
}









