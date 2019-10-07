#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#define TAM_INICIAL 8
#define FACTOR 2
#define FACTOR_COMP 4

/* Definición del struct pila proporcionado por la cátedra.
 */

struct pila {
    void** datos;
    size_t cantidad;   //Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

pila_t* pila_crear(void){
	pila_t* pila_nueva = malloc(sizeof(pila_t));
	if (pila_nueva==NULL){
		return NULL;
	}
	pila_nueva->cantidad = 0; 					             
	pila_nueva->datos=malloc(TAM_INICIAL * sizeof(void*));
	if (pila_nueva->datos == NULL){
		free(pila_nueva);
		return NULL;
	}
	pila_nueva->capacidad = TAM_INICIAL; 				
	return pila_nueva;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_redimensionar(pila_t *pila,size_t tam){
    void **aux = realloc (pila->datos, sizeof(void*) * tam);
    if (aux == NULL) return false;
    pila->datos = aux;
    pila->capacidad = tam;
    return true;
}

bool pila_esta_vacia(const pila_t *pila){
	return (pila->cantidad ==0);
}


bool pila_apilar(pila_t *pila, void* valor){
	if (pila->cantidad == pila->capacidad){
        if(!pila_redimensionar(pila, ((pila->capacidad)*FACTOR))){
            return false;
        }
    }
	pila->datos[pila->cantidad] = valor;
	pila->cantidad += 1 ;
	return true;
}

void* pila_ver_tope(const pila_t *pila){
    if(!pila_esta_vacia(pila)){
	    return pila->datos[pila->cantidad-1];
    }
    return NULL;
}


void* pila_desapilar(pila_t *pila){
    if(pila_esta_vacia(pila)) return NULL;
	void* tope = pila_ver_tope(pila);
	pila->cantidad -=1;
	if(pila->cantidad == pila->capacidad/FACTOR_COMP && pila->capacidad > TAM_INICIAL){
        if(!pila_redimensionar(pila, ((pila->capacidad)/FACTOR))){
		    return NULL;
        }    
	}
    return tope;
		
}
