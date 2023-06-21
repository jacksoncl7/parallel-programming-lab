#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[]) { /* omp_lastprivate.c  */
int i;
int x = 33;

    time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
//   printf ( "Current local time and ,  );

    // #pragma omp parallel for lastprivate(x) schedule(static, 2) num_threads(4)
    // #pragma omp parallel for lastprivate(x) schedule(dynamic, 2) num_threads(3)
    #pragma omp parallel for lastprivate(x) schedule(guided, 2) num_threads(4)
    for(i = 0; i <= 10; i++){
        x = i;
        printf("Número da thread: %d x: %d  date: %s\n",omp_get_thread_num(), x, asctime (timeinfo));
    }
    printf("x é %d\n", x);
    return(0);
}
