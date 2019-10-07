#include "pila.h"
#include "strutil.h"
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define SUMA '+'
#define RESTA '-'
#define MULTI '*'
#define DIVISION '/'
#define FREE_N free(n1); free(n2);
#define FREE_PILA_STRV pila_destruir(pila); free_strv(arreglo);

void destruir_datos_pila(pila_t* pila);


void destruir_datos_pila(pila_t* pila){
	while(!pila_esta_vacia(pila)){
		double* dato = pila_desapilar(pila);
		free(dato);
	}
	return;
}


int main(void){
	char* l = NULL; 
	pila_t* pila = pila_crear();
	size_t cap;
	getline(&l,&cap,stdin);
	printf("%s",l);
	int i = 0;
	char** arreglo = split(l,' ');
	while(arreglo[i] != NULL){
		double* subarreglo = malloc(sizeof(double));
		*subarreglo = atof(arreglo[i]);
		if (*subarreglo != 0 || arreglo[i][0] == '0'){
			pila_apilar(pila,subarreglo);
			i++;
			continue;
		}
		free(subarreglo); 
		
		if(strlen(arreglo[i]) != 1){
			fprintf(stderr,"Por favor, ingresar una operacion valida, el programa de detendrá\n");
			destruir_datos_pila(pila);
			FREE_PILA_STRV;
			return -1;
		}
		double* n2 = pila_desapilar(pila);
		double* n1 = pila_desapilar(pila);
		
		if( n1 == NULL || n2 ==NULL){
			fprintf(stderr,"La operacion no es válida\n");
			FREE_N;
			destruir_datos_pila(pila);
			FREE_PILA_STRV;
			return -1;
		}
		
		double* nres = malloc(sizeof(double));
		switch(arreglo[i][0]){
			case SUMA:
				*nres = *n1+*n2;
				FREE_N;
				pila_apilar(pila,nres);
				break;
			case RESTA:
				*nres = *n1-(*n2);
				FREE_N;
				pila_apilar(pila,nres);
				break;
			case MULTI:
				*nres = (*n1)*(*n2);
				FREE_N;
				pila_apilar(pila,nres);
				break;
			case DIVISION:
				*nres = *n1/(*n2);
				FREE_N;
				pila_apilar(pila,nres);
				break;

			default:
				fprintf(stderr,"Por favor, ingresar una operacion valida, el programa de detendrá\n");
				return -1;
				destruir_datos_pila(pila);
				FREE_PILA_STRV;
		}
		i++;
	
	}
	
	double* resultado = pila_desapilar(pila);
	if(resultado == NULL || !pila_esta_vacia(pila)){
		fprintf(stderr,"Por favor, ingresar una cantidad correspondiente de numeros y operaciones\n");
		destruir_datos_pila(pila);
		free(resultado);
		FREE_PILA_STRV;
		return -1;
	}
	
	fprintf(stdout,"%f\n",*resultado);
	free(resultado);
	free(l);
	destruir_datos_pila(pila);
	FREE_PILA_STRV;
	return 0;
}