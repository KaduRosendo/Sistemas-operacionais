#define _GNU_SOURCE // Isto precisa estar na primeira linha do arquivo
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define TAMANHO_PILHA 1024*64 // Definindo o tamanho da pilha para 64kB

// Variável global compartilhada
int variavelCompartilhada = 0;

// Função que será executada pelo processo filho (thread)
int funcaoFilho(void* argumento) {
    printf("Processo filho iniciando.\n");
    variavelCompartilhada = 1; // Modificando a variável compartilhada
    printf("Processo filho alterou variavelCompartilhada para %d\n", variavelCompartilhada);
    _exit(0); // Finalizando o processo filho
}

int main() {
    void* pilha;
    pid_t pid;

    // Alocando a pilha para o novo thread (processo filho)
    pilha = malloc(TAMANHO_PILHA);
    if (pilha == NULL) {
        perror("Erro ao alocar pilha");
        exit(1);
    }

    printf("Criando processo filho\n");
    // Criando o processo filho com clone
    pid = clone(&funcaoFilho, (char*)pilha + TAMANHO_PILHA,
                SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, NULL);
    if (pid == -1) {
        perror("Erro ao criar o processo filho");
        exit(2);
    }

    // Aguarda o processo filho terminar
    waitpid(pid, NULL, 0);
    printf("Processo pai lendo variavelCompartilhada como %d\n", variavelCompartilhada);

    // Liberando a pilha
    free(pilha);
    printf("Processo filho finalizado e pilha liberada.\n");
    return 0;
}
