#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DIMENSION_LIMIT 1000

int rows = 2; // Número de linhas da matriz
int cols = 2; // Número de colunas da matriz
int num_threads = 4; // Total de threads
double matriz[DIMENSION_LIMIT][DIMENSION_LIMIT]; // Matriz principal
double vector[DIMENSION_LIMIT]; // Vetor de entrada
double result[DIMENSION_LIMIT]; // Vetor de saída

void *MatrizVectorMultiply(void *arg) {
    long id = (long) arg;
    int local_rows = rows / num_threads;
    int start_row = id * local_rows;
    int end_row = (id + 1 == num_threads) ? rows : start_row + local_rows;

    for (int row = start_row; row < end_row; row++) {
        result[row] = 0.0;
        for (int col = 0; col < cols; col++)
            result[row] += matriz[row][col] * vector[col];
    }

    return NULL;
}

int main() {
    pthread_t *threads;
    long thread_id;

    // Alocar memória para os handlers das threads
    threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));

    // Preenchendo a matriz principal
    printf("Digite os valores para a matriz de dimensão %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("matriz[%d][%d]: ", i, j);
            scanf("%lf", &matriz[i][j]);
        }
    }

    // Preenchendo o vetor de entrada
    printf("Digite os valores para o vetor de tamanho %d:\n", cols);
    for (int i = 0; i < cols; i++) {
        printf("vector[%d]: ", i);
        scanf("%lf", &vector[i]);
    }

    // Criação de threads para multiplicação da matriz pelo vetor
    for (thread_id = 0; thread_id < num_threads; thread_id++) {
        pthread_create(&threads[thread_id], NULL, MatrizVectorMultiply, (void *) thread_id);
    }

    // Esperar todas as threads completarem
    for (thread_id = 0; thread_id < num_threads; thread_id++) {
        pthread_join(threads[thread_id], NULL);
    }

    // Liberando a memória alocada para os handlers das threads
    free(threads);

    // Exibindo o vetor resultante
    printf("Vetor resultante:\n");
    for (int i = 0; i < rows; i++) {
        printf("%.2f ", result[i]);
    }
    printf("\n");

    return 0;
}

