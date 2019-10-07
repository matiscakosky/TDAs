#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

bool imprimr(const char* clave, void* valor, void* extra);
bool suma_elementos(const char* clave, void* n1, void* extra);


static void prueba_abb_obtener_items(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL ABB OBTENER ITEMS*****************************************************\n");
	
    abb_t* abb = abb_crear(strcmp,NULL);
	char *claveA = "A", *valorA = "1";
    char *claveB = "B", *valorB = "2";
    char *claveC = "C", *valorC = "3";
    char *claveD = "D", *valorD = "4";
    char *claveE = "E", *valorE = "5";
    char *claveF = "F", *valorF = "6";
    char *claveG = "G", *valorG = "7";
    char *claveH = "H", *valorH = "8";
    char *claveI = "I", *valorI = "9";
	
	print_test("Prueba abb insertar clave F", abb_guardar(abb, claveF, valorF));
	print_test("Prueba abb insertar clave B", abb_guardar(abb, claveB, valorB));
	print_test("Prueba abb insertar clave G", abb_guardar(abb, claveG, valorG));
	print_test("Prueba abb insertar clave A", abb_guardar(abb, claveA, valorA));
	print_test("Prueba abb insertar clave D", abb_guardar(abb, claveD, valorD));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, claveC, valorC));
	print_test("Prueba abb insertar clave E", abb_guardar(abb, claveE, valorE));
	print_test("Prueba abb insertar clave I", abb_guardar(abb, claveI, valorI));
	print_test("Prueba abb insertar clave H", abb_guardar(abb, claveH, valorH));
	abb_item_t* items = abb_obtener_items(abb);
	
	print_test("Prueba abb obtener items[0] es A", items[0].valor == valorA);
	print_test("Prueba abb obtener items[1] es B", items[1].valor == valorB);
	print_test("Prueba abb obtener items[2] es C", items[2].valor == valorC);
	print_test("Prueba abb obtener items[3] es D", items[3].valor == valorD);
	print_test("Prueba abb obtener items[4] es E", items[4].valor == valorE);
	print_test("Prueba abb obtener items[5] es F", items[5].valor == valorF);
	print_test("Prueba abb obtener items[6] es G", items[6].valor == valorG);
	print_test("Prueba abb obtener items[7] es H", items[7].valor == valorH);
	print_test("Prueba abb obtener items[8] es I", items[8].valor == valorI);
	free(items);
	abb_destruir(abb);
	
}

bool suma_elementos(const char* clave, void* n1, void* extra){
	int* suma = extra;
	*suma += *(int*)n1;
	return true;
	
}
static void prueba_abb_iterador_post_interno(){
	printf("*****************************************************INICIO DE LA SEGUNDA PRUEBA DEL ITERADOR POST ORDEN INTTERNO*****************************************************\n");
	abb_t* abb = abb_crear(strcmp,NULL);
	char *clave17 = "17"; int valor17 = 17;
	char *clave15 = "15"; int valor15 = 15;
	char *clave22 = "22"; int valor22 = 22;
	char *clave19 = "19"; int valor19 = 19;
	char *clave25 = "25"; int valor25 = 25;
	char *clave11 = "11"; int valor11 = 11;
	char *clave16 = "16"; int valor16 = 16;
	char *clave13 = "13"; int valor13 = 13;
	int suma = 0;
	print_test("Prueba abb insertar clave 17", abb_guardar(abb, clave17, &valor17));
	print_test("Prueba abb insertar clave 15", abb_guardar(abb, clave15, &valor15));
	print_test("Prueba abb insertar clave 22", abb_guardar(abb, clave22, &valor22));
	print_test("Prueba abb insertar clave 19", abb_guardar(abb, clave19, &valor19));
	print_test("Prueba abb insertar clave 25", abb_guardar(abb, clave25, &valor25));
	print_test("Prueba abb insertar clave 11", abb_guardar(abb, clave11, &valor11));
	print_test("Prueba abb insertar clave 16", abb_guardar(abb, clave16, &valor16));
	print_test("Prueba abb insertar clave 13", abb_guardar(abb, clave13, &valor13));
	
	abb_post_order(abb,suma_elementos,&suma);
	printf("La suma total fue de:%d\n",suma);
	abb_destruir(abb);

}

static void prueba_abb_iterador_post2(){
	printf("*****************************************************INICIO DE LA SEGUNDA PRUEBA DEL ITERADOR POST ORDEN EXTERNO*****************************************************\n");
	abb_t* abb = abb_crear(strcmp,NULL);
	char *clave17 = "17"; int valor17 = 17;
	char *clave15 = "15"; int valor15 = 15;
	char *clave22 = "22"; int valor22 = 22;
	char *clave19 = "19"; int valor19 = 19;
	char *clave25 = "25"; int valor25 = 25;
	char *clave11 = "11"; int valor11 = 11;
	char *clave16 = "16"; int valor16 = 16;
	char *clave13 = "13"; int valor13 = 13;
	int suma = 0;
	
	print_test("Prueba abb insertar clave 17", abb_guardar(abb, clave17, &valor17));
	print_test("Prueba abb insertar clave 15", abb_guardar(abb, clave15, &valor15));
	print_test("Prueba abb insertar clave 22", abb_guardar(abb, clave22, &valor22));
	print_test("Prueba abb insertar clave 19", abb_guardar(abb, clave19, &valor19));
	print_test("Prueba abb insertar clave 25", abb_guardar(abb, clave25, &valor25));
	print_test("Prueba abb insertar clave 11", abb_guardar(abb, clave11, &valor11));
	print_test("Prueba abb insertar clave 16", abb_guardar(abb, clave16, &valor16));
	print_test("Prueba abb insertar clave 13", abb_guardar(abb, clave13, &valor13));
	abb_iter_post_t* iter = abb_iter_post_crear(abb);
	print_test("Prueba crear iterador externo post order abb", iter);
	
	printf("El orden de recorrido es 13 11 16 15 19 25 22 17. La suma deberia ir siguiendo ese patrón hasta llegar a %d\n",valor13+valor11+valor16+valor15+valor19+valor25+valor22+valor17);
	
	const char* clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13", suma == valor13);
	abb_iter_post_avanzar(iter);
	
	clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13+11", suma == valor13+valor11);
	abb_iter_post_avanzar(iter);
	
	clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13+11+16", suma == valor13+valor11+valor16);
	abb_iter_post_avanzar(iter);
	
	clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13+11+16+15", suma == valor13+valor11+valor16+valor15);
	abb_iter_post_avanzar(iter);
	
	clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13+11+16+15+19", suma == valor13+valor11+valor16+valor15+valor19);
	abb_iter_post_avanzar(iter);
	
	clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13+11+16+15+19+25", suma == valor13+valor11+valor16+valor15+valor19+valor25);
	abb_iter_post_avanzar(iter);
	
	clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13+11+16+15+19+25+22", suma == valor13+valor11+valor16+valor15+valor19+valor25+valor22);
	abb_iter_post_avanzar(iter);
		
	clave = abb_iter_post_ver_actual(iter);
	suma += *(int*)(abb_obtener(abb,clave));
	print_test("'suma' es 13+11+16+15+19+25+22+17", suma == valor13+valor11+valor16+valor15+valor19+valor25+valor22+valor17);
	
	printf("La suma total fue de:%d\n",suma);
	abb_iter_post_destruir(iter);
	abb_destruir(abb);
}

static void prueba_abb_iterador_post(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL ITERADOR POST ORDEN EXTERNO*****************************************************\n");
	
    abb_t* abb = abb_crear(strcmp,NULL);
	char *claveA = "A", *valorA = "1";
    char *claveB = "B", *valorB = "2";
    char *claveC = "C", *valorC = "3";
    char *claveD = "D", *valorD = "4";
    char *claveE = "E", *valorE = "5";
    char *claveF = "F", *valorF = "6";
    char *claveG = "G", *valorG = "7";
    char *claveH = "H", *valorH = "8";
    char *claveI = "I", *valorI = "9";
	
	print_test("Prueba abb insertar clave F", abb_guardar(abb, claveF, valorF));
	print_test("Prueba abb insertar clave B", abb_guardar(abb, claveB, valorB));
	print_test("Prueba abb insertar clave G", abb_guardar(abb, claveG, valorG));
	print_test("Prueba abb insertar clave A", abb_guardar(abb, claveA, valorA));
	print_test("Prueba abb insertar clave D", abb_guardar(abb, claveD, valorD));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, claveC, valorC));
	print_test("Prueba abb insertar clave E", abb_guardar(abb, claveE, valorE));
	print_test("Prueba abb insertar clave I", abb_guardar(abb, claveI, valorI));
	print_test("Prueba abb insertar clave H", abb_guardar(abb, claveH, valorH));
	
	print_test("La cantidad de elementos es 9", abb_cantidad(abb) == 9);
	abb_iter_post_t* iter = abb_iter_post_crear(abb);
	print_test("Prueba crear iterador externo post order abb", iter);
	print_test("Prueba iterador abb es A", *(abb_iter_post_ver_actual(iter)) == *claveA);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es C", *(abb_iter_post_ver_actual(iter)) == *claveC);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es E", *(abb_iter_post_ver_actual(iter)) == *claveE);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es D", *(abb_iter_post_ver_actual(iter)) == *claveD);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es B", *(abb_iter_post_ver_actual(iter)) == *claveB);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es H", *(abb_iter_post_ver_actual(iter)) == *claveH);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es I", *(abb_iter_post_ver_actual(iter)) == *claveI);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es G", *(abb_iter_post_ver_actual(iter)) == *claveG);
	abb_iter_post_avanzar(iter);
	
	print_test("Prueba iterador abb es F", *(abb_iter_post_ver_actual(iter)) == *claveF);

	
	
	abb_iter_post_destruir(iter);
	abb_destruir(abb);
}



static void ejemplo_corrector3(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL CORRECTOR 3 *****************************************************\n");
	
	/*Valor incorrecto devuelto por borrar("4") tras la secuencia de borrado: 1 3 2 4 <=== habiendo insertado: 1 3 2 4 5 6 7  */ 
	abb_t* abb = abb_crear(strcmp,NULL);
	char* a1="1", *valor1 = "GATO";
	char* a2="2",  *valor2 = "PERRO";
	char* a3="3",*valor3 = "VACA";
	char* a4="4",*valor4 = "OSO";
	char* a5="5",*valor5 = "DELFIN";
	char* a6="6",*valor6 = "LEON";
	char* a7="7",*valor7 = "TIGRE";
	
	print_test("Prueba abb insertar clave 2", abb_guardar(abb, a1, valor1));
	print_test("Prueba abb insertar clave 1", abb_guardar(abb, a3, valor3));
	print_test("Prueba abb insertar clave 3", abb_guardar(abb, a2, valor2));
	print_test("Prueba abb insertar clave 3", abb_guardar(abb, a4, valor4));
	print_test("Prueba abb insertar clave 3", abb_guardar(abb, a5, valor5));
	print_test("Prueba abb insertar clave 3", abb_guardar(abb, a6, valor6));
	print_test("Prueba abb insertar clave 3", abb_guardar(abb, a7, valor7));

	print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, a1) == valor1);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a3) == valor3);
	print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, a2) == valor2);
	print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, a4) == valor4);

	
	abb_destruir(abb);
}


static void ejemplo_corrector2(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL CORRECTOR 2 *****************************************************\n");
	
	/*Valor incorrecto devuelto por borrar("3") tras la secuencia de borrado: 2 1 3 <=== habiendo insertado: 2 1 3 */ 
	abb_t* abb = abb_crear(strcmp,NULL);
	char* a1="1", *valor1 = "GATO";
	char* a2="2",  *valor2 = "PERRO";
	char* a3="3",*valor3 = "VACA";
	
	print_test("Prueba abb insertar clave 2", abb_guardar(abb, a2, valor2));
	print_test("Prueba abb insertar clave 1", abb_guardar(abb, a1, valor1));
	print_test("Prueba abb insertar clave 3", abb_guardar(abb, a3, valor3));

	print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, a2) == valor2);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a1) == valor1);
	print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, a3) == valor3);

	
	abb_destruir(abb);
}

static void ejemplo_corrector(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL CORRECTOR*****************************************************\n");
	
	/*Valor incorrecto devuelto por borrar("3") tras la secuencia de borrado: 4 2 1 3 <=== habiendo insertado: 7 6 5 4 2 1 3*/ 
	abb_t* abb = abb_crear(strcmp,NULL);
	char* a1="1", *valor1 = "1";
	char* a2="2",  *valor2 = "2";
	char* a3="3",*valor3 = "3";
	char* a4="4", *valor4 = "4";
	char* a5="5", *valor5 = "5";
	char* a6="6", *valor6 = "6";
	char* a7="7", *valor7 = "7";
	
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a7, valor7));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a6, valor6));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a5, valor5));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a4, valor4));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a2, valor2));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a1, valor1));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a3, valor3));
	
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a3) == valor3);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a2) == valor2);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a1) == valor1);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a6) == valor6);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a5) == valor5);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a4) == valor4);
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a7) == valor7);
	
	abb_destruir(abb);
}

static void	prueba_inducida_martin_b(){
	printf("*****************************************************INICIO DE LA PRUEBA INDUCIDA POR MARTIN BUCHWALD*****************************************************\n");
	
	abb_t* abb = abb_crear(strcmp,NULL);
	char* a1="00000006", *valor1 = "1";
	char* a2="00000000",  *valor2 = "2";
	char* a3="00000009",*valor3 = "3";
	char* a4="00000004", *valor4 = "4";
	char* a5="00000010", *valor5 = "5";
	char* a6="00000013", *valor6 = "6";
	char* a7="00000008", *valor7 = "7";
	char* a8="00000003", *valor8 = "8";
	char* a9="00000014", *valor9 = "9";
	char* a10="00000001", *valor10 = "10";
	char* a11="00000002", *valor11 = "11";
	char* a12="00000007", *valor12 = "12";
	char* a13="00000005", *valor13 = "13";
	char* a14="00000011", *valor14 = "14";
	char* a15="00000012", *valor15 = "15";
	
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a1, valor1));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a2, valor2));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a3, valor3));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a4, valor4));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a5, valor5));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a6, valor6));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a7, valor7));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a8, valor8));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a9, valor9));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a10, valor10));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a11, valor11));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a12, valor12));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a13, valor13));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a14, valor14));
	print_test("Prueba abb insertar clave C", abb_guardar(abb, a15, valor15));
	
	
	print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 15);
	
	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, a1) == valor1);
	print_test("Prueba abb borrar clave10, es valor10", abb_borrar(abb, a10) == valor10);
	print_test("Prueba abb borrar clave7, es valor7", abb_borrar(abb, a7) == valor7);
	print_test("Prueba abb borrar clave13, es valor13", abb_borrar(abb, a13) == valor13);
	
	abb_destruir(abb);


}

static void prueba_abb_fallo(){
	printf("*****************************************************INICIO DE LA PRUEBA DE ARBOL QUE FALLA*****************************************************\n");
	
	//inserto el abecedario en el abb.
    abb_t* abb = abb_crear(strcmp,NULL);
	char *claveA = "A", *valorA = "1";
    char *claveB = "B", *valorB = "2";
    char *claveC = "C", *valorC = "3";
    char *claveD = "D", *valorD = "4";
	
	/*Los meto de forma tal que no quede lineal*/
	print_test("Prueba abb insertar clave C", abb_guardar(abb, claveC, valorC));
	print_test("Prueba abb insertar clave D", abb_guardar(abb, claveD, valorD));
	print_test("Prueba abb insertar clave B", abb_guardar(abb, claveB, valorB));
	print_test("Prueba abb insertar clave A", abb_guardar(abb, claveA, valorA));
	
	print_test("Prueba abb la cantidad de elementos es 4", abb_cantidad(abb) == 4);
		
	print_test("Prueba abb borrar claveB, es valorB", abb_borrar(abb, claveC) == valorC);
	print_test("Prueba abb borrar claveC, es valorC", abb_borrar(abb, claveA) == valorA);
	print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 2);
	
	/*destruyo el resto del arbol con los elementos que quedan*/
	abb_destruir(abb);
		
}


void swap (unsigned int* x,unsigned int* y) {
	unsigned int aux = *x;
	*x = *y;
	*y = aux;
}

static void prueba_abb_claves_desordenadas(int cant){
	
	printf("*****************************************************INICIO DE LA PRUEBA DE VOLUMEN RANDOM SIN COLISIONES*****************************************************\n");
	
	
	abb_t* abb = abb_crear(strcmp,NULL);
	char clave[10];
	unsigned int claves[cant];
	unsigned int valores[cant];
	unsigned int j = 0;
	bool ok = true;
	for(int i = 0; i<cant;i++){
		claves[i] = i;
		valores[i] = i;
	}
	for(int i = 0; i<cant;i++){
		j = rand()%(cant);
		swap(&claves[i],&claves[j]);
		swap(&valores[i],&valores[j]);
	}
	for(int i = 0; i<cant; i++){
		sprintf(clave,"%08ui",claves[i]);
		ok &= abb_guardar(abb,clave,&valores[i]);
	}
	
	print_test("Almaceno todos los elementos",ok);
	char *clave1= "1", *valor1 = "1";
	char *clave2= "2", *valor2 = "2";
	char *clave3= "3", *valor3 = "3";
	char *clave4= "4", *valor4 = "4";
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave1,valor1));
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave2,valor2));
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave3,valor3));
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave4,valor4));
	print_test("prueba abb pertenece", abb_pertenece(abb,clave3));
	print_test("prueba abb pertenece", abb_pertenece(abb,clave2));
	print_test("prueba abb pertenece", abb_pertenece(abb,clave1));
	print_test("prueba abb borrar", abb_borrar(abb,clave1) == valor1);
	print_test("prueba abb borrar", abb_borrar(abb,clave2) == valor2);
	print_test("prueba abb borrar", abb_borrar(abb,clave4) == valor4);
	print_test("prueba abb borrar", abb_borrar(abb,clave3) == valor3);

	abb_destruir(abb);

}

static void prueba_abb_volumen_desordenado(int cant){
	printf("*****************************************************INICIO DE LA PRUEBA DE VOLUMEN RANDOM CON COLISIONES*****************************************************\n");
	
	abb_t* abb = abb_crear(strcmp,NULL);
	int tam = 10;
	unsigned int valores[cant];
	char clave[tam];
	unsigned int j = 0;
	bool ok = true;
	srand((unsigned int)time(NULL));
	for (int i = 0; i<cant;i++){
		//Estas valores van a colisionar entre si, debe reemplazarlos
		j = rand()%(cant+1);
		valores[j]=j;
		sprintf(clave,"%08ui",j);
		ok &= abb_guardar(abb,clave,&valores[j]);
	}
	
	print_test("Almaceno todos los elementos",ok);
	char *clave1= "1", *valor1 = "1";
	char *clave2= "2", *valor2 = "2";
	char *clave3= "3", *valor3 = "3";
	char *clave4= "4", *valor4 = "4";
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave1,valor1));
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave2,valor2));
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave3,valor3));
	print_test("prueba abb guardar clave1", abb_guardar(abb,clave4,valor4));
	print_test("prueba abb pertenece", abb_pertenece(abb,clave3));
	print_test("prueba abb pertenece", abb_pertenece(abb,clave2));
	print_test("prueba abb pertenece", abb_pertenece(abb,clave1));
	print_test("prueba abb borrar", abb_borrar(abb,clave1) == valor1);
	print_test("prueba abb borrar", abb_borrar(abb,clave2) == valor2);
	print_test("prueba abb borrar", abb_borrar(abb,clave4) == valor4);
	print_test("prueba abb borrar", abb_borrar(abb,clave3) == valor3);

	abb_destruir(abb);
		
}

bool imprimr(const char* clave, void* valor, void* extra){
	printf("%s %s\n", clave, (char*) valor);
	return true;
}

static void prueba_abb_iterar_interno(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL ITERADOR INTERNO*****************************************************\n");
	
	abb_t* abb = abb_crear(strcmp,NULL);
	char *claveA = "A", *valorA = "1";
    char *claveB = "B", *valorB = "2";
    char *claveC = "C", *valorC = "3";
    char *claveD = "D", *valorD = "4";
    char *claveE = "E", *valorE = "5";
    char *claveF = "F", *valorF = "6";
    char *claveG = "G", *valorG = "7";
    char *claveH = "H", *valorH = "8";
	
	/*Los meto de forma tal que no quede lineal*/
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveD, valorD));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveF, valorF));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveC, valorC));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveE, valorE));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveA, valorA));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveG, valorG));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveH, valorH));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveB, valorB));
	
	abb_in_order(abb,imprimr,NULL);
	abb_destruir(abb);
}

static void prueba_abb_iterar(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL ITERADOR EXTERNO*****************************************************\n");
	
    abb_t* abb = abb_crear(strcmp,NULL);
	char *claveA = "A", *valorA = "1";
    char *claveB = "B", *valorB = "2";
    char *claveC = "C", *valorC = "3";
    char *claveD = "D", *valorD = "4";
    char *claveE = "E", *valorE = "5";
    char *claveF = "F", *valorF = "6";
    char *claveG = "G", *valorG = "7";
    char *claveH = "H", *valorH = "8";
	
	/*Los meto de forma tal que no quede lineal*/
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveD, valorD));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveF, valorF));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveC, valorC));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveE, valorE));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveA, valorA));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveG, valorG));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveH, valorH));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveB, valorB));
	
	abb_iter_t* iter = abb_iter_in_crear(abb);
	const char* clave;
    print_test("El iterador se creo correctamente y no esta al final", !abb_iter_in_al_final(iter));

    /* Valor de la clave A tiene que ser 1 */
    clave = abb_iter_in_ver_actual(iter);
	print_test("La clave que me devolvio el iterador es la correcta", abb_obtener(abb,clave) == valorA);
    print_test("Avanza el iterador", abb_iter_in_avanzar(iter));
    print_test("Iterador no esta al final", !abb_iter_in_al_final(iter));
	
	/* Valor de la clave B tiene que ser 2 */
    clave = abb_iter_in_ver_actual(iter);
	print_test("La clave que me devolvio el iterador es la correcta", abb_obtener(abb,clave) == valorB);
    print_test("Avanza el iterador", abb_iter_in_avanzar(iter));
    print_test("Iterador no esta al final", !abb_iter_in_al_final(iter));
	
	/* Valor de la clave C tiene que ser 3 */
    clave = abb_iter_in_ver_actual(iter);
	print_test("La clave que me devolvio el iterador es la correcta", abb_obtener(abb,clave) == valorC);
    print_test("Avanza el iterador", abb_iter_in_avanzar(iter));
    print_test("Iterador no esta al final", !abb_iter_in_al_final(iter));
	
	abb_iter_in_destruir(iter);
	abb_destruir(abb);
	
}
static void prueba_abb_vacio()
{
    abb_t* abb = abb_crear(strcmp,NULL);
	printf("*****************************************************INICIO DE LA PRUEBA ABB VACIO*****************************************************\n");
	
    print_test("El abb fue creado", abb);
    print_test("La cantidad de el,elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb pertenece clave cualquiera", !abb_pertenece(abb, "cualquiera"));
    print_test("Prueba abb borrar clave cualquiera, no pudo", !abb_borrar(abb, "cualquiera"));
    abb_destruir(abb);
}
static void prueba_abb_clave_vacia(){
	 abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = NULL, *valor = NULL;
	printf("*****************************************************INICIO DE LA PRUEBA CLAVE NULL VALOR NULL*****************************************************\n");
	
    print_test("Insertar la clave vacia",!abb_guardar(abb, clave, valor));
    print_test("El valor de la clave vacia es NULL", abb_obtener(abb, clave) == valor);
	print_test("Cantidad de elementos del abb es 1",! (abb_cantidad(abb) == 1));
    print_test("Borrar la clave vacia es NULL", abb_borrar(abb, clave) == valor);
    print_test("No quedan elementos", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}
static void prueba_abb_insertar_abc(){
	printf("*****************************************************INICIO DE LA PRUEBA DEL ABECEDARIO*****************************************************\n");
	
	//inserto el abecedario en el abb.
    abb_t* abb = abb_crear(strcmp,NULL);
	char *claveA = "A", *valorA = "1";
    char *claveB = "B", *valorB = "2";
    char *claveC = "C", *valorC = "3";
    char *claveD = "D", *valorD = "4";
    char *claveE = "E", *valorE = "5";
    char *claveF = "F", *valorF = "6";
    char *claveG = "G", *valorG = "7";
    char *claveH = "H", *valorH = "8";
	
	/*Los meto de forma tal que no quede lineal*/
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveD, valorD));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveF, valorF));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveC, valorC));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveE, valorE));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveA, valorA));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveG, valorG));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveH, valorH));
	print_test("Prueba abb insertar clave", abb_guardar(abb, claveB, valorB));
	
	print_test("Prueba abb la cantidad de elementos es 8", abb_cantidad(abb) == 8);
	
	print_test("Prueba abb pertenece claveA", abb_pertenece(abb, claveA));
	print_test("Prueba abb pertenece claveD", abb_pertenece(abb, claveD));
	print_test("Prueba abb pertenece claveE", abb_pertenece(abb, claveE));
	print_test("Prueba abb pertenece claveH", abb_pertenece(abb, claveH));
	
	print_test("Prueba abb borrar claveB, es valorB", abb_borrar(abb, claveB) == valorB);
	print_test("Prueba abb borrar claveC, es valorC", abb_borrar(abb, claveC) == valorC);
	print_test("Prueba abb borrar claveG, es valorG", abb_borrar(abb, claveG) == valorG);
	print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
	
	/*destruyo el resto del arbol con los elementos que quedan*/
	abb_destruir(abb);
		
}
void pruebas_abb_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
	prueba_abb_vacio();
	prueba_abb_clave_vacia();
	prueba_abb_insertar_abc();
	prueba_abb_iterar();
	prueba_abb_iterar_interno();
	prueba_abb_fallo();
	prueba_inducida_martin_b();
	ejemplo_corrector2();
	ejemplo_corrector();
	ejemplo_corrector3();
	prueba_abb_iterador_post();
	prueba_abb_iterador_post2();
	prueba_abb_iterador_post_interno();
	prueba_abb_obtener_items();
	prueba_abb_claves_desordenadas(4000);
	prueba_abb_volumen_desordenado(4000);

}