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
      currentDirection = 1 - currentDirection; // Toggle direction
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
    fprintf(stderr, "Failed to open input file.\n");
    return EXIT_FAILURE;
  }

  if (fscanf(inputFile, "%d", &totalIndividuals) != 1) {
    fprintf(stderr, "Failed to read the number of individuals.\n");
    fclose(inputFile);
    return EXIT_FAILURE;
  }

  Individual *queue = malloc(totalIndividuals * sizeof(Individual));
  if (!queue) {
    fprintf(stderr, "Failed to allocate memory for individuals.\n");
    fclose(inputFile);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < totalIndividuals; i++) {
    if (fscanf(inputFile, "%d %d", &queue[i].arrivalTime, &queue[i].moveDirection) != 2) {
      fprintf(stderr, "Failed to read data for individual %d.\n", i + 1);
      fclose(inputFile);
      free(queue);
      return EXIT_FAILURE;
    }
  }

  fclose(inputFile);

  pthread_t thread;
  if (pthread_create(&thread, NULL, processMovement, queue) != 0) {
    fprintf(stderr, "Failed to create thread.\n");
    free(queue);
    return EXIT_FAILURE;
  }

  pthread_join(thread, NULL);
  free(queue);

  FILE *outputFile = fopen("output.txt", "w");
  if (!outputFile) {
    fprintf(stderr, "Failed to open output file.\n");
    return EXIT_FAILURE;
  }

  fprintf(outputFile, "%d\n", finalTime);
  fclose(outputFile);

  return EXIT_SUCCESS;
}
