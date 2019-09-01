int trabajo(int idHilo){
    printf("Hilo %i START JOB\n", idHilo);
    int sum = 0;
    for(int i = 1; i<1001; i++){
        sum += i;
    }
    printf("Hilo %i END JOB\n", idHilo);
}
