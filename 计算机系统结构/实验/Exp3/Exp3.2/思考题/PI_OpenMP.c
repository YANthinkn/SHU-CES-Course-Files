#include "omp.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

#define N 1000000000
#define THREAD_NUM 6

double OpenMP_PI(int Steps, int ThreadNum);

int main(int argc, char *argv[]) {
    double PI;
    double ParallelStartTime, ParallelEndTime;
    ParallelStartTime = omp_get_wtime();
    PI = OpenMP_PI(N, THREAD_NUM);
    ParallelEndTime = omp_get_wtime();
    double OpenMP_Time = ParallelEndTime - ParallelStartTime;
    printf("\n======OpenMP======\n");
    printf("PI Result: %.20lf\nTime: %.16fs\n", PI, OpenMP_Time);
}

double OpenMP_PI(int Steps, int ThreadNum) {
    double sum;
    double Step = 1.0 / (double) Steps;
    omp_set_num_threads(ThreadNum);
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < Steps; i++) {
        double x = (i + 0.5) * Step;
        sum += 4.0 / (1.0 + x * x);
    }
    return Step * sum;
}

