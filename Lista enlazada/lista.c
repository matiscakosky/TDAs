#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/*Definiciones de los struct lista y nodo_lista y el iterador*/

typedef struct nodo_lista{
	void* dato;
	struct nodo_lista* prox; 
} nodo_lista_t;

struct lista{
	nodo_lista_t* prim;
	nodo_lista_t* ult;
	size_t largo;
};

struct lista_iter{
	nodo_lista_t* actual;
	nodo_lista_t* anterior;
	lista_t* lista;
};


nodo_lista_t* crear_nodo(void* valor);
void comenzar_lista(lista_t* lista, nodo_lista_t* nodo);

/*Implementacion de las primitivas de la lista*/

lista_t *lista_crear(void){
	lista_t* lista_nueva = malloc(sizeof(lista_t));
	if (lista_nueva == NULL) return NULL;
	lista_nueva->prim = NULL;
	lista_nueva->ult = NULL;
	lista_nueva->largo= 0;
	return lista_nueva;

}

void comenzar_lista(lista_t* lista, nodo_lista_t* nodo){
		lista->prim = nodo;
		lista->ult = nodo;
		lista->largo++;
}

nodo_lista_t* crear_nodo(void* valor){
	nodo_lista_t* nuevo_nodo = malloc(sizeof(nodo_lista_t));
	if (nuevo_nodo == NULL) return NULL;
	nuevo_nodo->dato = valor;
	nuevo_nodo->prox = NULL;
	return nuevo_nodo;
}

bool lista_esta_vacia(const lista_t *lista){
	return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_lista_t* nodo = crear_nodo(dato);
	if(nodo==NULL)return false;
	if(lista_esta_vacia(lista)){
		comenzar_lista(lista, nodo);
		return true;	
	}
	nodo->prox = lista->prim;
	lista->prim = nodo;
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_lista_t* nodo = crear_nodo(dato);
	if(nodo==NULL)return false;
	if(lista_esta_vacia(lista)){
		comenzar_lista(lista, nodo);
		return true;	
	}
	lista->ult->prox = nodo;
	lista->ult= nodo;
	lista->largo++;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	void* dato = lista_ver_primero(lista);
	nodo_lista_t* aux = lista->prim;
	if(aux->prox == NULL){
		lista->prim = NULL;
		lista->ult = NULL;
		lista->largo = 0;
		free(aux);
		return dato;
	}
	lista->prim = lista->prim->prox;
	lista->largo--;
	free(aux);
	return dato;
	
}

void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	while(!lista_esta_vacia(lista)){
		if(destruir_dato != NULL){
			destruir_dato(lista->prim->dato);
		}
		lista_borrar_primero(lista);
	}
	free(lista);

}

/*Implementacion de las primitivas del iterador externo de la lista*/

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t *iterador = malloc(sizeof(lista_iter_t));
	if (iterador == NULL) return NULL;
	iterador->actual = lista->prim;
	iterador->anterior = NULL;
	iterador->lista = lista;
	return iterador;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->actual == NULL;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return false;
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (lista_iter_al_final(iter)) return NULL;
	return iter->actual->dato;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if (lista_esta_vacia(iter->lista)){
		lista_insertar_primero(iter->lista,dato);
		iter->actual = iter->lista->prim;
		iter->anterior = NULL;
		return true;
	}
	if(iter->lista->prim == iter->actual){
		iter->anterior = NULL;
	}
	if (iter->anterior == NULL){
		lista_insertar_primero(iter->lista, dato);
		iter->actual = iter->lista->prim;
		return true;
	}
	if (lista_iter_al_final(iter)){
		lista_insertar_ultimo(iter->lista,dato);
		iter->actual = iter->lista->ult;
		return true;
	}
	nodo_lista_t* nodo = crear_nodo(dato);
	nodo->prox = iter->actual;
	iter->anterior->prox = nodo;
	iter->actual = nodo;
	iter->lista->largo++;
	return true;
	
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_esta_vacia(iter->lista)) return NULL;
	if(lista_iter_al_final(iter)) return NULL;
	void* dato = iter->actual->dato;
	if(iter->anterior == NULL){
		lista_borrar_primero(iter->lista);
		iter->actual = iter->lista->prim;
		return dato;
	}
	nodo_lista_t* aux = iter->actual;
	if(iter->lista->largo == 2 && iter->actual->prox == NULL){
		iter->actual = NULL;
		iter->lista->ult = iter->anterior;
		iter->anterior->prox = NULL;
		iter->lista->largo--;
		free(aux);
		return dato;
	}
	iter->anterior->prox = iter->actual->prox;
	iter->actual = iter->actual->prox;
	free(aux);
	iter->lista->largo--;
	return dato;
}


/*Implementacion de las primitivas del iterador interno*/

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	nodo_lista_t* nodo = lista->prim;
	while(nodo!= NULL && visitar(nodo->dato, extra)){
		nodo = nodo->prox;	
	}
}



































































