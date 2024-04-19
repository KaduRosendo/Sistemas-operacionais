#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int arrivalTime;
  int moveDirection;
} Individual;

int currentTime = 0;
int currentDirection = 0;
int totalIndividuals = 0;
int finalTime = 0;

void *processMovement(void *arg) {
  Individual *queue = (Individual *)arg;

  currentDirection = queue[0].moveDirection;
  finalTime = queue[0].arrivalTime + 10;

  int index = 0;
  int processedCount = 0;
  Individual nextInLine;

  while (1) {
    if (currentTime == finalTime) {
      currentDirection = 1 - currentDirection;
      if (nextInLine.moveDirection == currentDirection) {
        finalTime += 10;
        processedCount++;
      }
    }

    if (currentTime == queue[index].arrivalTime) {
      if (currentDirection == queue[index].moveDirection) {
        if (queue[index].arrivalTime <= finalTime) {
          finalTime = queue[index].arrivalTime + 10;
          processedCount++;
        }
        index++;
      } else {
        nextInLine = queue[index];
        index++;
      }
    }

    currentTime++;
    if (processedCount == totalIndividuals) {
      break;
    }
  }

  return NULL;
}

int main() {
  FILE *inputFile = fopen("input.txt", "r");
  if (!inputFile) {
    fprintf(stderr, "Falha ao abrir o arquivo input\n");
    return EXIT_FAILURE;
  }

  if (fscanf(inputFile, "%d", &totalIndividuals) != 1) {
    fprintf(stderr, "Falha ao ler o número de individuos\n");
    fclose(inputFile);
    return EXIT_FAILURE;
  }

  Individual *queue = malloc(totalIndividuals * sizeof(Individual));
  if (!queue) {
    fprintf(stderr, "Falha ao alocar memória para os individuos\n");
    fclose(inputFile);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < totalIndividuals; i++) {
    if (fscanf(inputFile, "%d %d", &queue[i].arrivalTime, &queue[i].moveDirection) != 2) {
      fprintf(stderr, "Falha ao ler dados dos individuos %d.\n", i + 1);
      fclose(inputFile);
      free(queue);
      return EXIT_FAILURE;
    }
  }

  fclose(inputFile);

  pthread_t thread;
  if (pthread_create(&thread, NULL, processMovement, queue) != 0) {
    fprintf(stderr, "Falha na criação do Thread\n");
    free(queue);
    return EXIT_FAILURE;
  }

  pthread_join(thread, NULL);
  free(queue);

  FILE *outputFile = fopen("output.txt", "w");
  if (!outputFile) {
    fprintf(stderr, "Falha ao abrir o arquio output\n");
    return EXIT_FAILURE;
  }

  fprintf(outputFile, "%d\n", finalTime);
  fclose(outputFile);

  return EXIT_SUCCESS;
}
