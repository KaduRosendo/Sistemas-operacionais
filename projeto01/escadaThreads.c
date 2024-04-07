#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int time;
    int direction; // 0 para esquerda-para-direita, 1 para direita-para-esquerda
} Person;

Person people[10000];
int n;
int last_time = 0; // Último tempo registrado de uso da escada
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Função executada por cada thread para simular uma pessoa usando a escada rolante
void* simulate_person(void* arg) {
    Person* p = (Person*)arg;
    
    pthread_mutex_lock(&mutex);
    
    // Espera até que seja possível usar a escada rolante conforme a direção desejada e o tempo de chegada
    while(p->time > last_time) {
        usleep((p->time - last_time) * 1000); // Simula a espera pela escada rolante
    }
    // Atualiza o último tempo de uso considerando o tempo para atravessar
    last_time = p->time + 10;
    
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    // Lendo o arquivo de entrada
    FILE *inputFile = fopen("input/E_1", "r");
    if (inputFile == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }
    
    fscanf(inputFile, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d %d", &people[i].time, &people[i].direction);
    }
    fclose(inputFile);
    
    pthread_t threads[n];
    
    // Criando uma thread para cada pessoa
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, simulate_person, (void*)&people[i]);
    }
    
    // Aguardando todas as threads terminarem
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Escrevendo o resultado no arquivo de saída
    FILE *outputFile = fopen("output/E_1", "w");
    if (outputFile == NULL) {
        perror("Erro ao abrir arquivo de saída");
        return 1;
    }
    
    fprintf(outputFile, "%d\n", last_time);
    fclose(outputFile);
    
    return 0;
}
