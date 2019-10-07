#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "abb_funciones.h"

typedef struct abb_nodo abb_nodo_t;

struct abb{
	size_t cant;
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destructor;
};

struct abb_nodo{
	const char* clave;
	void* valor;
	abb_nodo_t* izq;
	abb_nodo_t* der;
};

struct abb_iter_post{
	const abb_t* abb;
	pila_t* pila;
};
void abb_iterar(abb_nodo_t* nodo,bool visitar(const char *, void *, void *),void* extra);

/* *************************************************************************
*					ABB POST ORDER ITERADOR INTERNO						   *		
*																		   *
************************************************************************** */


void abb_post_order(abb_t* abb, bool (*visitar)(const char*, void*, void*), void* extra){
	abb_iterar(abb->raiz,visitar,extra);
}

void abb_iterar(abb_nodo_t* nodo,bool visitar(const char *, void *, void *),void* extra){
	if (!nodo) return;
	abb_iterar(nodo->izq,visitar,extra);
	abb_iterar(nodo->der,visitar,extra);
	if(!visitar(nodo->clave,nodo->valor,extra))return;
}


/* *************************************************************************
*					ABB POST ORDER ITERADOR EXTERNO						   *		
*																		   *
************************************************************************** */

