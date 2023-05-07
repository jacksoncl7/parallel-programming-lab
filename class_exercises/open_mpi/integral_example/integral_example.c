#include <stdio.h>
#include <math.h>
#include "mpi.h"

double f(double x) {
        double return_val;
        return_val = exp(x); /* Função exponencial */
        // return_val = x*x; /* Função exponencial */
        return return_val;
}

int main(int argc, char *argv[]) { /* mpi_trapezio.c  */
int my_rank, num_procs;  /* respectivamente q e p */
double a = 0.0,  b = 1.0;   /* Limites da integral */
double start_time, final_time; /* Tempo de execução */
long int n = 1024;     /* Número de trapezoides */
double x, h;                /* x e h, a base do trapezoide */
double integral=0.0, total; /* Integral de cada processo e total */
int origin, dest = 0;    /* origin e dest das mensagens */
int etiq = 3;               /* Uma etiqueta qualquer */

    /* Inicia o MPI e determina o ranque e o número de processos ativos  */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    /* h é o mesmo para todos os processos */
    h = (b - a)/n;
    /* O processo 0 calcula o valor de f(x)/2 em a e b */
    start_time = MPI_Wtime();
    if (my_rank == 0) {
        integral = (f(a) + f(b))/2.0;
    }
    /* Cada processo calcula a integral aprox. sobre n/num_procs trapézios */
    for (x = a+h*(my_rank+1); x < b ; x += num_procs*h) {
         integral += f(x);
    }
    integral = integral*h;
    /* O processo 0 soma as integrais parciais recebidas */
    if (my_rank == 0) {
        total = integral;
        for (origin = 1; origin < num_procs; origin++) {
             MPI_Recv(&integral, 1, MPI_DOUBLE, origin, etiq, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
             total += integral;
        }
    }
     /* Os demais processos enviam as integrais parciais para o processo 0 */
    else {
        final_time = MPI_Wtime();
        MPI_Send(&integral, 1, MPI_DOUBLE, dest, etiq, MPI_COMM_WORLD);
    }
    /* Imprime o resultado */
    if (my_rank == 0) {
        final_time = MPI_Wtime();
        printf("Foram gastos %3.5f segundos\n",final_time-start_time);
        printf("Com n = %ld trapezoides, a estimativa\n", n);
        printf("da integral de %lf até %lf = %lf \n", a, b, total);
        printf("O valor e^1 - 1 = %3.5f", exp(1)-1);
    }
    MPI_Finalize();
    return(0);
}
