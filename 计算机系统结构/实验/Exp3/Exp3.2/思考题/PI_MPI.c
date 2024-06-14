#include "mpi.h"
#include <stdio.h>
#include <math.h>

#define N 1000000000

int main(int argc, char *argv[]) {
    int myid, np, i, j;
    int tag = 666;
    double pi = 0.0;
    double fVal; //fVal代表取Xi所对应的函数值   4/(1+x^2) 即每个矩形的高度
    double h = (double) 1 / N; //每个矩形的宽度
    double local = 0.0; //每个进程计算的面积和
    double StartTime, EndTime;
    double xi;
    MPI_Status status;
    MPI_Init(&argc, &argv); //启动并行程序
    MPI_Comm_size(MPI_COMM_WORLD, &np); //获取进程总数
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); //获取当前进程号
    StartTime = MPI_Wtime(); //记录开始时间
    for (i = myid; i < N; i += np) //利用np个进程同时计算各部分矩形面积
    {
        xi = (i + 0.5) * h;
        fVal = 4.0 / (1.0 + xi * xi); //得到f(xi)
        local += fVal;
    }
    local = local * h; //得到该进程所计算的面积

    //进程号！=0的进程计算的结果发送到进程0上面
    if (myid != 0) {
        MPI_Send(&local, 1, MPI_DOUBLE, 0, myid, MPI_COMM_WORLD);
    }
    if (myid == 0) //进程号为0就累加每个进程的计算结果
    {
        pi = local;//得到进程0的值 后面接收就会覆盖这个值
        for (j = 1; j < np; j++) {
            MPI_Recv(&local, 1, MPI_DOUBLE, j, j, MPI_COMM_WORLD, &status); //把其他进程的结果发送到local中
            pi += local;//得到所有的面积和
        }
    }
    EndTime = MPI_Wtime();//结束计算时间
    if (myid == 0) {
        printf("\n======MPI======\n");
        printf("PI Result: %.20lf\nTime: %.16fs\n", pi, EndTime - StartTime);
    }
    MPI_Finalize();
    return 0;
}