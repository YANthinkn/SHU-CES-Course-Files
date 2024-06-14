#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_THREADS 16

void MatrixGenerate(double *MatSize, int n);

void SerialMatrixMultiply(double *a, double *b, double *c, int n);

void ParallelMatrixMultiply(double *a, double *b, double *c, int n);


int main() {
    int MatrixSize = 1000;
    double *x, *y, *z;
    struct timespec StartTime;
    struct timespec EndTime;
    for (int i = 0; i < 3; i++) {
        // 初始化
        x = (double *) malloc(sizeof(double) * MatrixSize * MatrixSize);
        y = (double *) malloc(sizeof(double) * MatrixSize * MatrixSize);
        z = (double *) malloc(sizeof(double) * MatrixSize * MatrixSize);
        MatrixGenerate(x, MatrixSize);
        MatrixGenerate(y, MatrixSize);
        printf("[%d * %d Matrix]\n", MatrixSize, MatrixSize);
        // 串行计算
        clock_gettime(CLOCK_REALTIME, &StartTime);
        SerialMatrixMultiply(x, y, z, MatrixSize);
        clock_gettime(CLOCK_REALTIME, &EndTime);
        long SerialTime = 1000000*(EndTime.tv_sec - StartTime.tv_sec) + (EndTime.tv_nsec - StartTime.tv_nsec) / 1000;
        printf("Serial Time: %.3lfms\n", SerialTime);
        // 并行计算
        omp_set_num_threads(NUM_THREADS);
        clock_gettime(CLOCK_REALTIME, &StartTime);
        ParallelMatrixMultiply(x, y, z, MatrixSize);
        clock_gettime(CLOCK_REALTIME, &EndTime);
        long ParallelTime = 1000000*(EndTime.tv_sec - StartTime.tv_sec) + (EndTime.tv_nsec - StartTime.tv_nsec) / 1000;
        printf("Parallel Time: %.3lfms\n", ParallelTime);
        printf("Speedup: %.3lf\n\n", SerialTime / ParallelTime);
        // 重置参数
        free(x);
        free(y);
        free(z);
        MatrixSize += 1000; // 更新矩阵尺寸
    }
    return 0;
}

void MatrixGenerate(double *MatSize, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            MatSize[i * n + j] = (double) rand() / RAND_MAX;
        }
    }
}

void SerialMatrixMultiply(double *a, double *b, double *c, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double t = 0;
            for (int k = 0; k < n; k++) {
                t += (double) a[i * n + k] * b[k * n + j];
            }
            c[i * n + j] = t;
        }
    }
}

void ParallelMatrixMultiply(double *a, double *b, double *c, int n) {
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double t = 0;
            for (int k = 0; k < n; k++) {
                t += (double) a[i * n + k] * b[k * n + j];
            }
            c[i * n + j] = t;
        }
    }
}