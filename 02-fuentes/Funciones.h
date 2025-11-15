/*#######################################################################################
#* Archivo: funciones.h
#* Autor: Mauricio Beltrán Huertas
#* Descripción:
#*      Interfaz que declara todas las funciones y estructuras utilizadas en los
#*      programas de multiplicación de matrices paralelas (Fork, POSIX, OpenMP).
######################################################################################*/

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

//Estructura utilizada en el modelo POSIX 
struct parametros {
    int nH;
    int idH;
    int N;
};

//Variables globales 

extern double *matrixA, *matrixB, *matrixC; // Apuntadores a las matrices
extern struct timeval inicio, fin; // Estructuras para medir el tiempo
extern pthread_mutex_t MM_mutex; // Mutex usado en el modelo POSIX

//Prototipos de funciones 

// Inician y finalizan la medición del tiempo de ejecución
void InicioMuestra();
void FinMuestra();

// Inicializa las matrices con valores aleatorios y las imprime en pantalla
void iniMatrix(double *m1, double *m2, int D);
void impMatrix(double *matrix, int D);

// Funciones específicas de multiplicación según el modelo de paralelismo 
void *multiMatrixPosix(void *variables); // Para POSIX
void multiMatrixFork(double *mA, double *mB, double *mC, int D, int filaI, int filaF);// Para Fork
void multiMatrixOpenMP(double *mA, double *mB, double *mC, int D); // Para OpenMP
void multiMatrixFilasOpenMP(double *mA, double *mB, double *mC, int D);// Para OpenMP (filas x filas)

#endif
