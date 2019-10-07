#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

// Los structs deben llamarse "abb" y "abb_iter".
struct abb;
struct abb_iter;

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;
typedef struct abb_iter_post abb_iter_post_t;
typedef struct abb_item abb_item_t;

struct abb_item
{
	const char* clave;
    void* valor;
};


// tipo de función para comparar claves
typedef int (*abb_comparar_clave_t) (const char *, const char *);

// tipo de función para destruir dato
typedef void (*abb_destruir_dato_t)(void *);

/* Crea el abb */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura abb fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool abb_guardar(abb_t *abb, const char *clave, void *dato);

/* Borra un elemento del abb y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura abb fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *abb_borrar(abb_t *abb, const char *clave);

/* Obtiene el valor del un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura abb fue inicializada
 */
void *abb_obtener(const abb_t *abb, const char *clave);

/* Determina si clave pertenece o no al abb.
 * Pre: La estructura abb fue inicializada
 */

bool abb_pertenece(const abb_t *abb, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: La estructura abb fue inicializada
 */
size_t abb_cantidad(const abb_t *abb);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura abb fue inicializada
 * Post: La estructura abb fue destruida
 */

// Obtiene los items del abb;
abb_item_t* abb_obtener_items(const abb_t* abb);

void abb_destruir(abb_t *abb);

/* Iterador del abb externo in order*/

// Crea iterador
abb_iter_t *abb_iter_in_crear(const abb_t *abb);

// Avanza iterador
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Comprueba si terminó la iteración
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye iterador
void abb_iter_in_destruir(abb_iter_t* iter);

/* Iterador del abb interno in order*/ 

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);


/* Iterador del abb externo post order*/

/* Iterador del abb interno post order*/
void abb_post_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* Iterador del abb externo post order*/
// Crear el iterador
abb_iter_post_t*  abb_iter_post_crear(const abb_t* arbol);

// Avanza el iterador
bool  abb_iter_post_avanzar(abb_iter_post_t* iter);

// Devuelve la clave actual, esa clave no se puede modificar
const char*  abb_iter_post_ver_actual(const abb_iter_post_t* iter);

// Comprueba si terminó la iteracion
bool  abb_iter_post_al_final(const abb_iter_post_t* iter);

//Destruye el iterador
void  abb_iter_post_destruir(abb_iter_post_t* iter);

#endif // abb_H


