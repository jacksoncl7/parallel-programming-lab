#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the qt of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int process_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    char mesage[100];
    MPI_Status status;
    int destiny, origin, tag=0;

    if (process_rank != 0)
    {
        sprintf(mesage, "Processo % d está vivo !", process_rank);
        destiny = 0;
        MPI_Send(mesage, strlen(mesage) + 1, MPI_CHAR, destiny, tag, MPI_COMM_WORLD);
    }
    else
    {
        for (origin = 1; origin < world_size; origin++)
        {
            MPI_Recv(mesage, 100, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            printf("%s\n", mesage);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
