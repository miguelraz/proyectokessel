#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdmath.h>

// Panaderia de Lamport para N hilos
//

int find_maximum(int arr[], int numHilos)
    int max = a[0];

    for(int i = 0; i<numHilos; i++){
        a[i] > max ? max = a[i] : ;
    }
    return max;
}

void lamport(numHilos){
      
      long int sumaHilo = 0;
      omp_set_num_threads(numHilos);

      int Numero[];
      bool Eligiendo[];

      for(int i = 0; i < numHilos; i++){
          Numero[i] = 0;
          Eligiendo[i] = false;
      }

      //inicia seccion paralela
      #pragma omp parallel
      {
		idHilo = omp_get_thread_num();
		if (idHilo==0){
          printf ("Hilo,%i,ENTER,BAKERY\n", idHilo);
	        
        TODO

		//cada hilo realiza trabajo
		sumaHilo=0;
		//int i;
        sumaHilo = trabajo(idHilo);
		//for (i=idHilo;i<1000000000;i+=numHilos){
        //  sumaHilo+=i;
		//}
          
        
		//indica que la siguiente seccion se realiza con acceso exclusivo
        #pragma omp critical
		{
          //cada hilo actualiza la suma total con su resultado parcial
          suma = trabajo(idHilo);
		}
        }
      }//fin de seccion paralela

}
