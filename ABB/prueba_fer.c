
#include <time.h>
static void prueba_abb_fer(int largo){
	abb_t* abb = abb_crear(strcmp,NULL);
	int largo_clave = 10;
	unsigned int valores[largo];
	char clave[largo_clave];
	unsigned int j = 0;
	bool ok = true;
	//char clavePro[largo_clave];
	srand((unsigned int)time(NULL));
	for (int i = 0; i<largo;i++){
		j = rand()%(largo+1);
		valores[j]=j;
		sprintf(clave,"%08ui",j);
		if (j == largo-2){
			printf("%s\n",clave);
		}
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
