#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#define NUM 8
#define VOL 5000
#define TOPE 1500


void crear_lista_vacia(void);
void enlistar_algunos_elementos(void);
void enlistar_volumen_elementos(void);
void enlistar_vector_heap(void);
void prueba_iterador_externo(void);
void prueba_iter_casos_base(void);
void prueba_iter_interno(void);
bool sumar_elementos(void* dato, void* extra);
bool sumar_elementos_hasta_tope(void* dato, void* extra);


bool sumar_elementos_hasta_tope(void* dato, void* extra){
	int* numero = dato;
	int* final = extra;
	*final += *numero;
	if (*final > TOPE) return false;
	return true;


}
bool sumar_elementos(void* dato, void* extra){
	int* numero = dato;
	int* final = extra;
	*final += *numero;
	return true;
}

void prueba_iter_interno(void){
	printf("**************INICIO DE LA PRUEBA DEL ITERADOR INTERNO**************\n");
	int resul=0, resul2=0;
	
	//Creo una lista
	lista_t* lista = lista_crear();
	bool ok = false;
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia", ok);
	
	int vector[VOL];
	for (int i = 0; i<VOL; i++){
		vector[i] = i;
		ok = lista_insertar_ultimo(lista, &vector[i]);
	}
	print_test("la lista se lleno correctamente", ok);
	ok = lista_esta_vacia(lista);
	print_test("la lista no esta vacia", !ok);
	
	lista_iterar(lista, sumar_elementos, &resul);
	print_test("el resultado es mayor al volumen", resul > VOL );
	
	lista_iterar(lista, sumar_elementos_hasta_tope, &resul2);
	print_test("el resultado no llega al volumen", resul2 < VOL );
	lista_destruir(lista, NULL);
	
}

void prueba_iter_casos_base(void){
	printf("**************INICIO DE LA PRUEBA DEL ITERADOR EXTERNO CASOS BASE**************\n");
	int dato=1, dato2=2;
	int *obj;
	//Creo una lista
	lista_t* lista = lista_crear();
	bool ok = false;
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia", ok);
	
	//Creo un iterador de lista
	lista_iter_t* iter = lista_iter_crear(lista);
	ok = lista_iter_al_final(iter);
	print_test("el iterador esta al final", ok);
	
	ok = lista_iter_insertar(iter, &dato);
	print_test("el dato se inserto correctamente", ok);
	
	ok = lista_iter_insertar(iter, &dato2);
	print_test("el dato se inserto correctamente", ok);
	
	ok = lista_iter_al_final(iter);
	print_test("el iterador no esta al final", !ok);
	
	obj = lista_iter_ver_actual(iter);
	print_test("el primer elemento de la lista es correcto", *obj == dato2);
	
	lista_iter_borrar(iter);
	obj = lista_iter_ver_actual(iter);
	print_test("el segundo elemento de la lista es correcto", *obj == dato);
	
	lista_iter_borrar(iter);
	dato = (int)lista_largo(lista);
	print_test("largo correcto de la lista", 0 == dato);
	
	//Destruyo ambas struct
	lista_destruir(lista, NULL);
	lista_iter_destruir(iter);	
	
	
}



void prueba_iterador_externo(void){
	printf("**************INICIO DE LA PRUEBA DEL ITERADOR EXTERNO**************\n");
	
	//Creo una lista para iterarla y la lleno con NUM elementos
	lista_t* lista = lista_crear();
	int *obj, *obj2;
	bool ok = false;
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia", ok);
	
	int vector[NUM];
	for (int i = 0; i<NUM; i++){
		vector[i] = i;
		ok = lista_insertar_primero(lista, &vector[i]);
	}
	
	//Creo un iterador
	lista_iter_t* iter = lista_iter_crear(lista);
	ok = lista_iter_al_final(iter);
	print_test("el iterador no esta al final",!ok);
	
	//Comparo los primeros elementos de ambas struct
	obj = lista_iter_ver_actual(iter);
	obj2 = lista_ver_primero(lista);
	print_test("el primer elemento del iterador es igual al de la lista", *obj == *obj2);
	
	ok = lista_iter_avanzar(iter);
	lista_borrar_primero(lista);
	print_test("el iterador avanzo de forma correcta", ok);
	
	obj = lista_iter_ver_actual(iter);
	obj2 = lista_ver_primero(lista);
	print_test("el segundo elemento del iterador es igual al de la lista", *obj == *obj2);
	ok = lista_iter_al_final(iter);
	print_test("el iterador no esta al final",!ok);
	
	//Inserto un elemento al principio de la lista desde el iterador
	ok = lista_iter_insertar(iter, &vector[0]);
	print_test("el iterador agrego de forma correcta el elemento",ok);
	obj = lista_iter_ver_actual(iter);
	print_test("Comparo el valor  con el agregado",*obj == vector[0]);
	
	//Avanzo al final del iterador
	while(lista_iter_ver_actual(iter)){
		lista_iter_avanzar(iter);
	}
	print_test("el iterador esta al final", lista_iter_al_final(iter));
	
	//Inserto un elemento al final de la lista
	ok = lista_iter_insertar(iter, &vector[NUM-1]);
	obj = lista_iter_ver_actual(iter);
	print_test("el iterador agrego de forma correcta el elemento",ok);
	print_test("Comparo el valor agregado con el ultimo", *obj == vector[NUM-1]);
	lista_iter_destruir(iter);	
	
	//Creo un iterador
	lista_iter_t* iter2 = lista_iter_crear(lista);
	ok = lista_iter_al_final(iter2);
	print_test("el iterador no esta al final",!ok);
	
	obj = lista_iter_borrar(iter2);
	print_test("Comparo el valor con el borrado", *obj == vector[0]);
	lista_iter_avanzar(iter2);
	lista_iter_borrar(iter2);
	obj = lista_iter_ver_actual(iter2);
	print_test("Comparo el valor con el borrado", *obj == vector[4]);
	
	//Destruyo ambas struct
	lista_destruir(lista, NULL);
	lista_iter_destruir(iter2);	
	
	
}

void enlistar_vector_heap(void){
	printf("**************INICIO DE LA PRUEBA DEL HEAP**************\n");
	lista_t* lista = lista_crear();
	bool ok = false;
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia", ok);
	int* v = malloc(NUM * sizeof(int));
	int* obj;
	v[0]=NUM;
	v[1]=VOL;
	v[2]=VOL*NUM;
	v[3]=NUM-VOL;
	ok = lista_insertar_ultimo(lista,v);
	obj = lista_ver_primero(lista);
	print_test("el valor se corresponde con el del primero de la lista", obj[0]==v[0]);
	print_test("el valor se corresponde con el del primero de la lista", obj[1]==VOL);
	print_test("el valor se corresponde con el del primero de la lista", obj[2]==v[2]);
	print_test("el valor se corresponde con el del primero de la lista", obj[3]==NUM-VOL);
	obj = lista_borrar_primero(lista);
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia", ok);
	
	
	// Libero la memoria del vector
	free(v);
	//Destruyo la lista
	lista_destruir(lista, NULL);
	print_test("la lista fue destruida",true);
	

}


void enlistar_volumen_elementos(void){
	printf("**************INICIO DE LA PRUEBA VOLUMEN ELEMENTOS**************\n");
	lista_t* lista = lista_crear();
	bool ok = false;
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia", ok);
	int v[VOL];
	int *obj;
	char* car = "c";
	size_t size;
	for (int i = 0; i<VOL; i++){
		v[i] = i;
		ok = lista_insertar_primero(lista, &v[i]);
	}
	print_test("los elementos se enlistaron de forma correcta", ok);
	
	//Compruebo los elementos enlistados
	obj = lista_ver_primero(lista);
	size = lista_largo(lista);
	print_test("el tamaño de la lista es el correcto", size == VOL);
	print_test("el primer elemento de la lista es el correcto", *obj == VOL-1);
	obj = lista_ver_ultimo(lista);
	print_test("el ultimo elemento de la lista es el correcto", *obj == 0);
	
	//Inserto un elemento de otro tipo al final y el principio deberia mantenerse y cambiar el final
	ok = lista_insertar_ultimo(lista, car);
	obj = lista_ver_primero(lista);
	print_test("el primer elemento de la lista es el correcto", *obj == VOL-1);
	obj = lista_ver_ultimo(lista);
	//print_test("el ultimo elemento de la lista es el correcto", *obj == *car);  //*

	
	//Destruyo la lista
	lista_destruir(lista, NULL);
	print_test("la lista fue destruida",true);
	
	
}			

void enlistar_algunos_elementos(void){
	printf("**************INICIO DE LA PRUEBA ALGUNOS ELEMENTOS**************\n");
	lista_t* lista = lista_crear();
	bool ok= false;
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia",ok);
	
	int dato =5;
	int* obj, *obj2;
	
	//Enlisto al final y borro al principio
	ok = lista_insertar_ultimo(lista,&dato);
	print_test("el elemento fue insertado",ok);
	
	obj = lista_borrar_primero(lista);
	print_test("el obj es igual al enlistado", *obj == dato);
	
	//Inserto elementos al principio
	int vector[NUM];
	for (int i = 0; i<NUM; i++){
		vector[i] = i;
		ok = lista_insertar_primero(lista, &vector[i]);
	}
	obj = lista_ver_primero(lista);
	obj2 = lista_ver_ultimo(lista);
	print_test("El primero corresponde al ultimo insertado", *obj == NUM-1);
	print_test("El ultimo corresponde al primero insertado", *obj2 == 0);
	
	//Borro elementos
	for (int i = 0; i<NUM; i++){
		ok = lista_borrar_primero(lista);
	}
	print_test("lista se vacio ", lista_esta_vacia(lista));
	
	
	//Inserto elementos al final
	for (int i=0; i<NUM; i++){
		vector[i] = i;
		ok = lista_insertar_ultimo(lista, &vector[i]);
	}
	obj = lista_ver_primero(lista);
	obj2 = lista_ver_ultimo(lista);
	print_test("El primero corresponde al ultimo insertado", *obj == 0);
	print_test("El ultimo corresponde al ultimo insertado", *obj2 == NUM-1);
	
	
	
	//Destruyo la lista
	lista_destruir(lista, NULL);
	print_test("la lista fue destruida",true);

}
void crear_lista_vacia(void){
	printf("**************INICIO DE LA PRUEBA LISTA VACIA**************\n");
	lista_t* lista = lista_crear();
	bool ok= false;
	
	//Pregunto si la lista esta vacia
	ok = lista_esta_vacia(lista);
	print_test("la lista esta vacia",ok);
	
	//Destruyo la lista
	lista_destruir(lista, NULL);
	print_test("la lista fue destruida",true);
}


void pruebas_lista_alumno(){
	crear_lista_vacia();
	enlistar_algunos_elementos();
	enlistar_volumen_elementos();
	enlistar_vector_heap();
	prueba_iterador_externo();
	prueba_iter_casos_base();
	prueba_iter_interno();
	
}