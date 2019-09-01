#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/*
Proyecto 1 - OpenMP y el Algoritmo de Kessel
Por Miguel Raz Guzman Maceod
412001466
AlgoritmosParalelos2020I
31/08/19
V1.0

Metas:
Implementar en C un programa que utilice el algoritmo de Torneo (basado en el algoritmo de Kessels) para administrar la exclusión mutua entre n hilos. 
El programa deberá recibir del usuario el número n de hilos a utilizar. 
Luego, deberá lanzar n hilos que iteren 10 veces, compitiendo en cada iteración para entrar a su sección crítica y utilizando el algoritmo de Torneo para manejar la exclusión mutua. 
La sección crítica consistirá en tres pasos: 
• imprimir en pantalla un mensaje que indique que el hilo entró a su sección crítica e indique el identificador del hilo. 
• realizar iterativamente la suma de los primeros mil números naturales (para tardar un poco) 
• imprimir en pantalla un mensaje que indique que el hilo ha terminado su sección crítica. 
Además, deberá indicarse por medio de un mensaje cada vez que el hilo "gane una ronda" y avance al siguiente nivel del árbol. 
• Incluir un README con nombre y numero de cuenta.

*/

// Copia descarada de la practica0 para empezar el programa
long int main(int argc, char** argv){
	struct timeval inicio, fin;//nos permiten medir el tiempo de ejecucion
	gettimeofday(&inicio, NULL);//guarda el tiempo al inicio del programa
	int tiempo;

	int MAX_HILOS=100; //limite superior (arbitrario) del numero de hilos
	int numHilos, idHilo;

	//verifica el numero de hilos que se paso como parametro
	if (argc < 2){
		printf("por favor especifique el numero de hilos\n");
		exit(1);
	}
	sscanf(argv[1], "%i", &numHilos);
	if (numHilos < 1 || numHilos > MAX_HILOS){
		printf("Numero de hilos no valido (%i)\n", numHilos);
		exit(1);
	}

	omp_set_num_threads(numHilos);
	long int suma, sumaHilo;
	suma=0;

	//inicia seccion paralela
	#pragma omp parallel private(idHilo, sumaHilo)
    {
		idHilo = omp_get_thread_num();
		if (idHilo==0){
			printf ("iniciando calculo con %i hilos\n", omp_get_num_threads());
		}

		//cada hilo realiza una suma parcial
		sumaHilo=0;
		int i;
		for (i=idHilo;i<1000000000;i+=numHilos){
			sumaHilo+=i;
		}

		//indica que la siguiente seccion se realiza con acceso exclusivo
		#pragma omp critical
		{
			//cada hilo actualiza la suma total con su resultado parcial
			suma+=sumaHilo;
		}
	}//fin de seccion paralela
	gettimeofday(&fin, NULL); //guarda el tiempo al final del programa
	tiempo = (fin.tv_sec - inicio.tv_sec)* 1000000 + (fin.tv_usec - inicio.tv_usec);
	printf("suma: %li  \ntiempo de ejecucion: %i microsegundos\n",suma, tiempo); //imprime resultados
}
