#include <stdio.h>
#include <stdbool.h>
#include <openmp.h>

int main(){

    int numHilos;
    int idHilo;

    int turn[] = {0,0};
    bool b[] = {0,0};
    int local[] = {0,0}

// P0 puede escribir en turn[0] y b[0] - leer en turn[1], b[1]
// P1 puede escribir en turn[1] y b[1] - leer en turn[0], b[0]
//
// Idea de Peterson:
// En vez de proteger SC, manipular tus banderas de turno.
// turn = 0 <=> turn[0] == turn[1]
// turn = 1 <=> turn[0] != turn[1]

#pragma openmp private

    if(idHilo == 0){
        b[0] = true;
        local[0] = turn[1];
        await( (b[idHilo] = false) || (local[idHilo] != ((turn[1 - i] + i) % 2)));
        // Entrando a seccion critica
        printf("Hilo,%i,ENTER,CRITICAL\n", idHilo);
        trabajo(idHilo);
        // Saliendo Seccion critica
        printf("Hilo,%i,EXIT,CRITICAL\n", idHilo);
        b[0] = false;
    }

    if(idHilo == 1){
        b[1] = true;
        local[1] = 1-turn[0]; // equivalente a !turn[0]
        turn[1] = local[1];
        await( (b[idHilo] = false) || (local[idHilo] == ((turn[1-i] + i) % 2)));
        // Entrando a seccion critica
        printf("Hilo,%i,ENTER,CRITICAL\n", idHilo);
        trabajo(idHilo);
        // Saliendo seccion critica
        printf("Hilo,%i,EXIT,CRITICAL\n", idHilo);
        b[1] = false;
    }


}


