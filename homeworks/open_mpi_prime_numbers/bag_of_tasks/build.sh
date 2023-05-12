mpicc bag_of_tasks_default.c -o3 -lm -o build/default
mpicc bag_of_tasks_send_irecv.c -o3 -lm -o build/send_irecv
mpicc bag_of_tasks_isend_recv.c -o3 -lm -o build/isend_recv
mpicc bag_of_tasks_isend_irecv.c -o3 -lm -o build/isend_irecv
mpicc bag_of_tasks_rsend_recv.c -o3 -lm -o build/rsend_recv