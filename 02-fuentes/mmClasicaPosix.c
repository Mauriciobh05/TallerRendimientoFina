/*#######################################################################################
#* Fecha:
#* Autor: Mauricio Beltrán Huertas 
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
#* Descripción:
#*      Implementación del algoritmo clásico de multiplicación de matrices cuadradas,
#*      utilizando paralelismo con hilos POSIX (Pthreads) para dividir el trabajo entre
#*      múltiples hilos. Cada hilo calcula un conjunto de filas de la matriz resultado.
#*      El programa permite evaluar el rendimiento del procesamiento concurrente frente
#*      a la ejecución secuencial, midiendo el tiempo total de ejecución en microsegundos.
######################################################################################*/

#include "funciones.h"


int main(int argc, char *argv[]){
	if (argc < 3){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		exit(0);	
	}
    int N = atoi(argv[1]);  // Tamaño de la matriz
    int n_threads = atoi(argv[2]);  // Número de hilos

    pthread_t p[n_threads];  // Arreglo para manejar los hilos
    pthread_attr_t atrMM;  // Atributos de los hilos



	// Reserva memoria dinámica para las matrices

	matrixA  = (double *)calloc(N*N, sizeof(double));
	matrixB  = (double *)calloc(N*N, sizeof(double));
	matrixC  = (double *)calloc(N*N, sizeof(double));

	iniMatrix(matrixA, matrixB, N);  // Inicializa e imprime las matrices
	impMatrix(matrixA, N);
	impMatrix(matrixB, N);

	InicioMuestra(); // Inicia la medición de tiempo

	pthread_mutex_init(&MM_mutex, NULL);  // Inicializa el mutex
	pthread_attr_init(&atrMM);  // Inicializa los atributos de los hilos
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    // Crea los hilos
    for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;  // ID del hilo
		datos->nH  = n_threads;// Total de hilos
		datos->N   = N;   // Tamaño de la matriz

        pthread_create(&p[j],&atrMM,multiMatrixPosix,(void *)datos);  // Se crea el hilo
	}

 // Espera a que todos los hilos terminen

    for (int j=0; j<n_threads; j++){
        pthread_join(p[j],NULL);
}
	FinMuestra();  // Finaliza la medición de tiempo

	
	impMatrix(matrixC, N);  // Imprime la matriz resultante

	/*Liberación de Memoria*/
	free(matrixA); // Se libera la memoria de A
	free(matrixB); // Se libera la memoria de B
	free(matrixC); // Se libera la memoria de C

// Destruye atributos y mutex

	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit (NULL);

	return 0;
}

