/*#######################################################################################
#* Fecha:
#* Autor: Mauricio Beltrán Huertas 
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Procesos Fork 
#* 
#* Descripción:
#*      Implementación del algoritmo clásico de multiplicación de matrices cuadradas
#*      utilizando paralelismo mediante la creación de múltiples procesos con la llamada
#*      al sistema fork(). Cada proceso hijo se encarga de calcular un subconjunto de
#*      filas de la matriz resultado, trabajando de forma independiente.
######################################################################################*/
#include "funciones.h"


int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");
		exit(0);
	}
	int N      = (int) atoi(argv[1]); // Tamaño de la matriz
	int num_P  = (int) atoi(argv[2]); // Número de procesos a crear

         // Reserva memoria dinámica para las matrices
	double *matA = (double *) calloc(N*N, sizeof(double));
	double *matB = (double *) calloc(N*N, sizeof(double));
	double *matC = (double *) calloc(N*N, sizeof(double));

    srand(time(0)); 
    
// Inicializa e imprime las matrices
    iniMatrix(matA, matB, N);
    impMatrix(matA, N);
    impMatrix(matB, N);
    
    int rows_per_process = N/num_P; // Calcula cuántas filas procesará cada proceso

	InicioMuestra(); // Se inicia la medición del tiempo

    for (int i = 0; i < num_P; i++) { 	// Crea los procesos hijos
        pid_t pid = fork();
        
        if (pid == 0) { 
            int start_row = i * rows_per_process;
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;
            
			multiMatrixFork(matA, matB, matC, N, start_row, end_row); 
            
			if(N<9){ // Imprime el rango calculado por el proceso hijo (solo si N < 9)
           		printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);
            	for (int r = start_row; r < end_row; r++) {
                	for (int c = 0; c < N; c++) {
                    	printf(" %.2f ", matC[N*r+c]);
                	}
                	printf("\n");
            	}
			}
            exit(0); 
        } else if (pid < 0) { // Error en la creación del proceso
            perror("fork failed");
            exit(1);
        }
    }
     // Espera a que todos los procesos hijos terminen
    for (int i = 0; i < num_P; i++) { 
        wait(NULL);
    }
  	
	FinMuestra(); 
 	// Se libera la memoria dinámica
	free(matA);
	free(matB);
	free(matC);

    return 0;
}
