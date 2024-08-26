#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    int sum = 0;
    double start_time, end_time;

    // Iniciar el temporizador
    start_time = omp_get_wtime();

    // Calcular la suma de los primeros N números naturales en paralelo
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;
    }

    // Detener el temporizador
    end_time = omp_get_wtime();

    // Imprimir el resultado y el tiempo de ejecución
    printf("La suma de los primeros %d números naturales es: %d\n", N, sum);
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);

    return 0;
}
