#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define NUM 64
#define MUL 5
#define VOL 5000

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void prueba_algunos_elementos(void);
void prueba_null(void);
void prueba_pila_vacia(void);
void prueba_volumen_elementos(void);
void prueba_apilar_diferentes(void);
void prueba_memoria_dinamica(void);



void prueba_memoria_dinamica(void){
	printf("**************INICIO DE LA PRUEBA DE MEMORIA DINAMICA**************\n");
	pila_t* pila = pila_crear();
	bool ok = false;
	int* valores = malloc(NUM*sizeof(int));
	int* valores1 = malloc(NUM*sizeof(int));
	int* valores2 = malloc(NUM*sizeof(int));
	for (int i=0; i<NUM; i++){
		valores[i] = i;
		valores1[i] = i*MUL ;
		valores2[i] = i;
	}
	ok = pila_apilar(pila,valores2);
	ok = pila_apilar(pila,valores1);
	ok = pila_apilar(pila,valores);
	print_test("los valores se apilaron correctamente",ok);
	
	int* apilado = pila_ver_tope(pila);
	print_test("El primer valor del primer puntero  desapilado coincide", apilado[0] == 0);
	pila_desapilar(pila);
	apilado = pila_ver_tope(pila);
	print_test("El ultimo valor del puntero se corresponde con el ultimo del desapilado", apilado[NUM-1] == valores1[NUM-1]);
	
	pila_destruir(pila);
	free(valores);
	free(valores1);
	free(valores2);
	print_test("se destruyo la pila", true);
	
	
	
		
}


void prueba_apilar_diferentes(void){
	printf("**************INICIO DE LA PRUEBA DE DIFERENTES TIPOS DE ELEMENTOS**************\n");
	pila_t* pila = pila_crear();
	print_test("la pila inicialmente esta vacia", pila_esta_vacia(pila));
	print_test("la pila inicialmente tiene null en su tope", pila_ver_tope(pila)==NULL);
	//Creo los distintos tipos de datos para apilar
	char* letra = "c";
	char v[]= "Algoritmos";
	long numlong = 34.00;
	int numint = 45;
	int arreglo[5]={0,1,2,3,4};
	
	//Apilo los datos segun los como los inicialize
	pila_apilar(pila, letra);
	pila_apilar(pila, v);
	pila_apilar(pila, &numlong);
	pila_apilar(pila, &numint);
	pila_apilar(pila, arreglo);
	
	//Desapilo los datos
	print_test("El primer dato es el arreglo de enteros", pila_desapilar(pila)==arreglo);
	int* valor_entero = pila_desapilar(pila);
	print_test("El segundo dato es el el int", *valor_entero == numint);
	long* valor_long = pila_desapilar(pila);
	print_test("El tercer dato es el long", *valor_long == numlong);
	print_test("El cuarto dato es el arreglo de chars", pila_desapilar(pila) == v);
	char* valor_char = pila_desapilar(pila);
	print_test("El quinto dato es el char", valor_char == letra);
	
	//destruyo la pila
	pila_destruir(pila);
	print_test("se destruyo la pila", true);
	
	

}
void prueba_volumen_elementos(void){
	printf("**************INICIO DE LA PRUEBA DE VOLUMEN**************\n");
	pila_t* pila = pila_crear();
	//lleno la pila de elementos con un valor random al principio
	int v[VOL];
	int valor_random = 250;
	bool ok = true;
	ok = pila_apilar(pila,&valor_random);
	for (int i=0; i<VOL;i++){
		v[i]=i;
		ok &= pila_apilar(pila, &v[i]);	
	}
	print_test("la pila fue llenada con exito",ok);
	
	//desapilo la pila
	int* valor_pila;
	for (int i=VOL; i>0;i--){
		valor_pila = pila_desapilar(pila);	
	}
	valor_pila = pila_desapilar(pila);
	print_test("desapilo todo correctamente", *valor_pila == valor_random);
	
	//destruyo la pila
	pila_destruir(pila);
	print_test("la pila fue destruida",true);
	
	
}
void prueba_null(void){
	/* Hace una prueba apilando pocos elementos y entre ellos NULL*/
	
	//Creo una pila
	printf("**************INICIO DE LA PRUEBA NULL**************\n");
	pila_t* pila = pila_crear();
	
	//Apilo el primer elemento como NULL
	bool ok=true;
	ok = pila_apilar(pila,NULL);
	print_test("Apilado el NULL",ok);
	
	//Apilo 5 elementos de tipo entero
	int v[NUM];
    for(int i=0; i<NUM; i++){
        v[i]=i;
        ok &= pila_apilar(pila, &v[i]);
    }
    print_test("Guardó los NUM valores", ok);
	
	//Desapilo los 5 elementos anteriores
	int* valor_actual;
	for(int i=NUM; i>=0; i--){
		valor_actual=pila_desapilar(pila);
	}
	valor_actual=pila_desapilar(pila);
	print_test("El elemento actual es NULL", valor_actual==NULL);
	
	//La pila esta vacía
	print_test("La pila quedo vacía", pila_esta_vacia(pila));
	
	
	// Destruyo la pila.
	pila_destruir(pila);
    print_test("la pila fue destruida", true);
}

void prueba_algunos_elementos(void){
    /*Hace una prueba con NUM elementos desapilandolos de a uno*/
	
	// Ejemplo de crear una pila vacia.
	printf("**************INICIO DE LA PRUEBA UNO**************\n");
	pila_t* pila = pila_crear();
	print_test("Creo una pila vacia", pila != NULL);
    
    //Apilo NUM elementos
    bool ok=true;
    int v[NUM];
    for(int i=0; i<NUM; i++){
        v[i]=i;
        ok &= pila_apilar(pila, &v[i]);
    }
    print_test("Guardó los NUM valores", ok);
    
   //Desapilo el ultimo elemento
    ok= pila_desapilar(pila);
    print_test("Desapilo el ultimo elemento", ok);
    
    //Me fijo el tope
    int* tope;
    tope = pila_ver_tope(pila);
    print_test("Desapilo correctamente el ultimo elemento", *tope == NUM-2);
    
    //Vuelvo a desapilar
    ok= pila_desapilar(pila);
    print_test("Desapilo el penultimo elemento", ok);
    
    //Me fijo el tope
    int* tope2;
    tope2 = pila_ver_tope(pila);
    print_test("Desapilo correctamente el penultimo elemento", *tope2 == NUM-3);
    
	// Destruyo la pila.
	pila_destruir(pila);
    print_test("la pila fue destruida", true);

}

void prueba_pila_vacia(void){
	printf("**************INICIO DE LA PRUEBA VACIA**************\n");
	pila_t* pila = pila_crear();
	bool ok = false;
	ok = pila_esta_vacia(pila);
	print_test("pila esta vacia", ok);
	
	//Intento desapilar algo de la pila vacia
	void* valor = pila_desapilar(pila);
	print_test("el valor desapilado es null", valor == NULL);
	
	//Destruyo la pila
	pila_destruir(pila);
	print_test("la pila fue destruida",true);
	
}

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
	prueba_null();
	prueba_algunos_elementos();
	prueba_pila_vacia();
	prueba_volumen_elementos();
	prueba_apilar_diferentes();
	prueba_memoria_dinamica();
}

