## Laboratório de programação paralela
Notas e soluções sobre programação paralela utilizando open-mpi e open-mp


## Estrutura dos diretórios
```
.
├── README.md
├── class_exercises
│   └── open_mpi
│       ├── README.md
│       ├── communication_methods
│       │   ├── bsend.c
│       │   ├── isend.c
│       │   ├── reduce.c
│       │   ├── rsend.c
│       │   ├── sendrecv.c
│       │   └── ssend.c
│       ├── hello_world
│       │   ├── hello_world_mpi.c
│       │   └── hello_world_with_mesages.c
│       ├── integral_example
│       │   ├── integral_example.c
│       │   └── integral_example_w_reduce.c
│       └── matrix
│           └── mxv.c
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
        │   └── test.sh
        ├── experiments
        └── naive
            ├── build
            │   ├── naive_default_build
            │   ├── naive_isend_irecev_build
            │   ├── naive_isend_recev_build
            │   ├── naive_send_irecev_build
            │   ├── naive_send_recev_build
            │   └── testing_build
            ├── naive_default.c
            ├── naive_isend_irecev.c
            ├── naive_isend_recev.c
            ├── naive_send_irecev.c
            └── naive_send_recev.c
```
