# Constantes globales para la compilacion
CC = gcc
OBJ1 = pila.o dc.o strutil.o
OBJ2 = paste.o
OBJ3 = more.o
OBJ4 = strutil.o
CFLAGS = -g -std=c99 -Wall -pedantic -Wconversion -Wno-sign-conversion -Werror

#Instruccion que se va a ejecutar por defalut
all: paste more 
#El default que se compila tiene dependencia a los objetos OBJ
#El comando compila los OBJ con CC y CFLAGS resultando el EXEC

dc: pila.o strutil.o dc.o 
	$(CC) $(CFLAGS) $(OBJ1) -o dc
	
paste: paste.o
	$(CC) $(CFLAGS) $(OBJ2) -o paste

more: more.o
	$(CC) $(CFLAGS) $(OBJ3) -o more
	
	
#Todos los objetos definidos en "OBJ=" con dependencia a los archivos .c y .h van a compilarse de la misma manera
%.o: %.c %.h 
	$(CC) $(CFLAGS) -c $<