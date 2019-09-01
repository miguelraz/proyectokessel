#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

// Preguntas Fer y Daniel: 
// 1. Instruccion await
// Donde se gana la ronda
// Que no hay carrera cuando un hilo gana una ronda?
// Indicar vs quien se gano ronda - ID?

// 1. Crear Arbol con N verts y raiz 1. y 2^k = N
// 2. Hijo izquierdo es 2v, con v in [1..n-1]
// 3. Hijo derecho es 2v+1
// 4. hoja n+i es el proceso i
// 5. arreglo local a proceso edge[v] con entradas {1,0}
// 6. Usaremos esto:
// 7. b[v,0], b[v,1]
// 8. turn[v,0]
// 9. turn[v,1]
//    Local registers:
//    node - indica nodo actual del arbol en que compiten
//    id - de que nodo en alguno d elos subarbols llego el proc.
//      if id 2v par -> id = P0 en algo anterior
//      if id 2v+1 impar -> id = P1 en algo anterior
//    local - para cada proceso de Kessels

int kessels(int numHilos){

    int numHilos = omp_set_num_threads(numHilos);
    int n = numHilos;
    int v = numHilos - 1;
    int edge[v] = {0};
    int b[v][2] = {0};
    int turn[v][2] = {0};
    int local = 0;

// STAR 3. Algoritmo de Torneo 
#pragma omp parallel 
    
    int idHilo = get_thread_num(); // Quien soy
    int node = idHilo + n;         // Donde estoy
    int id = node % 2;             // De que arbol vengo

    int nodeid = idHilo + n;

    // STAR 2. Competencia para salir de bucle y entrar a seccion critica
    while (node > 1){
        id = node % 2;
        node = node / 2;
        b[node][id] = true;
        local = (turn[mode][1 - id] + id) % 2;
        turn[node][id] = local;
        await( (b[node][1 - id] = false) || local != (turn[node][1 - id] + id) % 2);
        edge[node] = id;
    }

    // 4. Mensaje de ganar ronda
    printf("Hilo,%i,NODE,%i\n", idHilo, nodeid);
    // 1. Entrar a seccion critica
    printf("Hilo,%i,ENTER,CRITICAL\n", idHilo);
    suma = trabajo(idHilo);
    // 3. Salir de seccion critica
    printf("Hilo,%i,EXIT,CRITICAL\n", idHilo);

    node = 1;
    // Cleanup y resettear etiquetas
    while(node < n){
        b[node, edge[node]] = false;
        node = 2*node + edge[node];
    }

}
