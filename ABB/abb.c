#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct abb_nodo abb_nodo_t;

struct abb_nodo{
	const char* clave;
	void* valor;
	abb_nodo_t* izq;
	abb_nodo_t* der;
};

struct abb{
	size_t cant;
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destructor;
};

struct abb_iter{
	const abb_t* abb;
	pila_t* pila;
};

const char* copia_clave(const char *clave);
abb_nodo_t* recorrer_arbol(const abb_t *abb,abb_nodo_t* nodo, const char *clave);
void destruir_arbol_datos(abb_t *abb, abb_nodo_t* nodo);
bool es_hoja(abb_nodo_t* nodo);
abb_nodo_t* crear_nodo (const char* clave, void* dato);
bool abb_guardar_nuevo(abb_t* abb, abb_nodo_t* padre, abb_nodo_t* nodo);
abb_nodo_t* abb_borrar_nodo(abb_t* abb,abb_nodo_t* nodo ,abb_nodo_t* padre, const char *clave);
void swap_nodos(abb_nodo_t* nodo_b,abb_nodo_t* nodo_s);
void borrar_izqoder(abb_t* abb, abb_nodo_t* nodo, abb_nodo_t* padre, const char *clave);
abb_nodo_t* maximo_subizq(abb_nodo_t* nodo,bool primera);
void abb_iterar(abb_nodo_t* nodo,bool visitar(const char *, void *, void *),void* extra);

const char* copia_clave(const char *clave){
	size_t len = strlen(clave);
	const char* copia = malloc((len+1)*sizeof(char));
	strcpy((char*)copia,clave);
	return copia;
}

bool abb_guardar(abb_t *abb, const char *clave, void *dato){
	if (!clave) return false;
	abb_nodo_t* nodo_nuevo = crear_nodo(clave,dato);
	if(nodo_nuevo == NULL) return false;	
	if(!abb->raiz){
		abb->raiz = nodo_nuevo;
		abb->cant++;
		return true;
	} 
	if(abb_guardar_nuevo(abb, abb->raiz, nodo_nuevo)){
		abb->cant++;
	}
	return true;
}


bool abb_guardar_nuevo(abb_t* abb, abb_nodo_t* padre, abb_nodo_t* nodo){
	if (es_hoja(padre)){
		int comparacion = abb->cmp(padre->clave,nodo->clave);
		if(comparacion > 0){ 				//padre mayor al hijo
			padre->izq = nodo;
		}
		else if(comparacion < 0){ 			//padre menor al hijo	
			padre->der = nodo;
		}
		else{								//padre igual al hijo
			if (abb->destructor != NULL){
				abb->destructor(padre->valor);
			}
			padre->valor=nodo->valor;
			free((char*)nodo->clave); 					
			free(nodo); 					//Lo libero ya que no lo voy a usar
			return false;
		}
		return true;
	}
	
	if (!padre->der || !padre->izq){
		int comparacion = abb->cmp(padre->clave,nodo->clave);
		if (comparacion > 0){
			if(!padre->izq){
				padre->izq = nodo;
			}
			else{
				return abb_guardar_nuevo(abb,padre->izq,nodo);
			}
		}
		else if(comparacion < 0){
			if(!padre->der){
				padre->der = nodo;
			}
			else{
				return abb_guardar_nuevo(abb,padre->der,nodo);
			}
		}
		else{
			if (abb->destructor != NULL){
				abb->destructor(padre->valor);
			}
			padre->valor=nodo->valor;
			free((char*)nodo->clave); 	
			free(nodo); 
			return false;
		}
		return true;
	}
	int comparacion = abb->cmp(padre->clave,nodo->clave);
	if (comparacion > 0){
		return abb_guardar_nuevo(abb,padre->izq,nodo);
	}
	else if(comparacion < 0){
		return abb_guardar_nuevo(abb,padre->der,nodo);
	}
	else{
		if (abb->destructor){
			abb->destructor(padre->valor);
		}
		padre->valor=nodo->valor;
		free((char*)nodo->clave); 	
		free(nodo); 
		return false;
	}
	return true;
}

void *abb_borrar(abb_t *abb, const char *clave){
	if(!abb->raiz) return NULL;
	abb_nodo_t* nodo = abb_borrar_nodo(abb,abb->raiz,NULL,clave);
	if(!nodo) return NULL;
	if (abb->destructor){
		abb->destructor(nodo->valor);
	}
	void* dato = nodo->valor;
	free((char*)nodo->clave);
	free(nodo);
	abb->cant--;
	return dato;
}
/*Lo que hace swap nodos no es actualizar el arbol sino que cambia unicamente las calves del nodo a borrar por las del nodo_s y 
sus respectivos valores*/
void swap_nodos(abb_nodo_t* nodo_b,abb_nodo_t* nodo_s){
	const char* clave = nodo_b->clave;
	void* valor = nodo_b->valor;
	nodo_b->clave = nodo_s->clave;
	nodo_b->valor = nodo_s->valor;
	nodo_s->clave = clave;
	nodo_s->valor = valor;
}

abb_nodo_t* maximo_subizq(abb_nodo_t* nodo,bool primera){
	abb_nodo_t* aux = nodo;
	if(nodo->izq){
		aux = nodo->izq;
		while (aux->der){
			aux=aux->der;
		}
	}
	return aux;

}

/*Esta funcion cortocircuita los nodos cuando hay que borrar un nodo con un solo hijo*/
void borrar_izqoder(abb_t* abb,abb_nodo_t* nodo, abb_nodo_t* padre, const char *clave){
	if(nodo){
		if(!padre){
			abb->raiz = nodo;
			return;
		}
		int nueva = abb->cmp(padre->clave,nodo->clave);
		if (nueva < 0){
			padre->der = nodo;
		}
		else{
			padre->izq = nodo;
		}
	}
}

abb_nodo_t* abb_borrar_nodo(abb_t* abb, abb_nodo_t* nodo, abb_nodo_t* padre, const char *clave){
	if(!nodo) return NULL;
	int comparacion = abb->cmp(nodo->clave,clave);
	if (!comparacion){
		if(es_hoja(nodo)){
			if(!padre){
				abb->raiz = NULL;
		  		return nodo;
			}
			//Codigo de coty
			if(padre->izq == nodo){
				padre->izq = NULL;
				return nodo;
			}
			padre->der = NULL;
			return nodo;
		}
		if(!nodo->izq || !nodo->der){
			if(nodo->izq){
				borrar_izqoder(abb,nodo->izq,padre,clave);
			}
			
			if(nodo->der){
				borrar_izqoder(abb,nodo->der,padre,clave);
			}
			return nodo;
		}
		
		if(nodo->izq && nodo->der){
			abb_nodo_t* nodo_s = maximo_subizq(nodo,true);
			swap_nodos(nodo, nodo_s);
			return abb_borrar_nodo(abb,nodo->izq,nodo,clave);
		}
	}
	
	if (comparacion > 0){
		return abb_borrar_nodo(abb,nodo->izq,nodo,clave);
	}
	else{
		return abb_borrar_nodo(abb,nodo->der,nodo,clave);
	}
}


abb_nodo_t* crear_nodo (const char* clave, void* dato){
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if (nodo == NULL) return NULL;
	nodo->clave = copia_clave(clave);
	nodo->valor = dato;
	nodo->izq = NULL;
	nodo->der = NULL;
	return nodo;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;
	abb->cant = 0;
	abb->cmp = cmp;
	abb->destructor = destruir_dato;
	abb->raiz = NULL;
	return abb;
}

abb_nodo_t* recorrer_arbol(const abb_t *abb,abb_nodo_t* nodo, const char *clave){
	if(!nodo) return NULL;
	int comparacion = abb->cmp(nodo->clave,clave);
	if (!comparacion) return nodo;
	if (comparacion > 0){
		return recorrer_arbol(abb, nodo->izq, clave);
	}
	else{
		return recorrer_arbol(abb, nodo->der, clave);
	}
	return nodo;
}

bool abb_pertenece(const abb_t *abb, const char *clave){
	abb_nodo_t* nodo = recorrer_arbol(abb,abb->raiz,clave);
	if(nodo)return true;
	return false;
}

void *abb_obtener(const abb_t *abb, const char *clave){
	abb_nodo_t* nodo = recorrer_arbol(abb,abb->raiz,clave);
	if(nodo)return nodo->valor;
	return NULL;
}

bool es_hoja(abb_nodo_t* nodo){
   return !nodo->der && !nodo->izq;
}

size_t abb_cantidad(abb_t *abb){
	return abb->cant;
}


void destruir_arbol_datos(abb_t *abb, abb_nodo_t* nodo){
	if(!nodo) return;
	if (nodo->izq){
		destruir_arbol_datos(abb,nodo->izq);
	}
	if (nodo->der){
		destruir_arbol_datos(abb,nodo->der);
	}
	if(abb->destructor){
		abb->destructor(nodo->valor);
	}
	free((char*)nodo->clave);
	free(nodo);
	return;
}
void abb_destruir(abb_t *abb){
	destruir_arbol_datos(abb, abb->raiz);
	free(abb);
	return;
}

/*************************************** Iterador externo ABB ***************************************/


abb_iter_t *abb_iter_in_crear(const abb_t *abb){
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if (!iter) return NULL;
	pila_t* pila = pila_crear();
	if(!pila) return NULL;
	iter->pila = pila;
	iter->abb = abb;
	if(!abb->raiz) return iter;
	abb_nodo_t* aux = abb->raiz;
	pila_apilar(pila,aux);
	while(aux->izq){
		pila_apilar(pila,aux->izq);
		aux = aux->izq;
	}
	return iter;
}


bool abb_iter_in_avanzar(abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)) return false;
	abb_nodo_t* nodo = pila_desapilar(iter->pila);
	if(nodo->der){
		pila_apilar(iter->pila,nodo->der);
		abb_nodo_t* aux = nodo->der;
		while(aux->izq){
			pila_apilar(iter->pila,aux->izq);
			aux = aux->izq;
		}
	}
	return true;	
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)) return NULL;
	abb_nodo_t* nodo = pila_ver_tope(iter->pila);
	return nodo->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return (pila_esta_vacia(iter->pila));
}

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);
}


/*************************************** Iterador interno ABB ***************************************/


void abb_in_order(abb_t *abb, bool visitar(const char *, void *, void *), void *extra){
	abb_iterar(abb->raiz,visitar,extra);
}

void abb_iterar(abb_nodo_t* nodo,bool visitar(const char *, void *, void *),void* extra){
	if (!nodo) return;
	abb_iterar(nodo->izq,visitar,extra);
	if(!visitar(nodo->clave,nodo->valor,extra))return;
	abb_iterar(nodo->der,visitar,extra);
	
}








