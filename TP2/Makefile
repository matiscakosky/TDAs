# Constantes globales para la compilacion
CC = gcc
OBJ1 = hash.o uniq-count.o strutil.o lista.o pila.o cola.o
OBJ4 = hash.o comm.o strutil.o lista.o pila.o cola.o
OBJ2 = abb.o pila.o main_abb.o pruebas_alumno_abb.o testing.o
OBJ3 = heap.o testing.o vector_dinamico.o heap-utils.o main_heap.o pruebas_alumno_heap.o
CFLAGS = -g -std=c99 -Wall -pedantic -Wconversion -Wno-sign-conversion -Werror -Wshadow

#Instruccion que se va a ejecutar por defalut
all: uniq-count comm abb heap heap-utils

#El default que se compila tiene dependencia a los objetos OBJ
#El comando compila los OBJ con CC y CFLAGS resultando el EXEC

comm: $(OBJ4)
	$(CC) $(CFLAGS) $(OBJ4) -o comm

uniq-count: $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o uniq-count
	
abb: $(OBJ2)
	$(CC) $(CFLAGS) $(OBJ2) -o abb

heap: $(OBJ3)
	$(CC) $(CFLAGS) $(OBJ3) -o heap

heap-utils: $(OBJ3)
	$(CC) $(CFLAGS) $(OBJ3) -o heap-utils


	
	
#Todos los objetos definidos en "OBJ=" con dependencia a los archivos .c y .h van a compilarse de la misma manera
%.o: %.c %.h 
	$(CC) $(CFLAGS) -c $<
		
#Borra todos los archivos
clean:
	rm $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) uniq-count comm abb heap heap-utils
#Make compila unicamente los elementos que se hayan modificado recientemente
	