#include <stdio.h>
#include <string.h>
#define TAM 8
#define HASHTAM 4



size_t hashing(const char *clave, size_t stringsize);

/*Funcion hashing sacada de Wikipedia*/
size_t hashing(const char *clave, size_t tam){
	
       int hashval, j;
	   size_t len = strlen(clave);
       hashval = (int) clave[0];
       for (j = 1; j < len; j++) 
	   hashval += (int) clave[j];
       return(hashval % tam);
 } 

int main(void){



	const char* k = "vaca";
	size_t pos = hashing(k,HASHTAM);
		printf("vaca es %zu\n", pos);
	
	const char* k1 = "gato";
	size_t pos1 = hashing(k1,HASHTAM);
		printf("gato es %zu\n", pos1);
	
	const char* k2 = "perro";
	size_t pos2 = hashing(k2,HASHTAM);
		printf("perro es %zu\n", pos2);
	
	const char* k3 = "00000004";
	size_t pos3 = hashing(k3, HASHTAM);
		printf("00000004 es %zu\n", pos3);
	




	return 0;
}