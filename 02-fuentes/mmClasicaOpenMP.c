/*#######################################################################################
 #* Fecha: 
 #* Autor: Mauricio Beltrán Huertas 
 #* Programa: 
 #* 	 Multiplicación de Matrices algoritmo clásico
 #* Versión:
 #*	 Paralelismo con OpenMP
 #* Descripción 
 #* 
 #*       Implementación del algoritmo clásico de multiplicación de matrices cuadradas 
 #*      utilizando paralelismo con OpenMP. El programa divide las iteraciones del cálculo 
 #*      entre múltiples hilos gestionados automáticamente por el compilador, permitiendo 
 #*      aprovechar los núcleos del procesador para reducir el tiempo de ejecución.
######################################################################################*/

#include "funciones.h"

int main(int argc, char *argv[]){
	if(argc < 3){ // Verifica que se ingresen los dos parámetros 
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}


	int N = atoi(argv[1]); // Tamaño de la matriz
	int TH = atoi(argv[2]);
	double *matrixA  = (double *)calloc(N*N, sizeof(double)); // Reserva memoria para A
	double *matrixB  = (double *)calloc(N*N, sizeof(double)); // Reserva memoria para B
	double *matrixC  = (double *)calloc(N*N, sizeof(double)); // Reserva memoria para C

	srand(time(NULL));

	omp_set_num_threads(TH); // Se configuran los hilos que OpenMP usará

	iniMatrix(matrixA, matrixB, N); // Se inicializan las matrices A y B

	impMatrix(matrixA, N); // Se imprime A (si N < 9)
	impMatrix(matrixB, N); // Se imprime B (si N < 9)

	InicioMuestra();  // Se inicia la medición del tiempo
	multiMatrixOpenMP(matrixA, matrixB, matrixC, N);
	FinMuestra(); // Se finaliza la medición y se muestra el tiempo total

	impMatrix(matrixC, N);

	/*Liberación de Memoria*/
	free(matrixA); // Se libera la memoria de A
	free(matrixB); // Se libera la memoria de B
	free(matrixC); // Se libera la memoria de C
	
	return 0;
}
