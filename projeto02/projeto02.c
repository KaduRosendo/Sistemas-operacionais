#define _GNU_SOURCE
#include <malloc.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h> // Biblioteca para utilizar mutex

// Tamanho da pilha: 64kB
#define STACK_SIZE (1024 * 64)

struct Account {
    int balance;
};
typedef struct Account Account;

Account from, to;
int Value1, Value2;
pthread_mutex_t mutex; // Mutex para sincronização

// Função de transferência protegida por mutex
void *transferFROM(void *arg) {
    pthread_mutex_lock(&mutex); // Bloqueia o mutex antes de acessar as variáveis compartilhadas

    if (from.balance >= Value1) {
        from.balance -= Value1;
        to.balance += Value1;
    } else {
        printf("Saldo insuficiente!\n");
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    printf("Transferência concluída com sucesso!\n");
    printf("Saldo da conta C1: %d\n", from.balance);
    printf("Saldo da conta C2: %d\n", to.balance);

    pthread_mutex_unlock(&mutex); // Libera o mutex após o acesso às variáveis compartilhadas
    return NULL;
}

void *transferTO(void *arg) {
    pthread_mutex_lock(&mutex); // Bloqueia o mutex antes de acessar as variáveis compartilhadas

    if (to.balance >= Value2) {
        to.balance -= Value2;
        from.balance += Value2;
    } else {
        printf("Saldo insuficiente!\n");
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    printf("Transferência concluída com sucesso!\n");
    printf("Saldo da conta C1: %d\n", from.balance);
    printf("Saldo da conta C2: %d\n", to.balance);

    pthread_mutex_unlock(&mutex); // Libera o mutex após o acesso às variáveis compartilhadas
    return NULL;
}

int main() {
    void *stack;
    pthread_t threads[100]; // Identificadores de thread
    int i;

    // Inicialização das contas
    from.balance = 100;
    to.balance = 100;
    Value1 = 20;
    Value2 = 10;

    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex

    // Alocação da pilha
    stack = malloc(STACK_SIZE);
    if (stack == NULL) {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    for (i = 0; i < 50; i++) {
        if (pthread_create(&threads[i], NULL, transferFROM, NULL) != 0) {
            perror("pthread_create");
            exit(2);
        }

        if (pthread_create(&threads[i + 50], NULL, transferTO, NULL) != 0) {
            perror("pthread_create");
            exit(2);
        }
    }

    for (i = 0; i < 100; i++) {
        pthread_join(threads[i], NULL);
    }

    // Liberação da pilha e do mutex
    free(stack);
    pthread_mutex_destroy(&mutex);

    printf("Transferências concluídas e memória liberada.\n");
    return 0;
}
