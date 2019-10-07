#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define TAM_I 13
#define FAC_CARGA 2
#define FAC_DESCARGA 0.7
#define REDIM_FACTOR 2

/*Definiciones de los struct hash y el iterador de hash*/

typedef struct par_hash{
	const char* clave;
	void* valor;
}par_hash_t;

struct hash{
	lista_t** lista;
	hash_destruir_dato_t destructor;
	size_t tam;
	size_t cant;
};

struct hash_iter{
	const hash_t* hash;
	lista_iter_t* lista_iter;
	size_t pos;
};


lista_iter_t* buscar_clave(const hash_t* hash,const char* clave);
size_t hashing(const char* clave, size_t tam);
par_hash_t* par_crear(const char *clave, void *dato);
const char* copia_clave(const char *clave);
void rehash(hash_t* hash, size_t tam_nuevo);
bool prox_pos_valida(hash_iter_t *iter);




/*Funcion hashing sacada de Wikipedia*/
size_t hashing(const char *source, size_t tam){
	  	size_t length = strlen(source);
		size_t hash = 0;
		for(size_t i = 0; i < length; i++) {
			char c = source[i];
			int a = c - '0';
			hash = (hash * 10) + a;     
		} 

		return hash % tam;
} 

void rehash(hash_t* hash, size_t tam_nuevo){
	lista_t** tabla = malloc(tam_nuevo * sizeof(lista_t**));
	for (int j=0; j < tam_nuevo; j++){
		tabla[j] = lista_crear();
	}
	for(int i=0; i < hash->tam; i++){
		lista_t* lista = hash->lista[i];
		while(!lista_esta_vacia(lista)){
			par_hash_t* par = lista_borrar_primero(lista);
			size_t pos = hashing(par->clave, tam_nuevo);
			lista_insertar_ultimo(tabla[pos],par); 
		}
		lista_destruir(lista, NULL);
	}
	lista_t** aux = hash->lista;
	free(aux);
	hash->tam = tam_nuevo;
	hash->lista = tabla;
	
}


hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	if (hash == NULL) return NULL;
	hash->tam = TAM_I;
	hash->cant = 0;
	hash->destructor = destruir_dato;
	hash->lista = malloc(TAM_I* sizeof(lista_t**));
	if (hash->lista == NULL){
		free(hash);
		return NULL;
	}
	for (int i =0; i < TAM_I; i++){
		hash->lista[i] = lista_crear();
	}
	return hash;

}



par_hash_t* par_crear(const char *clave, void *dato){
	par_hash_t* par = malloc(sizeof(par_hash_t));
	if (par==NULL) return NULL;
	par->clave = copia_clave(clave);
	par->valor = dato;
	return par;
}

lista_iter_t* buscar_clave(const hash_t* hash,const char* clave){
	int comparacion;
	size_t pos = hashing(clave, hash->tam);
	lista_t* lista = hash->lista[pos];
	lista_iter_t* iter = lista_iter_crear(lista);
	while(!lista_iter_al_final(iter)){
		par_hash_t* par = lista_iter_ver_actual(iter);
		comparacion = strcmp(clave, par->clave);
		if (comparacion==0) return iter;
		lista_iter_avanzar(iter);
	}
	free(iter);
	return NULL;
}


void *hash_obtener(const hash_t *hash, const char *clave){
	lista_iter_t* iter = buscar_clave(hash,clave);
	if(iter == NULL) return NULL;
	par_hash_t* par = lista_iter_ver_actual(iter);
	lista_iter_destruir(iter);
	return par->valor;

}

size_t hash_cantidad(const hash_t *hash){
	return hash->cant;

}

void hash_destruir(hash_t *hash){
	for (int i =0; i < hash->tam; i++){
		lista_iter_t* iter = lista_iter_crear(hash->lista[i]);
		while(!lista_iter_al_final(iter)){
			par_hash_t* par = lista_iter_borrar(iter);
			if(hash->destructor != NULL){
				hash->destructor(par->valor);
			}
			free((char*)par->clave);
			free(par);
		}
		lista_destruir(hash->lista[i], hash->destructor);
		lista_iter_destruir(iter);
	}
	free(hash->lista);	
	free(hash);
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	lista_iter_t* iter = buscar_clave(hash,clave);
	if(iter != NULL){
		lista_iter_destruir(iter);
		return true;
	}
	lista_iter_destruir(iter);
	return false;
}

const char* copia_clave(const char *clave){
	size_t len = strlen(clave);
	const char* copia = malloc((len+1)*sizeof(char));
	strcpy((char*)copia,clave);
	return copia;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	lista_iter_t* iter = buscar_clave(hash,clave);
	if(iter == NULL){
		if((hash->cant)/(hash->tam) >= FAC_CARGA){
			rehash(hash,hash->tam * REDIM_FACTOR);
		}
		size_t pos = hashing(clave, hash->tam);
		par_hash_t* par = par_crear(clave, dato);
		if (par == NULL) return false; 
		lista_insertar_ultimo(hash->lista[pos],par); 
		hash->cant++;
		lista_iter_destruir(iter);
		return true;
	}
	par_hash_t* par = lista_iter_ver_actual(iter);
	
	if (hash->destructor != NULL){
		hash->destructor(par->valor);
	}
	
	par->valor = dato;
	lista_iter_destruir(iter);
	return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
	lista_iter_t* iter = buscar_clave(hash,clave);
	if(iter == NULL) return NULL;
	par_hash_t* par = lista_iter_borrar(iter);
	void* returnvalue = par->valor;
	free((char*)par->clave);
	free(par);
	hash->cant--;
	lista_iter_destruir(iter);
	if (hash->tam >= TAM_I && (hash->cant)/(hash->tam) <= FAC_DESCARGA){
		rehash(hash,hash->tam / REDIM_FACTOR);
	}
	return returnvalue;
}



/*********************************************Primitivas del iterador**********************************************/


hash_iter_t *hash_iter_crear(const hash_t *hash){	
	hash_iter_t* iter = malloc (sizeof(hash_iter_t));
	if (iter == NULL) return NULL;
	iter->hash = hash;
	iter->lista_iter = NULL;
	for (int i=0; i < hash->tam; i++){
		if (!lista_esta_vacia(hash->lista[i])){
			iter->lista_iter = lista_iter_crear(hash->lista[i]);
			iter->pos = i;
			break;
		}
	}
	return iter;

}

	
bool hash_iter_avanzar(hash_iter_t *iter){
	// Pregunto si estoy en el ultimo nodo de la ultima posicion valida del hash
	if (hash_iter_al_final(iter)) return false;
	
	if (!lista_iter_al_final(iter->lista_iter)){
		lista_iter_avanzar(iter->lista_iter);
		if (!lista_iter_al_final(iter->lista_iter) || hash_iter_al_final(iter)) return true;
	}
	for (size_t i = iter->pos+1; i < iter->hash->tam; i++){
		if (!lista_esta_vacia(iter->hash->lista[i])){
			lista_iter_destruir(iter->lista_iter); 
			iter->lista_iter = lista_iter_crear(iter->hash->lista[i]);
			iter->pos = i;
			break;			
			}
		}
	return true;
}


const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if (hash_iter_al_final(iter)) return NULL;
	par_hash_t* par = lista_iter_ver_actual(iter->lista_iter);
	return par->clave;
}


bool hash_iter_al_final(const hash_iter_t *iter){
	if (iter->lista_iter == NULL) return true;
	if (lista_iter_al_final(iter->lista_iter)){
		size_t pos = iter->pos+1;
		while (pos < iter->hash->tam){
			if (!lista_esta_vacia(iter->hash->lista[pos])){
				return false;
			}
			pos++;
		}
		return true;
	}
	//Si no esta al final de nada devuelvo false
	return false;
}


void hash_iter_destruir(hash_iter_t* iter){
	if (iter->lista_iter != NULL){
		lista_iter_destruir(iter->lista_iter);
	}
	free(iter);
}















