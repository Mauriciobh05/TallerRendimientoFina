/*#######################################################################################
 #* Fecha:
 #* Autor: Mauricio Beltrán Huertas 
 #* Programa:
 #*      Multiplicación de Matrices algoritmo matriz Transpuesta (Filas x Filas) 
 #* Versión:
 #*      Paralelismo con OpenMP
 * Descripción:
 *      Implementación paralela del algoritmo de Multiplicación de Matrices utilizando OpenMP.
 *      Este programa realiza la multiplicación de matrices cuadradas haciendo uso de la 
 *      transposición de la segunda matriz Filas x Filas, con el objetivo de optimizar el acceso 
 *      a memoria y evaluar el rendimiento del paralelismo mediante OpenMP.
 #######################################################################################*/

#include "funciones.h"

int main(int argc, char *argv[]){
	if(argc < 3){ // se validan los parametros 
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}


	int N = atoi(argv[1]); // tamaño de la matriz 
	int TH = atoi(argv[2]);
	double *matrixA  = (double *)calloc(N*N, sizeof(double)); // Reserva memoria para A
	double *matrixB  = (double *)calloc(N*N, sizeof(double)); // Reserva memoria para B
	double *matrixC  = (double *)calloc(N*N, sizeof(double)); // Reserva memoria para C
	srand(time(NULL));

	omp_set_num_threads(TH);

	iniMatrix(matrixA, matrixB, N); // Se inicializan las matrices con valores aleatorios

	impMatrix(matrixA, N);  //  imprime A solo si N < 6
	impMatrix(matrixB, N);  // Se imprime B transpuesta solo si N < 6

	InicioMuestra(); // Se inicia la medición de tiempo
	multiMatrixFilasOpenMP(matrixA, matrixB, matrixC, N); // Se multiplica A x B en paralelo
	FinMuestra(); // Se finaliza la medición y se imprime el tiempo total

	impMatrix(matrixC, N);

	/*Liberación de Memoria*/
	free(matrixA);  // Se libera memoria de A
	free(matrixB);  // Se libera memoria de B
	free(matrixC);  // Se libera memoria de C 
	
	return 0;
}
