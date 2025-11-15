/*#######################################################################################
#* Archivo: funciones.c
#* Autor: Mauricio Beltrán Huertas
#* Descripción:
#*      Interfaces de funciones que implementa las operaciones comunes de los
#*      programas de multiplicación de matrices inicialización, impresión,
#*      medición de tiempo y cálculo paralelo.
######################################################################################*/

#include "funciones.h"

// Declaración de variables globales
double *matrixA, *matrixB, *matrixC;
struct timeval inicio, fin;
pthread_mutex_t MM_mutex;

// Funciones de medición 
void InicioMuestra() { // Guarda el tiempo inicial
    gettimeofday(&inicio, (void *)0);
}

void FinMuestra() { 
    // Calcula y muestra el tiempo total transcurrido en microsegundos desde que se llamó a InicioMuestra()

    gettimeofday(&fin, (void *)0); 
    // Captura el tiempo actual y lo guarda en la estructura fin

    fin.tv_usec -= inicio.tv_usec;
    // Calcula la diferencia en microsegundos entre el tiempo final y el inicial

    fin.tv_sec  -= inicio.tv_sec;
    // Calcula la diferencia en segundos entre el tiempo final y el inicial

    double tiempo = (double)(fin.tv_sec * 1000000 + fin.tv_usec);
    // Convierte los segundos a microsegundos y los suma con los microsegundos restantes
    // para obtener el tiempo total en microsegundos

    printf("%9.0f µs\n", tiempo);
    // Imprime el tiempo total transcurrido con formato de 9 dígitos y el símbolo de microsegundos
}

// Inicialización e impresión

void iniMatrix(double *mA, double *mB, int D) {  // Inicializa las matrices con valores aleatorios
    for (int i = 0; i < D * D; i++, mA++, mB++) {
        *mA = (double)rand() / RAND_MAX * (5.0 - 1.0);
        *mB = (double)rand() / RAND_MAX * (9.0 - 5.0);
    }
}

void impMatrix(double *matrix, int D) { // Imprime una matriz si el tamaño es pequeño
    if (D < 9) {
        printf("\nImpresión ...\n");
        for (int i = 0; i < D * D; i++, matrix++) {
            if (i % D == 0) printf("\n");
            printf(" %.2f ", *matrix);
        }
        printf("\n ");
    }
}

// Multiplicación POSIX 

void *multiMatrixPosix(void *variables) { // Función que ejecuta cada hilo: multiplica parte de la matriz
    struct parametros *data = (struct parametros *)variables; // Recibe los datos del hilo
    
    int idH = data->idH; // ID del hilo
    int nH  = data->nH;  // Total de hilos
    int D   = data->N;   // Tamaño de la matriz

    // Define las filas inicial y final que este hilo procesará
    int filaI = (D / nH) * idH;
    int filaF = (D / nH) * (idH + 1);
    double Suma, *pA, *pB;

    for (int i = filaI; i < filaF; i++) { // Recorre las filas asignadas
        for (int j = 0; j < D; j++) {  // Recorre todas las columnas
            pA = matrixA + i * D;    // Apunta al inicio de la fila de A
            pB = matrixB + j;        // Apunta al inicio de la columna de B
            Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB += D) {
                Suma += *pA * *pB; // Multiplica y acumula productos
            }
            matrixC[i * D + j] = Suma; // Guarda el resultado
        }
    }

    pthread_mutex_lock(&MM_mutex);   // Bloquea el mutex 
    pthread_mutex_unlock(&MM_mutex); // Libera el mutex
    pthread_exit(NULL);              // Termina el hilo
}

// Multiplicación Fork 

void multiMatrixFork(double *mA, double *mB, double *mC, int D, int filaI, int filaF) { 
    // Multiplica las matrices A y B en el rango de filas asignado 
    double Suma, *pA, *pB; // Declara una variable acumuladora  y dos punteros para recorrer A y B

    // Recorre las filas desde la fila inicial (filaI) hasta la fila final (filaF)
    for (int i = filaI; i < filaF; i++) {
        // Recorre todas las columnas de la matriz B
        for (int j = 0; j < D; j++) {
            Suma = 0.0; // Reinicia el acumulador para cada posición i, j
            pA = mA + i * D; // Apunta al inicio de la fila i en la matriz A
            pB = mB + j;     // Apunta al inicio de la columna j en la matriz B

            // Recorre los elementos de la fila i de A y la columna j de B
            for (int k = 0; k < D; k++, pA++, pB += D) {
                Suma += *pA * *pB; // Multiplica y acumula los productos parciales
            }

            // Al finalizar el recorrido de k, guarda el resultado en la posición correspondiente de C
            mC[i * D + j] = Suma;
        }
    }
}

// Multiplicación OpenMP 

void multiMatrixOpenMP(double *mA, double *mB, double *mC, int D) { 
    // Multiplica matrices usando paralelismo con OpenMP
    double Suma, *pA, *pB;
    #pragma omp parallel  // Se inicia la región paralela
    {
    #pragma omp for  // Se distribuye el trabajo del bucle entre los hilos
    for (int i = 0; i < D; i++) { // Recorre las filas de la matriz A
        for (int j = 0; j < D; j++) { // Recorre las columnas de la matriz B
            pA = mA + i * D;	
            pB = mB + j; 
            Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB += D) {
                Suma += *pA * *pB;
            }
            mC[i * D + j] = Suma; // Guarda el resultado en la posición correspondiente de C
        }
    }
    }
}

// Multiplicación Filas x Filas con OpenMP 

void multiMatrixFilasOpenMP(double *mA, double *mB, double *mC, int D) { 
    // Se multiplican las matrices usando paralelismo con OpenMP
    double Suma, *pA, *pB;
    #pragma omp parallel  // Se inicia la región paralela
    {
    #pragma omp for // Se distribuye el trabajo entre los hilos 
    for (int i = 0; i < D; i++) {  // Recorre las filas de A
        for (int j = 0; j < D; j++) {   // Se recorren las columnas de B transpuesta
            pA = mA + i * D;     // Se apunta al inicio de la fila i
            pB = mB + j * D;     // Se apunta al inicio de la fila j 
            Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB++) { // Se recorre los elementos de la fila y columna
                Suma += *pA * *pB;
            }
            mC[i * D + j] = Suma; // Se guarda el resultado 
        }
    }
    }
}


