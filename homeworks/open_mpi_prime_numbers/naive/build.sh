mpicc naive_default.c -o3 -lm -o build/default
mpicc naive_send_irecv.c -o3 -lm -o build/send_irecv
mpicc naive_isend_recv.c -o3 -lm -o build/isend_recv
mpicc naive_isend_irecv.c -o3 -lm -o build/isend_irecv
mpicc naive_rsend_recv.c -o3 -lm -o build/rsend_recv
mpicc naive_rsend_irecv.c -o3 -lm -o build/rsend_irecv
mpicc naive_ssend_recv.c -o3 -lm -o build/ssend_recv
mpicc naive_ssend_irecv.c -o3 -lm -o build/ssend_irecv
