#include "strutil.h"
#include <stdlib.h>
#include <stdio.h>
#define SEP ','
#define SEP2 '|'

int main(void){
	char* joined;
	char *cadena = ",mati,scakosky,fiuba,racing,,,avellaneda,,";
	char **splited;
	fprintf(stdout,"%s\n",cadena);
	splited = split(cadena,SEP);
	int i = 0;
	while (splited[i] != NULL){
		fprintf(stdout,"%s\n",splited[i]);
		i++;
	}
	//Con cadena vacia en char* cadena y la siguiente linea se prueba hacer join de 0
	//splited[0]=NULL;
	joined = join(splited, SEP2);
	if(joined){
		fprintf(stdout,"%s\n",joined);
		free(joined);
		free_strv(splited);
	}
	return 0;
}




