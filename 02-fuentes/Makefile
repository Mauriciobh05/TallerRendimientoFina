##########################################################################################
# Fecha: 2/11/2025
# Autor: Mauricio Beltrán Huertas
# Archivo: Makefile
# Descripción:
#     Archivo de automatización para la compilación de los programas de
#     multiplicación de matrices paralelas. Facilita la compilación de las versiones
#     que utilizan diferentes modelos de paralelismo: OpenMP, Pthreads (POSIX) y Fork.
#
#     Permite compilar todos los programas con una sola orden "make all"
#     aplicando las banderas necesarias según el modelo de ejecución.
#     Además, incluye una regla `clean` para eliminar los ejecutables generados.
##########################################################################################

CC = /opt/homebrew/opt/gcc/bin/gcc-15

# Banderas comunes
CFLAGS = -Wall -lm

# Banderas OpenMP para COMPILACIÓN 
FOPENMP_COMPILE = -fopenmp

# Banderas especificas para OpenMP 
FOPENMP_LINK = -fopenmp -O3

# Banderas POSIX
POSIX = -lpthread

# Lista de programas a compilar 
PROGRAMAS = mmClasicaFork mmClasicaPosix mmClasicaOpenMP mmFilasOpenMP

all: $(PROGRAMAS)

# Fork: Compila con -fopenmp 
mmClasicaFork: mmClasicaFork.c Funciones.c Funciones.h
	$(CC) mmClasicaFork.c Funciones.c -o $@ $(CFLAGS) $(FOPENMP_COMPILE)

# POSIX: Compila con -fopenmp 
mmClasicaPosix: mmClasicaPosix.c Funciones.c Funciones.h
	$(CC) mmClasicaPosix.c Funciones.c -o $@ $(CFLAGS) $(POSIX) $(FOPENMP_COMPILE)

# OpenMP: Compila y enlaza con -fopenmp
mmClasicaOpenMP: mmClasicaOpenMP.c Funciones.c Funciones.h
	$(CC) mmClasicaOpenMP.c Funciones.c -o $@ $(CFLAGS) $(FOPENMP_LINK)

# OpenMP Filas: Compila y enlaza con -fopenmp
mmFilasOpenMP: mmFilasOpenMP.c Funciones.c Funciones.h
	$(CC) mmFilasOpenMP.c Funciones.c -o $@ $(CFLAGS) $(FOPENMP_LINK)

clean:
	rm -f $(PROGRAMAS) *.dat