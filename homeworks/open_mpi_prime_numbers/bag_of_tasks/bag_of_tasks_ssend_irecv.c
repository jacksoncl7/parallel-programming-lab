#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>
#define TAMANHO 500000 // 500_000

int primo(int n)
{
    int i;
	
    for(i = 3;
        i < (int)(sqrt(n) + 1);
        i+=2)
    {
        if(n%i == 0)
            return 0;
	}
	return 1;
}

/* bag_of_tasks_ssend_irecv.c */
int main(int argc, char *argv[])
{
    double t_inicial, t_final;
    int num_primo_cont=0, num_primo_total=0;
    int i, num_primo_max;
    int meu_ranque, num_procs, num_inicial, proc_dest, proc_raiz=0, tag=1, stop=0;
    MPI_Status estado;
    MPI_Request pedido_recebe;

    /* Verifica o número de argumentos passados */
	if(argc < 2)
    {
        printf("Entre com o valor do maior inteiro como parâmetro para o programa.\n");
       	return 0;
    } 
    else 
    {
        num_primo_max = strtol(argv[1], (char **) NULL, 10);
    }
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    /* Se houver menos que dois processos aborta */
    if(num_procs < 2)
    {
        printf("Este programa deve ser executado com no mínimo dois processos.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
       	return(1);
    }
    
    /* Registra o tempo inicial de execução do programa */
    t_inicial = MPI_Wtime();
    
    /* Envia pedaços com TAMANHO números para cada processo */
    if(meu_ranque == 0)
    {
        /* NOTE(Gustavo): caso 'TAMANHO' for muito grande, o programa ficará preso nesse loop.
           Por exemplo, se: 
           * num_primo_max = 1003;
           * TAMANHO = 500;
           * num_procs = 4;
           Como o proc. 0 é o master, ele envia '3' para o proc. 1, '503' para o proc. 2 e então
           sai do loop, já que '1003' não é menor que num_primo_max. Porém, isso faz com que o 
           proc. 3 fique esperando um 'num_inicial', então, ocorre deadlock. */
        for(proc_dest = 1, num_inicial = 3;
            proc_dest < num_procs && num_inicial < num_primo_max;
            proc_dest++, num_inicial += TAMANHO)
        {
            MPI_Ssend(&num_inicial, 1, MPI_INT, proc_dest, tag, MPI_COMM_WORLD);
            // printf("(1o envio) Processo 0 enviou %d para o processo %d\n", num_inicial, proc_dest);
        }
        
        /* Fica recebendo as contagens parciais de cada processo */
        while(stop < (num_procs-1))
        {
		    MPI_Irecv(&num_primo_cont, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &pedido_recebe);
            MPI_Wait(&pedido_recebe, &estado);

            num_primo_total += num_primo_cont;
            proc_dest = estado.MPI_SOURCE;
            // printf("Processo 0 recebeu %d do processo %d\n", num_primo_cont, proc_dest);
            if(num_inicial > num_primo_max) 
            {
                tag = 99;
                stop++;
            }
            // printf("Processos finalizados = %d\n", stop);
            
            /* Envia um novo pedaço com TAMANHO números para o mesmo processo*/
            MPI_Ssend(&num_inicial, 1, MPI_INT, proc_dest, tag, MPI_COMM_WORLD);
            // printf("(envio posterior) Processo 0 enviou %d para %d\n", num_inicial, proc_dest);
            num_inicial += TAMANHO;
        }
    }
    else 
    {
        /* Cada processo escravo recebe o início do espaço de busca */
        while(estado.MPI_TAG != 99)
        {
            // printf("Processo %d está aguardando...\n", meu_ranque);
            MPI_Irecv(&num_inicial, 1, MPI_INT, proc_raiz, MPI_ANY_TAG, MPI_COMM_WORLD, &pedido_recebe);
            MPI_Wait(&pedido_recebe, &estado);
            // printf("Processo %d recebeu %d.\n", meu_ranque, num_inicial);
            if(estado.MPI_TAG != 99)
            {
                for(i = num_inicial, num_primo_cont = 0;
                    i < (num_inicial + TAMANHO) && i < num_primo_max;
                    i+=2)
                {
		            if(primo(i) == 1)
                        num_primo_cont++;
                }
                
                /* Envia a contagem parcial para o processo mestre */
                MPI_Ssend(&num_primo_cont, 1, MPI_INT, proc_raiz, tag, MPI_COMM_WORLD);
            }
        }
        
        /* Registra o tempo final de execução */
        /* NOTE(Gustavo): talvez essa linha seja desnecessária, pois, ao final, o processo 0 é o que
           realiza o cálculo do tempo tomado. */
        t_final = MPI_Wtime();
    }
    
	if(meu_ranque == 0)
    {
		t_final = MPI_Wtime();
        num_primo_total += 1;    /* Acrescenta o 2, que é primo */
		printf("Quant. de primos entre 1 e %d: %d \n", num_primo_max, num_primo_total);
		printf("Tempo de execucao: %1.3f \n", t_final - t_inicial);
	}

    /* Finaliza o programa */
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
}