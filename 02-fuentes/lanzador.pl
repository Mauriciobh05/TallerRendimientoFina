#!/usr/bin/perl
#############################################
# Pontificia Universidad Javeriana
# Autor: Mauricio Beltrán Huertas
# Materia: Sistemas Operativos
# Tema: Taller de Evaluación de Rendimiento
# Script de automatización de ejecución por lotes
# Descripción:
#     Este script automatiza la ejecución de diferentes versiones del algoritmo de 
#     multiplicación de matrices (Fork, POSIX, OpenMP y FilasOpenMP) con múltiples 
#     configuraciones de tamaño de matriz y cantidad de hilos/procesos.
#
#     Su objetivo es facilitar la creación de una batería de experimentos completa 
#     para el análisis de rendimiento, ejecutando cada programa 30 veces con cada 
#     combinación de parámetros y guardando los resultados en archivos .dat separados.
#############################################

$Path = `pwd`; # Obtiene el directorio actual donde se encuentra el script
chomp($Path); # Elimina el salto de línea final del comando `pwd`

@Ejecutables = ( # Lista de ejecutables a probar 
    "mmClasicaFork",
    "mmClasicaPosix",
    "mmClasicaOpenMP",
    "mmFilasOpenMP"
);

@Size_Matriz = ("2","10","20"); # Tamaños de matriz a evaluar
@Num_Hilos = (1,2,4,8,16,20); # Cantidad de hilos o procesos a utilizar en cada prueba
$Repeticiones = 30; # Número de repeticiones por configuración 

foreach $prog (@Ejecutables) { # Bucle principal: recorre todos los programas a ejecutar
    print "\n=== Ejecutando $prog ===\n"; # Indica el programa que se está ejecutando
    foreach $size (@Size_Matriz) {    # Recorre cada tamaño de matriz
        foreach $hilo (@Num_Hilos) { # Recorre cada cantidad de hilos/procesos

            if ($hilo <= $size) {  # Solo ejecuta si el número de hilos es menor o igual al tamaño de la matriz
                $file = "$Path/${prog}_Size-${size}_Hilos-${hilo}.dat"; # Define el nombre del archivo de salida para esta configuración
                for ($i = 0; $i < $Repeticiones; $i++) { # Ejecuta el programa repetidas veces para la misma configuración
                    system("$Path/$prog $size $hilo >> $file");  # Redirige la salida estándar (tiempos) al archivo .dat
                }
                print "$Path/$prog $size $hilo\n";  # Imprime en pantalla el comando ejecutado para seguimiento
            }
        }
    }
}

