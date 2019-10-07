#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


	
/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.	
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlistados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);


// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);


// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

//Obtiene el largo de la lista
//Pre: la lista fue creada
//Post: Se devolvio el largo de la lista
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador de tipo lista_t
// Post: devuelve un iterador de lista comenzando a iterar desde el primer elemento de la lista
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza sobre el iterador, si no puede devuelve false
// Pre: el iterador fue creado
// Post: Avanza sobre la lista una posicion
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve un elemento con el valor de la posicion actual de la lista
// Pre: el iterador y la lista fueron creadas
// Post: se devolvio el dato sobre el elemento actual de la lista
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve si el iterador esta al final, si no esta devuelve false
// Pre: El iterador fue creado
// Post: Se devolvio si el iterador llego al final de la lista
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador
// Pre: el iterador fue creado
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en la lista, si no puede devuelve false
// Pre: La lista y el iterador fueron creados
// Post: se inserto en la posicion del iterador el nuevo dato
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Elimina un elemento de la lista y devuelve el valor eliminado, si la lista esta vacia devuelve NULL
// Pre: La lista y el iterador fueron creados
// Post: se elimino de la posicion del iterador el dato
void *lista_iter_borrar(lista_iter_t *iter);

/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera una lista
// La función de callback "visitar" recibe el dato y un puntero extra, y devuelve true si se debe seguir iterando, false en caso contrario
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);



























