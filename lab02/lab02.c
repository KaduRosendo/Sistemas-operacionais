
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAMANHO_MSG 256

int main(void) {
    int fd_pipe[2]; // Canal de comunicação entre processos
    pid_t pid_filho;
    char mensagem_do_pai[TAMANHO_MSG] = "Olá do pai!";
    char buffer[TAMANHO_MSG];

    // Criação do pipe
    if (pipe(fd_pipe) < 0) {
        perror("Erro ao criar o pipe");
        exit(EXIT_FAILURE);
    }

    pid_filho = fork();
    if (pid_filho < 0) {
        perror("Erro ao criar processo filho");
        exit(EXIT_FAILURE);
    } else if (pid_filho == 0) { // Processo filho
        close(fd_pipe[1]); // Fecha o lado de escrita no processo filho
        // Recebe a mensagem do processo pai
        read(fd_pipe[0], buffer, TAMANHO_MSG);
        printf("Filho: Recebi a mensagem '%s'\n", buffer);
        close(fd_pipe[0]); // Fecha o lado de leitura
        printf("Filho encerrando.\n");
        exit(EXIT_SUCCESS);
    } else { // Processo pai
        close(fd_pipe[0]); // Fecha o lado de leitura no processo pai
        // Envia a mensagem para o processo filho
        write(fd_pipe[1], mensagem_do_pai, TAMANHO_MSG);
        printf("Pai: Mensagem enviada ao filho.\n");
        close(fd_pipe[1]); // Fecha o lado de escrita
        wait(NULL); // Espera o processo filho terminar
        printf("Pai encerrando.\n");
    }

    return EXIT_SUCCESS;
}
