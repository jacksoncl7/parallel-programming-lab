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
    if (argc != 3 || !isInteger(argv[1]) || !isInteger(argv[2])) {
        printf("Uso: ./bag_of_tasks <objetivo> <Numero de Threads>\n");
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
    int bagSize = 20;

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

    double startingTime = omp_get_wtime();
    omp_init_lock(&generationSem);
    omp_init_lock(&consumeSem);

    #pragma omp parallel
    {
        #pragma omp master
        {
            while (end != objective){
                end = start + chunkSize;
                if (end > objective) { end = objective; }
                printf("\nMaster [%d] criou um novo chunk %d..%d\n", omp_get_thread_num(), start, end);

                while(!omp_test_lock(&generationSem)) {
                    continue;
                }
                if (end != objective) start = end + 1;
                omp_unset_lock(&consumeSem);
            }
        }

        while (end != objective) {
            if  (end == 0) continue;

            #pragma single nowait private(localCount)
            {
                if(!omp_test_lock(&consumeSem)) continue;
                omp_test_lock(&generationSem);
                localCount = 0;
                for (int num = start; num <= end; num++) {
                    if (isPrime(num)) {
                        localCount++;
                    }
                }
                #pragma omp atomic
                primeCount += localCount;

                printf("\nResultado na thread [%d] com chunk %d..%d foi %d \n", omp_get_thread_num() , start, end, localCount, primeCount);
                omp_unset_lock(&generationSem);
            }
        }
    }

    double finishingTime = omp_get_wtime();
    primeCount += 1; // Adds the number '2', which is also prime.
    printf("Quant. de primos entre 1 e n: %ld \n", primeCount);
	printf("Tempo de execucao: %1.3lf \n", finishingTime - startingTime);

    return 0;
}
