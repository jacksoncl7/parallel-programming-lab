#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool isPrime(int num) {
    if (num <= 1)
        return false;

    if (num == 2)
        return true;

    if (num % 2 == 0)
        return false;

    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0)
            return false;
    }

    return true;
}

int countPrimes(int n) {
    int count = 0;
    for (int num = 2; num <= n; num++) {
        if (isPrime(num))
            count++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: ./count_primes <numero>\n");
        return 1;
    }

    int n = atoi(argv[1]);

    clock_t start = clock();

    int primeCount = countPrimes(n);

    clock_t end = clock();

    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Quantidade de números primos encontrados até %d: %d\n", n, primeCount);
    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}
