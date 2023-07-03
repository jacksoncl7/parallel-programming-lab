## Laboratório de programação paralela
Notas e soluções sobre programação paralela utilizando open-mpi e open-mp


## Estrutura dos diretórios
```
.
├── README.md
├── class_exercises
│   ├── mpi
│   │   ├── README.md
│   │   ├── communication_methods
│   │   │   ├── bsend.c
│   │   │   ├── isend.c
│   │   │   ├── reduce.c
│   │   │   ├── rsend.c
│   │   │   ├── sendrecv.c
│   │   │   └── ssend.c
│   │   ├── hello_world
│   │   │   ├── hello_world_mpi.c
│   │   │   └── hello_world_with_mesages.c
│   │   ├── integral_example
│   │   │   ├── integral_example.c
│   │   │   └── integral_example_w_reduce.c
│   │   └── matrix
│   │       └── mxv.c
│   └── open_mp
│       ├── README.md
│       ├── atomic_graph.c
│       ├── barrier.c
│       ├── copyprivate.c
│       ├── firstprivate.c
│       ├── firstprivate_class_version.c
│       ├── hello_world.c
│       ├── if.c
│       ├── lastprivate.c
│       ├── private_example.c
│       └── shared.c
└── homeworks
    ├── open_mpi_prime_numbers
    │   ├── bag_of_tasks
    │   │   ├── anotações.txt
    │   │   ├── bag_of_tasks_default.c
    │   │   ├── bag_of_tasks_isend_irecv.c
    │   │   ├── bag_of_tasks_isend_recv.c
    │   │   ├── bag_of_tasks_rsend_irecv.c
    │   │   ├── bag_of_tasks_rsend_recv.c
    │   │   ├── bag_of_tasks_send_irecv.c
    │   │   ├── bag_of_tasks_ssend_irecv.c
    │   │   ├── bag_of_tasks_ssend_recv.c
    │   │   ├── build
    │   │   │   ├── default
    │   │   │   ├── isend_irecv
    │   │   │   ├── isend_recv
    │   │   │   ├── rsend_irecv
    │   │   │   ├── rsend_recv
    │   │   │   ├── send_irecv
    │   │   │   ├── ssend_irecv
    │   │   │   └── ssend_recv
    │   │   ├── build.sh
    │   │   ├── build_and_test.sh
    │   │   ├── perf_output.txt
    │   │   ├── perf_output_2.txt
    │   │   └── test.sh
    │   └── naive
    │       ├── build
    │       ├── build.sh
    │       ├── build_and_test.sh
    │       ├── naive_default.c
    │       ├── naive_isend_irecv.c
    │       ├── naive_isend_recv.c
    │       ├── naive_rsend_irecv.c
    │       ├── naive_rsend_recv.c
    │       ├── naive_send_irecv.c
    │       ├── naive_send_recv.c
    │       ├── naive_ssend_irecv.c
    │       ├── naive_ssend_recv.c
    │       ├── perf_out.txt
    │       └── test.sh
    └── openmp_prime_numbers
        ├── bag_of_tasks
        │   ├── bag_final.c
        │   ├── bag_of_tasks.c
        │   ├── bag_of_tasks_sec_prop.c
        │   ├── bag_of_tasks_team_prop.c
        │   ├── build
        │   │   ├── bag_final
        │   │   ├── bag_of_final
        │   │   ├── build.sh
        │   │   ├── build_and_test.sh
        │   │   └── test.sh
        │   ├── build_gustavo.sh
        │   ├── linear_reference
        │   │   ├── brute_force_prime_number.c
        │   │   └── lock_example.c
        │   └── results
        │       ├── bag_of_task_result.json
        │       ├── bag_of_task_result.txt
        │       ├── build-tools
        │       │   ├── perf_outputToJSON.py
        │       │   ├── plotPerfJSON.py
        │       │   ├── plotPerfJSON_Eficiencia.py
        │       │   └── plotPerfJSON_Speedup.py
        │       ├── plot-tools
        │       └── plots_bag_of_tasks
        │           ├── 32_500_000.png
        │           └── 3_250_000.png
        ├── naive
        │   ├── build
        │   ├── mpi_reference
        │   │   ├── naive_mpi
        │   │   └── naive_mpi.c
        │   ├── naive_omp_atomic.c
        │   ├── naive_omp_critical.c
        │   ├── naive_omp_default.c
        │   └── results
        │       ├── 325_000.png
        │       ├── 32_500_000.png
        │       ├── 3_250_000.png
        │       ├── build-tools
        │       │   ├── build.sh
        │       │   ├── build_and_test.sh
        │       │   └── test.sh
        │       ├── perf_output.json
        │       ├── perf_output.txt
        │       ├── perf_output_2.json
        │       ├── perf_output_2.txt
        │       ├── plot-tools
        │       │   ├── perf_outputToJSON.py
        │       │   ├── plotPerfJSON.py
        │       │   └── plotPerfJSON_Eficiencia.py
        │       ├── plots
        │       │   ├── 325_000.png
        │       │   └── 3_250_000.png
        │       ├── plots_2
        │       │   ├── 32_500_000.png
        │       │   └── 3_250_000.png
        │       ├── plots_3
        │       │   ├── 325_000.png
        │       │   ├── 32_500_000.png
        │       │   └── 3_250_000.png
        │       └── plots_4
        │           ├── 325_000.png
        │           ├── 32_500_000.png
        │           └── 3_250_000.png
        └── tests
            └── mpi_compare
                ├── 32_500_000.png
                ├── 3_250_000.png
                ├── assets
                │   └── MPI-PLOTS
                │       ├── bag_of_tasks-32_500_000.png
                │       ├── bag_of_tasks-3_250_000.png
                │       ├── naive-32_500_000.png
                │       └── naive-3_250_000.png
                ├── bag_of_tasks_mpi.json
                ├── bag_of_tasks_mpi.txt
                ├── naive_mpi.json
                └── naive_mpi.txt
```
