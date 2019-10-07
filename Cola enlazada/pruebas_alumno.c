#include "cola.h"
#include "testing.h"
#include "pila.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define VOL 5000

void crear_cola_vacia(void);
void prueba_algunos_elementos(void);
void prueba_volumen_elementos(void);
void prueba_encolar_distintos(void);
void prueba_encolar_vector_heap(void);
void cast_pila(void* pila);


void cast_pila(void* pila){
	pila_destruir((pila_t*)pila);
}

void prueba_encolar_distintos(void){
	printf("**************INICIO DE LA PRUEBA DE DISTINTOS ELEMENTOS**************\n");
	cola_t* cola = cola_crear();
	pila_t* pila = pila_crear();
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* p_desencolada;
	print_test("las pilas fueron creadas correctamente",true);
	int a=5, *valor;
	bool ok;
	
	//Creo los distintos tipos de datos para apilar
	char* letra = "c";
	char v[]= "Algoritmos";
	long numlong = 34.00;
	int numint = 45;
	int arreglo[5]={0,1,2,3,4};
	
	//Apilo los datos segun los como los inicialice
	ok = pila_apilar(pila, letra);
	ok = pila_apilar(pila, v);
	ok = pila_apilar(pila, &numlong);
	ok = pila_apilar(pila, &numint);
	ok = pila_apilar(pila, arreglo);
	print_test("Todo se apilo de forma correcta", ok);
	
	//Encolo un elemento de tipo int
	ok = cola_encolar(cola, &a);
	print_test("El elemento de tipo int se encolo de forma correcta", ok);
	
	//Encolo las pilas
	ok = cola_encolar(cola, pila);
	ok = cola_encolar(cola, pila1);
	ok = cola_encolar(cola, pila2);
	print_test("Las pilas se encolaron de forma correcta", ok);
	
	valor = cola_desencolar(cola);
	print_test("El valor se corresponde con el elemento de tipo int", *valor == a);
	
	//Compruebo el dato de la pila
	p_desencolada = cola_ver_primero(cola);
	print_test("El primer dato es el arreglo de enteros", pila_desapilar(p_desencolada) == arreglo);
	
	
	//Destruyo la cola con las pilas adentro
	cola_destruir(cola, cast_pila);
	print_test("la cola fue destruida",true);
}

void prueba_encolar_vector_heap(void){
	printf("**************INICIO DE LA PRUEBA DEL HEAP **************\n");
	cola_t* cola = cola_crear();
	//LLeno de valores los vectores en el heap
	int *valores = malloc(2 * sizeof(int));
	int *valores2 = malloc(3 * sizeof(int));
	valores[0]=5;
	valores[1]=3;
	valores2[0]=-1;
	valores2[1]=10;
	valores2[2]=150;
	
	//Encolo los dos punteros
	cola_encolar(cola, valores);
	cola_encolar(cola, valores2);
	
	//Compruebo los valores que estan al principio de la cola
	int *primero =cola_ver_primero(cola);
	print_test("El primer elemento es el puntero al vector en el heap", primero[0]==5);
	print_test("El segundo elemento es el puntero al vector en el heap", primero[1]==3);
	cola_desencolar(cola);
	free(primero);
	
	//Compruebo los valores que estan al principio de la cola
	primero=cola_ver_primero(cola);
	print_test("El primer elemento es el puntero al segundo vector en el heap", primero[0]==-1);
	print_test("El segundo elemento es el puntero al segundo vector en el heap", primero[1]==10);
	print_test("El tercer elemento es el puntero al segundo vector en el heap", primero[2]==150);
	
	cola_destruir(cola,free);
	print_test("la cola fue destruida",true);
}

void prueba_volumen_elementos(void){
	printf("**************INICIO DE LA PRUEBA DE VOLUMEN**************\n");
	cola_t* cola = cola_crear();
	bool ok;
	int v[VOL];
	for (int i=0; i<VOL; i++){
		v[i]=i;
		ok = cola_encolar(cola, &v[i]);
	}
	print_test("Los elementos se encolaron de forma correcta", ok);
	//Destruyo la cola sin desencolar previamente los elementos
	cola_destruir(cola, NULL);
	print_test("la cola fue destruida", true);

}

void crear_cola_vacia(void){
	printf("**************INICIO DE LA PRUEBA COLA VACIA**************\n");
	cola_t* cola = cola_crear();
	bool ok= false;
	
	//Pregunto si la cola esta vacia
	ok = cola_esta_vacia(cola);
	print_test("la cola esta vacia",ok);
	
	//Destruyo la cola
	cola_destruir(cola, NULL);
	print_test("la cola fue destruida",true);
}
void prueba_algunos_elementos(void){
	printf("**************INICIO DE LA PRUEBA ALGUNOS ELEMENTOS**************\n");
	cola_t* cola = cola_crear();
	bool ok = cola_esta_vacia(cola);
	print_test("la cola esta vacia",ok);
	int a = 5, b=6, c=7, d=8, e=9, *valor;
	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_encolar(cola, &c);
	cola_encolar(cola, &d);
	cola_encolar(cola, &e);
	cola_encolar(cola, &a);
	
	valor = cola_desencolar(cola);
	print_test("el valor se corresponde con el desencolado", *valor == a);
	
	valor = cola_desencolar(cola);
	print_test("el valor se corresponde con el desencolado", *valor == b);
	
	valor = cola_desencolar(cola);
	print_test("el valor se corresponde con el desencolado", *valor == c);
	
	valor = cola_desencolar(cola);
	print_test("el valor se corresponde con el desencolado", *valor == d);
	
	valor = cola_desencolar(cola);
	print_test("el valor se corresponde con el desencolado", *valor == e);
	
	valor = cola_desencolar(cola);
	print_test("el valor se corresponde con el desencolado", *valor == a);
	
	ok = cola_esta_vacia(cola);
	print_test("la cola esta vacia",ok);
	cola_destruir(cola, NULL);
	print_test("la cola fue destruida",true);
	
}

void pruebas_cola_alumno(){
	crear_cola_vacia();
	prueba_algunos_elementos();
	prueba_volumen_elementos();
	prueba_encolar_distintos();
	prueba_encolar_vector_heap();
}