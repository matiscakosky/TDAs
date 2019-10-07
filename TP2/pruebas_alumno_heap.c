#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define TAM 8
#define TAM2 13


int f_min(const void*elem1,const void* elem2){
	int* a = (int*) elem1;
	int* b = (int*) elem2;
	if (*a > *b) return -1;	
	if (*a < *b) return 1;
	return 0;
}

int f_max(const void*elem1,const void* elem2){
	int* a = (int*) elem1;
	int* b = (int*) elem2;
	if (*a > *b) return 1;	
	if (*a < *b) return -1;
	return 0;
}

static void prueba_heap_actualizar_prioridad(){
	printf("*****************************************************INICIO DE LA PRUEBA HEAP ACTUALIZAR PRIORIDAD*****************************************************\n");
	int c1=12,c2=15,c3=-1,c4=7,c5=11,c6=9,c7=8,c8=10;
	int* a[TAM];
	a[0] = &c1;
	a[1] = &c2;
	a[2] = &c3;
	a[3] = &c4;
	a[4] = &c5;
	a[5] = &c6;
	a[6] = &c7;
	a[7] = &c8;
	void* arreglo = a;
	heap_t* heap = heap_crear_arr(arreglo,TAM,f_max);
	print_test("Maximo es C2",heap_ver_max(heap) == &c2);
	c8 = 100;
	heap_actualizar_prioridad(heap,&c8);
	int* prioridad_max = heap_desencolar(heap);
	print_test("La prioridada de c3 fue actualizada de mas baja a mas alta", *prioridad_max == c8);
	print_test("Le sigue c2",heap_ver_max(heap) == &c2);
	heap_destruir(heap,NULL);
	
	
}


void prueba_heap_sort(){
	printf("*****************************************************INICIO DE LA PRUEBA HEAP SORT*****************************************************\n");
	int c1=1,c2=2,c3=3,c4=4,c5=5,c6=6,c7=7,c9=9;
	int* a[TAM];
	a[0] = &c7;
	a[1] = &c5;
	a[2] = &c6;
	a[3] = &c3;
	a[4] = &c4;
	a[5] = &c2;
	a[6] = &c1;
	a[7] = &c9;
	void* arreglo = a;
	heap_sort(arreglo,TAM,f_max);
	for(int i =0;i<TAM;i++){
		printf("%d\n",*a[i]);
	}	
}
void prueba_heap_crear_arreglo(){
	printf("*****************************************************INICIO DE LA PRUEBA HEAP CREAR ARREGLO*****************************************************\n");
	int c1=1,c2=2,c3=3,c4=4,c5=5,c6=6,c7=7,c9=9;
	int* a[TAM];
	a[0] = &c7;
	a[1] = &c5;
	a[2] = &c6;
	a[3] = &c3;
	a[4] = &c4;
	a[5] = &c2;
	a[6] = &c1;
	a[7] = &c9;
	void* arreglo = a;
	heap_t* heap = heap_crear_arr(arreglo,TAM,f_max);
	print_test("El heap tiene c9 en el tope", heap_ver_max(heap) == &c9);
	print_test("Desencolar el maximo, es c9", heap_desencolar(heap) == &c9);
	print_test("Desencolar el maximo, es c7", heap_desencolar(heap) == &c7);
	print_test("Desencolar el maximo, es c6", heap_desencolar(heap) == &c6);
	print_test("Desencolar el maximo, es c5", heap_desencolar(heap) == &c5);
	print_test("Desencolar el maximo, es c4", heap_desencolar(heap) == &c4);
	print_test("Desencolar el maximo, es c3", heap_desencolar(heap) == &c3);
	print_test("Desencolar el maximo, es c2", heap_desencolar(heap) == &c2);
	print_test("Desencolar el maximo, es c1", heap_desencolar(heap) == &c1);
	print_test("La cantidad de el,elementos es 0", (heap_cantidad(heap) == 0));
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	heap_destruir(heap,NULL);
}

void prueba_heap_desencolar(){
	printf("*****************************************************INICIO DE LA PRUEBA HEAP DESENCOLAR*****************************************************\n");
	int c1=1,c2=2,c3=3,c4=4,c5=5,c6=6,c7=7,c9=9;
	heap_t* heap = heap_crear(f_max);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("Heap encolar", heap_encolar(heap,&c7));
	print_test("Heap encolar", heap_encolar(heap,&c5));
	print_test("Heap encolar", heap_encolar(heap,&c6));
	print_test("Heap encolar", heap_encolar(heap,&c3));
	print_test("Heap encolar", heap_encolar(heap,&c4));
	print_test("Heap encolar", heap_encolar(heap,&c2));
	print_test("Heap encolar", heap_encolar(heap,&c1));
	print_test("Heap encolar", heap_encolar(heap,&c9));
    print_test("El heap tiene c9 en el tope", heap_ver_max(heap) == &c9);
	print_test("Desencolar el maximo, es c9", heap_desencolar(heap) == &c9);
	print_test("Desencolar el maximo, es c7", heap_desencolar(heap) == &c7);
	print_test("Desencolar el maximo, es c6", heap_desencolar(heap) == &c6);
	print_test("Desencolar el maximo, es c5", heap_desencolar(heap) == &c5);
	print_test("Desencolar el maximo, es c4", heap_desencolar(heap) == &c4);
	print_test("Desencolar el maximo, es c3", heap_desencolar(heap) == &c3);
	print_test("Desencolar el maximo, es c2", heap_desencolar(heap) == &c2);
	print_test("Desencolar el maximo, es c1", heap_desencolar(heap) == &c1);
	print_test("La cantidad de el,elementos es 0", (heap_cantidad(heap) == 0));
	print_test("El heap esta vacio", heap_esta_vacio(heap));	
	heap_destruir(heap,NULL);
	
}

void prueba_heap_encolar_desencolar_algunos(){
	int c1 = 1;
	int c2 = 2;
	int c3 = 3;
	int c4 = 4;
	heap_t* heap = heap_crear(f_max);
	printf("*****************************************************INICIO DE LA PRUEBA HEAP ENCOLAR*****************************************************\n");
    print_test("El heap fue creado", heap);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("Heap encolar", heap_encolar(heap,&c1));
    print_test("Heap encolar", heap_encolar(heap,&c2));
    print_test("Heap encolar", heap_encolar(heap,&c3));
    print_test("Heap encolar", heap_encolar(heap,&c4));
    print_test("Heap encolar", heap_encolar(heap,&c4));
    print_test("El heap tiene c4 en el tope", heap_ver_max(heap) == &c4);
    print_test("Desencolar el maximo, es c4", heap_desencolar(heap) == &c4);
    print_test("Desencolar el maximo, es c4", heap_desencolar(heap) == &c4);
    print_test("Desencolar el maximo, NO es c4", !(heap_desencolar(heap) == &c4));
    print_test("El heap tiene c2 en el tope", heap_ver_max(heap) == &c2);
	
	heap_destruir(heap,NULL);	

}

void prueba_heap_vacio(){
	heap_t* heap = heap_crear(f_max);
	printf("*****************************************************INICIO DE LA PRUEBA HEAP VACIO*****************************************************\n");
    print_test("El heap fue creado", heap);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("La cantidad de el,elementos es 0", (heap_cantidad(heap) == 0));
    print_test("Prueba heap desencolar es NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba heap desencolar es NULL", heap_ver_max(heap) == NULL);
	heap_destruir(heap,NULL);	
}

void pruebas_heap_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
	prueba_heap_vacio();
	prueba_heap_encolar_desencolar_algunos();
	prueba_heap_desencolar();
	prueba_heap_crear_arreglo();
	prueba_heap_sort();
	prueba_heap_actualizar_prioridad();
	
}