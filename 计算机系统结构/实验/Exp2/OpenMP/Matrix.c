#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define THREAD_NUM 32

void MatrixGenerate(double *MatSize, int n);

void SerialMatrixMultiply(double *a, double *b, double *c, int n);

void ParallelMatrixMultiply(double *a, double *b, double *c, int n);


int main() {
    int MatrixSize = 1000;
    double *x, *y, *z;
    clock_t StartTime, EndTime;
    for (int i = 0; i < 3; i++) {
        // 初始化
        x = (double *) malloc(sizeof(double) * MatrixSize * MatrixSize);
        y = (double *) malloc(sizeof(double) * MatrixSize * MatrixSize);
        z = (double *) malloc(sizeof(double) * MatrixSize * MatrixSize);
        MatrixGenerate(x, MatrixSize);
        MatrixGenerate(y, MatrixSize);
        printf("[%d * %d Matrix]\n", MatrixSize, MatrixSize);
        // 串行计算
        StartTime = clock();
        SerialMatrixMultiply(x, y, z, MatrixSize);
        EndTime = clock();
        double SerialTime = (double) (EndTime - StartTime) / CLOCKS_PER_SEC;
        printf("Serial Time: %.3lfs\n", SerialTime);
        // 并行计算
        omp_set_num_threads(THREAD_NUM);
        StartTime = clock();
        ParallelMatrixMultiply(x, y, z, MatrixSize);
        EndTime = clock();
        double ParallelTime = (double) (EndTime - StartTime) / CLOCKS_PER_SEC;
        printf("Thread Num: %d\n", THREAD_NUM);
        printf("Parallel Time: %.3lfs\n", ParallelTime);
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
