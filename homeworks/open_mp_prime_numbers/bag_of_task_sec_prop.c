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
    if (argc != 4 || !isInteger(argv[1]) || !isInteger(argv[2]) || !isInteger(argv[3])) {
        printf("Uso: ./bag_of_tasks <objetivo> <num_threads> <size_of_bag>\n");
        return false;
    }

    return true;
}

void processTask(Task *task, int *resultVector, int index) {

}

int main(int argc, char *argv[]) {

    if (!validateInput(argc, argv)) {
        return 1;
    }

    int objective = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    int bagSize = atoi(argv[3]);
    int primeCount = 0;

    //start to count the execution time
    clock_t startTime = clock();


    omp_set_num_threads(numThreads);


    int chunkSize = objective / bagSize;
    int start = 3;
    int end;
    bool sem = false;
    int localCount = 0;

    #pragma omp parallel
    {

    #pragma omp master
    {
        while (end != objective){
            if (sem == false) {
                #pragma atomic
                end = start + chunkSize;
            if (end > objective) end = objective;

            printf("Master [%d] criou um noco chunk %d..%d\n", omp_get_thread_num(), start, end);
            #pragma atomic
            sem = true;
            }

            if (end != objective) start = end + 1;
        }
    }

        while (end != objective) {
            #pragma single nowait private(localCount)
            if (sem == false) continue;
            int thread = omp_get_thread_num();

            #pragma atomic
            sem = false;

            for (int num = start; num <= end; num++) {
                if (isPrime(num)) {
                    localCount++;
                }
            }

            printf("Resultado na thread [%d] com chunk %d..%d foi %d\n", thread , start, end, localCount);
            #pragma atomic
            primeCount += localCount;
        }
    }

    clock_t endTime = clock();
    double cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    printf("\nQuantidade de números primos encontrados: %d\n", primeCount+1);
    printf("\nTempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}
