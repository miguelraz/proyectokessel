#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <stdbool.h>

/*
Proyecto 1 - OpenMP y el Algoritmo de Kessel
Por Miguel Raz Guzman Maceod
412001466
AlgoritmosParalelos2020I
31/08/19
V1.0

Metas:
Implementar en C un programa que utilice el algoritmo de Torneo (basado en el algoritmo de Kessels) para administrar la exclusión mutua entre n hilos. 

• 0. El programa deberá recibir del usuario el número n de hilos a utilizar. 

• STAR 1. Luego, deberá lanzar n hilos que iteren 10 veces, 
• STAR 2. compitiendo en cada iteración (de 10) para entrar a su sección crítica
• STAR 3. utilizando el algoritmo de Torneo para manejar la exclusión mutua. 

La sección crítica consistirá en tres pasos: 
• 1. imprimir en pantalla un mensaje que indique que el hilo entró a su sección crítica e indique el identificador del hilo. 
• 2. 🎯 realizar iterativamente la suma de los primeros mil números naturales (para tardar un poco) 
• 3. imprimir en pantalla un mensaje que indique que el hilo ha terminado su sección crítica. 
• 4. Además, deberá indicarse por medio de un mensaje cada vez que el hilo "gane una ronda" y avance al siguiente nivel del árbol. 
• 5. 🎯  Incluir un README con nombre y numero de cuenta.

Prioridades:
0 x
5 x
2 x
1 x
3 x
STAR 1 x 
STAR 2 x
STAR 3 
4 x 
*/

// 2. Realiza la suma iterativa de los primeros 1000 naturales
int trabajo(int idHilo){
    printf("Hilo,%i,START,JOB\n", idHilo);
    int sum = 0;
    for(int i = 1; i<1001; i++){
        sum += i;
    }
    printf("Hilo,%i,END,JOB\n", idHilo);
    return sum;
}

// Copia descarada de la practica0 para empezar el programa
long int main(int argc, char** argv){
  //struct timeval inicio, fin;//nos permiten medir el tiempo de ejecucion
  //gettimeofday(&inicio, NULL);//guarda el tiempo al inicio del programa
  //int tiempo;

	int MAX_HILOS=1024; //limite superior (arbitrario) del numero de hilos
	int numHilos, idHilo;

    // 0. Recibir del usuario el numero de n hilos a utilizar
	if (argc < 2){
		printf("Por favor especifique el numero de hilos\n");
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
    
    // STAR 1. Mando los hilos a iterar 10 veces
    for(int n = 0; n < 10; n++){
      
      //inicia seccion paralela
      #pragma omp parallel private(idHilo, sumaHilo)
      {
		idHilo = omp_get_thread_num();
		if (idHilo==0){
          printf ("Hilo,%i,ENTER,MAIN,NUMHILOS,%i" omp_get_num_threads(), numHilos);
		}

		//cada hilo realiza trabajo
		sumaHilo=0;
		int i;
		//for (i=idHilo;i<1000000000;i+=numHilos){
        //  sumaHilo+=i;
		//}
          
        
		//indica que la siguiente seccion se realiza con acceso exclusivo
        #pragma omp critical
		{
          suma+=sumaHilo;
		}
        
      }
    }
}
