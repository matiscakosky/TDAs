#include "tp0.h"
#include <stdio.h>
/* ******************************************************************
 *                     FUNCIONES A COMPLETAR						*
 * *****************************************************************/
 
 /* *****************************************************************
  *						ALUMNO: Matias Scakosky
  *						PADRON: 99627
  * *************************************************************** */	
  
int comparar_componentes(int vector1[], int vector2[], int n);

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
	int aux = *x;
	*x = *y;
	*y = aux;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
	if (n == 0){
		return -1;
	}
	int valmaximo = vector[0];
	int pos = 0;
	for(int i=0; i<n; i++){
		if(vector[i] > valmaximo){
			valmaximo = vector[i];
			pos = i;
		}
	}
	return pos;
	
}
	

int comparar_componentes(int vector1[], int vector2[], int n){
	for(int i=0; i<n; i++){
		if (vector1[i] < vector2[i]){
				return -1;
			}
		else if (vector1[i] > vector2[i]){
				return 1;
			}
	}
	return 0;
}
/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
	int comparacion;
	if (n1 == n2){
		comparacion = comparar_componentes(vector1, vector2, n1);
	}
	else if	(n1>n2){
		comparacion = comparar_componentes(vector1, vector2, n2);
		if (comparacion == 0){
			return 1;
		}
	}
	else if	(n1<n2){
		comparacion = comparar_componentes(vector1, vector2, n1);
		if (comparacion == 0){
			return -1;
		}
	}
	return comparacion;
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
	int largo = --n; 
	for(int i=0; i<n; i++){
		int posmaximo = maximo(vector, largo+1); //el largo+1 representa al vector entero sin las posiciones ya ordenadas
		swap(&vector[posmaximo], &vector[largo]);
		largo--;
	}





}
