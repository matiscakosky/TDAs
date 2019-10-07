#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

/* Definiciones de los struct cola y nodo_cola */

typedef struct nodo_cola{
	void* dato;
	struct nodo_cola* prox; 
} nodo_cola_t;

struct cola{
	nodo_cola_t* prim;
	nodo_cola_t* ult;
};

nodo_cola_t* crear_nodo(void* valor);

/*Implementacion de las primitivas*/

cola_t* cola_crear(void) {
	cola_t* cola_nueva = malloc(sizeof(cola_t));
	if (cola_nueva == NULL) return NULL;
	cola_nueva->prim = NULL;
	cola_nueva->ult = NULL;
	return cola_nueva;
}


void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	while(!cola_esta_vacia(cola)){
		if(destruir_dato != NULL){
			destruir_dato(cola->prim->dato);
		}
		cola_desencolar(cola);
	}
	free(cola);
}

void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola)) return NULL;
	int* valor = cola_ver_primero(cola);
	nodo_cola_t* aux = cola->prim;
	if (!aux->prox){
		cola->prim = NULL;
		cola->ult = NULL;
	}
	else cola->prim = aux->prox;
	free(aux);
	return valor;
}

nodo_cola_t* crear_nodo(void* valor){
	nodo_cola_t* nuevo_nodo = malloc(sizeof(nodo_cola_t));
	if (nuevo_nodo == NULL) return NULL;
	nuevo_nodo->dato = valor;
	nuevo_nodo->prox = NULL;
	return nuevo_nodo;
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_cola_t* nodo_n = crear_nodo(valor);
	if (!nodo_n) return false;
	if(cola_esta_vacia(cola)){
		cola->prim = nodo_n;
		cola->ult = nodo_n;
		return true;
	}
	cola->ult->prox = nodo_n;
	cola->ult = nodo_n;
	return true;
}

void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)) return NULL;
	return cola->prim->dato;
}


bool cola_esta_vacia(const cola_t *cola){
	if(!cola->prim) return true;
	return false;
}





