#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct {
    int scheduledTime;
    int preferredDirection;
} Traveller;

int currentTime = 0;
int activeDirection = 0;
int numberOfTravellers = 0;
int scheduleEnd = 0;
int communicationPipe[2];

void handleTraveller(Traveller *travellers) {
    activeDirection = travellers[0].preferredDirection;
    scheduleEnd = travellers[0].scheduledTime + 10;

    int index = 0;
    int processedTravellers = 0;
    Traveller onHold;

    while (1) {
        if (currentTime == scheduleEnd) {
            activeDirection = 1 - activeDirection; // Toggle the direction
            if (onHold.preferredDirection == activeDirection) {
                scheduleEnd += 10;
                processedTravellers++;
                write(communicationPipe[1], &scheduleEnd, sizeof(scheduleEnd));
            }
        }

        if (currentTime == travellers[index].scheduledTime) {
            if (activeDirection == travellers[index].preferredDirection) {
                if (travellers[index].scheduledTime <= scheduleEnd) {
                    scheduleEnd = travellers[index].scheduledTime + 10;
                    processedTravellers++;
                    write(communicationPipe[1], &scheduleEnd, sizeof(scheduleEnd));
                }
                index++;
            } else {
                onHold = travellers[index];
                index++;
            }
        }

        currentTime++;
        if (processedTravellers == numberOfTravellers) {
            break;
        }
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Falha ao abrir o arquivo input\n");
        return EXIT_FAILURE;
    }

    if (fscanf(inputFile, "%d", &numberOfTravellers) != 1) {
        fprintf(stderr, "Falha ao ler o número de passageiros\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    Traveller *travellers = malloc(numberOfTravellers * sizeof(Traveller));
    if (travellers == NULL) {
        fprintf(stderr, "Alocação de memória falhou\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < numberOfTravellers; i++) {
        if (fscanf(inputFile, "%d %d", &travellers[i].scheduledTime, &travellers[i].preferredDirection) != 2) {
            fprintf(stderr, "Falha ao ler as informações dos passageiros %d\n", i + 1);
            free(travellers);
            fclose(inputFile);
            return EXIT_FAILURE;
        }
    }
    fclose(inputFile);

    if (pipe(communicationPipe) == -1) {
        fprintf(stderr, "Falha na criação do Pipe\n");
        free(travellers);
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Falha na criação do Processo\n");
        free(travellers);
        return EXIT_FAILURE;
    } else if (pid == 0) {
        close(communicationPipe[0]);
        handleTraveller(travellers);
        close(communicationPipe[1]);
        free(travellers);
        exit(EXIT_SUCCESS);
    }

    close(communicationPipe[1]);
    int temp;
    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        fprintf(stderr, "Falaha ao abrir o arquivo output\n");
        return EXIT_FAILURE;
    }

    while (read(communicationPipe[0], &temp, sizeof(temp)) > 0) {
        scheduleEnd = temp;
    }
    fprintf(outputFile, "%d\n", scheduleEnd);
    fclose(outputFile);
    close(communicationPipe[0]);

    wait(NULL);
    return EXIT_SUCCESS;
}
