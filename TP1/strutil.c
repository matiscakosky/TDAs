#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAD_VACIA ""

char** split(const char* str, char sep){
	if (!str) return NULL;
	int len =(int) strlen(str);
	int cantsep = 0;
	int possep = 0;
	for (int i = 0; i<len; i++){
		if (str[i] == sep){
			cantsep++;
		}
	}
	char **strv = malloc(sizeof(char*) * (cantsep+2));
	if (len == 0) strv[0]=CAD_VACIA;
	int str_p = 0;
	for (int j = 0; j<len+1; j++){
		if(str[j] == sep || str[j] == '\0' || str[j] == '\n'){
			if (j == len-1) strv[str_p] = CAD_VACIA;
			if (j-possep == 0) strv[str_p] = CAD_VACIA;
			char* cadena = calloc(1 ,sizeof(char) * ((j-possep) + 1));
			if (cadena == NULL) return NULL;
			strncpy(cadena,str+possep,j-possep);
			strv[str_p] = cadena;
			possep = j+1;
			str_p++;	
		}
	}
	strv[cantsep+1] = NULL;
	return strv;
	
}

char* join(char** strv, char sep){
	size_t len = 0;
	int i=0, letra=0, pos=0;
	if (!strv) return NULL;
	while (strv[i] != NULL){
		len += strlen(strv[i]);
		i++;
	}
	len += i;
	char* cadena = calloc(1, sizeof(char)*len+1);
	if (!cadena) return NULL;
	if (len==0){
		cadena[0]= '\0';
		return cadena;
	}
	i =0;
	while (strv[i] != NULL){
		while(strv[i][letra] != '\0'){
			cadena[pos] = strv[i][letra];
			pos++;
			letra++;
		}
		cadena[pos] = sep;
		letra = 0;
		i++;
		pos++;
	}
	cadena[len-1] = '\0';
	return cadena;
	
}


void free_strv(char *strv[]){
	int i = 0;
	while (strv[i] != NULL){
		free(strv[i]);
		i++;
	}
	free(strv);

}
