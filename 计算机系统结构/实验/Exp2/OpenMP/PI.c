#include <stdio.h>
#include <time.h>
#include <omp.h>

#define THREAD_NUM 4
static long num_steps = 100000;

double SerialPI(int Steps);

double ParallelPI_1(int Steps);

double ParallelPI_2(int Steps);

double ParallelPI_3(int Steps);

double ParallelPI_4(int Steps, int ThreadNum);

int main() {
    int Steps = 1000000000;
    double PI;
    clock_t SerialStartTime, SerialEndTime;

    SerialStartTime = clock();
    PI = SerialPI(Steps);
    SerialEndTime = clock();
    double t0 = (double) (SerialEndTime - SerialStartTime) / CLOCKS_PER_SEC;
    // 串行方法
    printf("======Serial======\n");
    printf("PI Result: %.16lf\nTime: %.16fs\n", PI, t0);
    // 并行方法1
    double ParallelStartTime, ParallelEndTime;
    ParallelStartTime = omp_get_wtime();
    PI = ParallelPI_1(Steps);
    ParallelEndTime = omp_get_wtime();
    double t1 = ParallelEndTime - ParallelStartTime;
    printf("\n======Parallel 1======\n");
    printf("PI Result: %.16lf\nTime: %.16fs\n", PI, t1);
    // 并行方法2
    ParallelStartTime = omp_get_wtime();
    PI = ParallelPI_2(Steps);
    ParallelEndTime = omp_get_wtime();
    double t2 = ParallelEndTime - ParallelStartTime;
    printf("\n======Parallel 2======\n");
    printf("PI Result: %.16lf\nTime: %.16fs\n", PI, t2);
    // 并行方法3
    ParallelStartTime = omp_get_wtime();
    ParallelPI_3(Steps);
    ParallelEndTime = omp_get_wtime();
    double t3 = ParallelEndTime - ParallelStartTime;
    printf("\n======Parallel 3======\n");
    printf("PI Result: %.16lf\nTime: %.16fs\n", PI, t3);
    // 并行方法4（测试THREAD_NUM情况）
//    ParallelStartTime = omp_get_wtime();
//    ParallelPI_4(Steps,THREAD_NUM);
//    ParallelEndTime = omp_get_wtime();
//    double t4 = ParallelEndTime - ParallelStartTime;
//    printf("\n======Parallel 4======\n");
//    printf("PI Result: %.16lf\nTime: %.16fs\n", PI, t4);
    printf("\n======Parallel 4======\n");
    for (int i = 1; i <= 2048; i *= 2) {
        ParallelStartTime = omp_get_wtime();
        PI = ParallelPI_4(Steps, i);
        ParallelEndTime = omp_get_wtime();
        double t4 = ParallelEndTime - ParallelStartTime;
        printf("[Thread Num:%d]\n", i);
        printf("PI Result: %.16lf\nTime: %.16fs\nSpeedup: %.6f\n", PI, t4, t0 / t4);
    }
}

double SerialPI(int Steps) {
    double sum = 0.0;
    double Step = 1.0 / (double) Steps;
    for (int i = 0; i < Steps; i++) {
        double x = (i + 0.5) * Step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    return Step * sum;
}


double ParallelPI_1(int Steps) {
    int i;
    double sum[THREAD_NUM * 16]; // 目的：减少False Sharing，实现加速比>1
    double result = 0.0;
    double Step = 1.0 / (double) Steps;
    omp_set_num_threads(THREAD_NUM);
#pragma omp parallel private(i)
    {
        double x;
        int id = omp_get_thread_num();
        for (i = id, sum[id] = 0.0; i < Steps; i += THREAD_NUM) {
            x = (i + 0.5) * Step;
            sum[id * 16] += 4.0 / (1.0 + x * x);
        }
    }
    for (i = 0; i < THREAD_NUM; ++i) {
        result += sum[i * 16];
    }
    return result * Step;
}


double ParallelPI_2(int Steps) {
    double sum[THREAD_NUM * 16]; // 目的：减少False Sharing，实现加速比>1
    double result = 0.0;
    double Step = 1.0 / (double) Steps;
    omp_set_num_threads(THREAD_NUM);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        sum[id] = 0.0;
#pragma omp for
        for (int i = 0; i < Steps; i++) {
            double x = (i + 0.5) * Step;
            sum[id * 16] += 4.0 / (1.0 + x * x);
        }
    }
    for (int i = 0; i < THREAD_NUM; ++i) {
        result += sum[i * 16];
    }
    return result * Step;
}


double ParallelPI_3(int Steps) {
    int i;
    double sum;
    double result = 0.0;
    double Step = 1.0 / (double) Steps;
    omp_set_num_threads(THREAD_NUM);
#pragma omp parallel private(sum, i)
    {
        int id = omp_get_thread_num();
        sum = 0.0;
        for (i = id; i < Steps; i += THREAD_NUM) {
            double x = (i + 0.5) * Step;
            sum += 4.0 / (1.0 + x * x);
        }
#pragma omp critical
        result += sum;
    };
    return result * Step;
}


double ParallelPI_4(int Steps, int ThreadNum) {
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