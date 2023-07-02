#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <ctype.h>
#include <time.h>

#define MAX_TASKS 100

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

int main(int argc, char *argv[]) {

    if (!validateInput(argc, argv)) {
        return 1;
    }

    int objective = atoi(argv[1]);
    int numThreads = atoi(argv[2]);
    int bagSize = atoi(argv[3]);

    //start to count the execution time
    // clock_t startTime = clock();

    omp_set_num_threads(numThreads);
    int chunkSize = objective / bagSize;
    int start = 3;
    int end = 0;
    int primeCount = 0;
    bool workerControl = true;
    omp_lock_t generationSem, consumeSem;

    int localCount = 0;
    int localStart = 0;
    int localEnd = 0;

    omp_init_lock(&generationSem);
    omp_init_lock(&consumeSem);
    omp_set_lock(&consumeSem);

    #pragma omp parallel
    {
        #pragma omp master
        {
            while (end != objective){
                if(!omp_test_lock(&generationSem)) continue;

                end = start + chunkSize;
                if (end > objective) { end = objective; }
                printf("Master [%d] criou um novo chunk %d..%d\n", omp_get_thread_num(), start, end);

                if (end != objective) start = end + 1;
                omp_unset_lock(&consumeSem);
            }
        }

        while (workerControl) {
            #pragma single nowait private(localCount, localStart, localEnd)
            {
                if(!omp_test_lock(&consumeSem)) continue;

                localStart = start;
                localEnd = end;
                omp_unset_lock(&generationSem);

                for (int num = localStart; num <= localEnd; num++) {
                    if (isPrime(num)) {
                        localCount++;
                    }
                }

                #pragma critical
                {
                    printf("Resultado na thread [%d] com chunk %d..%d foi %d | parcial %d \n", omp_get_thread_num() , start, end, localCount, primeCount);
                    primeCount += localCount;
                    if (end >= objective) {
                        workerControl = false;
                    }
                }
            }
        }
    }

    printf("Quantidade de números primos encontrados: %d\n", primeCount+1);
    // clock_t endTime = clock();
    // double cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    // printf("\nTempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}
