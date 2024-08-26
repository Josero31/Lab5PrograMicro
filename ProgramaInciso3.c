#include <stdio.h>
#include <omp.h>

#define N 10
#define ARRAY_SIZE 10

// Función para calcular el factorial de un número
void calculate_factorial(int num) {
    long long factorial = 1;
    for (int i = 1; i <= num; i++) {
        factorial *= i;
    }
    printf("Factorial de %d es: %lld\n", num, factorial);
}

// Función para generar la serie de Fibonacci hasta N términos
void generate_fibonacci(int num) {
    long long fib[N];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < num; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    printf("Serie de Fibonacci hasta %d términos: ", num);
    for (int i = 0; i < num; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");
}

// Función para encontrar el máximo en un arreglo
void find_max_in_array(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf("El máximo en el arreglo es: %d\n", max);
}

int main() {
    int arr[ARRAY_SIZE] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            calculate_factorial(N);
        }

        #pragma omp section
        {
            generate_fibonacci(N);
        }

        #pragma omp section
        {
            find_max_in_array(arr, ARRAY_SIZE);
        }
    }

    return 0;
}
