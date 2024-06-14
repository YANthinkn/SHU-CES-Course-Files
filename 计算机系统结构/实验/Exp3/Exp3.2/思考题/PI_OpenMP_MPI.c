#include "mpi.h"
#include "omp.h"
#include <stdio.h>
#include <math.h>

#define N 1000000000

int main(int argc, char *argv[]) {
    int rank, nproc;
    int i, low, up;
    double local = 0.0, pi, w, temp;
    double StartTime, EndTime;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    StartTime = MPI_Wtime();//记录开始时间
    w = 1.0 / N;
    low = rank * (N / nproc);
    up = low + N / nproc - 1;
#pragma omp parallel for reduction(+:local) private(temp, i)
    for (i = low; i < up; i++) {
        temp = (i + 0.5) * w;
        local = local + 4.0 / (1.0 + temp * temp);
    }
    MPI_Reduce(&local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    EndTime = MPI_Wtime(); // 记录结束时间
    if (rank == 0) {
        printf("\n======OpenMP+MPI======\n");
        printf("PI Result: %.20lf\nTime: %.16fs\n", pi * w, EndTime - StartTime);
    }
    MPI_Finalize();
    return 0;
}
