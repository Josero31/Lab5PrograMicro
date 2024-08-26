#include <stdio.h>
#include <omp.h>

#define N 10

int main() {
    int variable1 = 0;
    int variable2 = 0;

    // Usando shared para variable1 y private para variable2
    #pragma omp parallel for shared(variable1) private(variable2)
    for (int i = 0; i < N; i++) {
        variable1 += i;
        variable2 = i;
        printf("Thread %d, Iteration %d, variable1: %d, variable2: %d\n", omp_get_thread_num(), i, variable1, variable2);
    }

    printf("Final value of variable1: %d\n", variable1);
    printf("Final value of variable2: %d (Note: This value is not meaningful outside the parallel region)\n", variable2);

    return 0;
}
