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
    └── open_mpi_prime_numbers
        ├── bag_of_tasks
        │   ├── anotações.txt
        │   ├── bag_of_tasks_default.c
        │   ├── bag_of_tasks_isend_irecv.c
        │   ├── bag_of_tasks_isend_recv.c
        │   ├── bag_of_tasks_rsend_irecv.c
        │   ├── bag_of_tasks_rsend_recv.c
        │   ├── bag_of_tasks_send_irecv.c
        │   ├── bag_of_tasks_ssend_irecv.c
        │   ├── bag_of_tasks_ssend_recv.c
        │   ├── build
        │   │   ├── default
        │   │   ├── isend_irecv
        │   │   ├── isend_recv
        │   │   ├── rsend_irecv
        │   │   ├── rsend_recv
        │   │   ├── send_irecv
        │   │   ├── ssend_irecv
        │   │   └── ssend_recv
        │   ├── build.sh
        │   ├── build_and_test.sh
        │   ├── perf_output.txt
        │   ├── perf_output_2.txt
        │   └── test.sh
        └── naive
            ├── build
            ├── build.sh
            ├── build_and_test.sh
            ├── naive_default.c
            ├── naive_isend_irecv.c
            ├── naive_isend_recv.c
            ├── naive_rsend_irecv.c
            ├── naive_rsend_recv.c
            ├── naive_send_irecv.c
            ├── naive_send_recv.c
            ├── naive_ssend_irecv.c
            ├── naive_ssend_recv.c
            ├── perf_out.txt
            └── test.sh
```
