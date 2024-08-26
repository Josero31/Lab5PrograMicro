#include <stdio.h>
#include <omp.h>

#define INPUT_SIZE 1024
#define TAP1 16
#define TAP2 16

float sample[INPUT_SIZE + TAP1];
float coeff1[TAP1], coeff2[TAP2];
float data_out[INPUT_SIZE], final[INPUT_SIZE];

float correction(float data, float coeff) {
    return data * coeff; // Simple función de corrección como ejemplo
}

int main() {
    float sum;

    // Llenar sample y coefficients con valores de ejemplo
    for (int i = 0; i < INPUT_SIZE + TAP1; i++) {
        sample[i] = i * 0.1; // Valores de ejemplo
    }
    for (int j = 0; j < TAP1; j++) {
        coeff1[j] = j * 0.2; // Valores de ejemplo para coeff1
    }
    for (int j = 0; j < TAP2; j++) {
        coeff2[j] = j * 0.3; // Valores de ejemplo para coeff2
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Productor: Filtro de Respuesta al Impulso Finito (FIR)
            for (int i = 0; i < INPUT_SIZE; i++) {
                sum = 0.0;
                for (int j = 0; j < TAP1; j++) {
                    sum += sample[i + j] * coeff1[j];
                }
                data_out[i] = sum;
            }
        }

        #pragma omp section
        {
            // Consumidor: aplicar función de corrección
            for (int i = 0; i < INPUT_SIZE; i++) {
                final[i] = 0.0;
                for (int j = 0; j < TAP2; j++) {
                    final[i] += correction(data_out[i], coeff2[j]);
                }
            }
        }
    }

    // Imprimir los primeros valores para verificar la funcionalidad
    for (int i = 0; i < 10; i++) {
        printf("final[%d] = %f\n", i, final[i]);
    }

    return 0;
}
