#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) { /* omp_firstprivate.c  */
int a[4] = {1, 1, 1, 1};
int b[4] = {0, 0, 0, 0};
int myid, neighb, n = 2;

    omp_set_num_threads(4);

    // a = (int *) malloc(omp_get_num_threads()*sizeof(int));
    // b = (int *) malloc(omp_get_num_threads()*sizeof(int));


/* Prepara os parâmetros para a computação e aloca memória */
#pragma omp parallel private(myid, neighb)
{
    myid = omp_get_thread_num();
    neighb = myid - 1;
    if (myid == 0) {
        neighb = omp_get_num_threads() - 1;
    }

    a[myid] = a[myid] * 3;

    # pragma omp barrier

    b[myid] = a[neighb] + 2;
} /*-- Final de região paralela --*/

    printf("Saida de B\n");
    for(int j=0; j < 4; j++) {
        printf("%d ", b[j]);
    }
    printf("\n");
   return(0);
}
