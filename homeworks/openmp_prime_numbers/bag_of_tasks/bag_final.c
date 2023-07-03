#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <omp.h>
#include <stdbool.h>

// #define NUMBER_OF_THREADS 8
// #define MAX_NUMBER 1'000'000'000

uint8_t isNumberPrime(int64_t n)
{
	for (int64_t i = 3; i < (int64_t)(sqrt(n) + 1); i+=2)
    {
		if(n%i == 0) return 0;
	}

	return 1;
}

uint64_t computePrimes(int start, int end)
{
    uint64_t primeCount = 0;
    if(start % 2 == 0) start += 1; // accounting for start being even.
    for (int64_t i = start; i <= end; i += 2)
	{
		if(isNumberPrime(i))
        {
            primeCount += 1;
        }
	}
    return primeCount;
}

int main(int argc, char *argv[])
{
    int64_t maxNumber;
    #ifdef MAX_NUMBER
        maxNumber = MAX_NUMBER;    
    #else
        if(argc < 2)
        {
            printf("Parâmetro(s) de entrada inválido(s)! Entre com um valor para o maior inteiro!\n");
            return 0;
        }
        else
        {
            maxNumber = strtol(argv[1], (char **) NULL, 10);
        }
    #endif

    int32_t numberOfThreads;
    #ifdef NUMBER_OF_THREADS
        numberOfThreads = NUMBER_OF_THREADS;
    #else
        if(argc < 3)
        {
            printf("Parâmetro(s) de entrada inválido(s)! Entre com um valor para o número de threads!\n");
            return 0;
        }
        else
        {
            numberOfThreads = strtol(argv[2], (char **) NULL, 10);
        }
    #endif
    int64_t bagSize = 1000;
    int start = 3, end = bagSize + 3;
    int localStart, localEnd;
    
    omp_lock_t estaProduzindo, estaConsumindo;
    bool existeEstoque = true;
    omp_init_lock(&estaProduzindo);
    omp_init_lock(&estaConsumindo);

    (void) omp_set_num_threads(numberOfThreads);

    int64_t primeCount = 0;
    double startingTime = omp_get_wtime();
    #pragma omp parallel shared(start, end, primeCount) private(localStart, localEnd)
    {
        int id = omp_get_thread_num();
        if(id == 0)
        {
            while(end < maxNumber)
            {
                while(existeEstoque) continue;
                omp_set_lock(&estaProduzindo);
                start += bagSize;
                if(start + bagSize > maxNumber)
                {
                    end = maxNumber;
                }
                else
                {
                    end = start + bagSize;
                }

                existeEstoque = true;
                omp_unset_lock(&estaProduzindo);
            }
        }
        else
        {
            while(end < maxNumber)
            {
                while(!omp_test_lock(&estaConsumindo)) continue;
                while(!existeEstoque) continue;
                localStart = start;
                localEnd = end;
                existeEstoque = false;
                omp_unset_lock(&estaConsumindo);
                
                uint64_t localPrimeCount = computePrimes(localStart, localEnd);
                #pragma omp atomic
                primeCount += localPrimeCount;
            }
        }
        #pragma omp barrier
    }
    
    double finishingTime = omp_get_wtime();
    primeCount += 1; // Adds the number '2', which is also prime.
    printf("Quant. de primos entre 1 e n: %ld \n", primeCount);
	printf("Tempo de execucao: %1.3lf \n", finishingTime - startingTime);

    return 0;
}