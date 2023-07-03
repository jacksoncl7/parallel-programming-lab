#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <ctype.h>
#include <time.h>

#define MAX_TASKS 100

typedef struct {
    int start;
    int end;
} Task;

int isPrime(int num) {
    if (num <= 1)
        return 0;

    if (num == 2)
        return 1;

    if (num % 2 == 0)
        return 0;

    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

bool isInteger(const char *str) {
    if (str == NULL || *str == '\0' || isspace(*str))
        return false;

    char *endptr;
    strtol(str, &endptr, 10);

    return (*endptr == '\0');
}

bool validateInput(int argc, char *argv[]) {
    if (argc != 3 || !isInteger(argv[1]) || !isInteger(argv[2])) {
        printf("Uso: ./bag_of_tasks <objetivo> <num_threads>\n");
        return false;
    }

    return true;
}

void processTask(Task *task, int *resultVector, int index) {
    int localCount = 0;
    for (int num = task->start; num <= task->end; num++) {
        if (isPrime(num)) {
            localCount++;
        }
    }
    resultVector[index] += localCount;
}

int main(int argc, char *argv[]) {

    if (!validateInput(argc, argv)) {
        return 1;
    }

    int objective = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    int bagSize = 20;

    omp_set_num_threads(numThreads);

    double startingTime = omp_get_wtime();

    int chunkSize = objective / bagSize;
    int extra = objective % bagSize;
    int start = 3;
    Task bag[bagSize];

    for (int i = 0; i < bagSize; i++) {
        Task task;
        task.start = start;
        task.end = start + chunkSize - 1;

        if (extra > 0) {
            task.end++;
            extra--;
        }

        bag[i] = task;

        start = task.end + 1;
    }

    int resultVector[bagSize];
    for (int i = 0; i < bagSize; i++) resultVector[i] =  0;

    #pragma omp parallel for schedule(guided)
    for (int i = 0; i < bagSize; i++) {
        processTask(&bag[i], resultVector, i);
    }

    for (int i = 1; i < bagSize; i++) {
        resultVector[0] +=  resultVector[i];
    }

    double finishingTime = omp_get_wtime();
    int primeCount = 1 + resultVector[0]; // Adds the number '2', which is also prime.
    printf("Quant. de primos entre 1 e n: %ld \n", primeCount);
	printf("Tempo de execucao: %1.3lf \n", finishingTime - startingTime);

    return 0;
}
