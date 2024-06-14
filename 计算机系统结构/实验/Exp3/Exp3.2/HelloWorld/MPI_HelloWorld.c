#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size, rank;
    char ProcessorName[MPI_MAX_PROCESSOR_NAME];
    int NameLength;
    MPI_Init(0, 0);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(ProcessorName, &NameLength);
    printf("Hello World from Processor %s,Rank %d,Out of %d Processors.\n", ProcessorName, rank, size);
    MPI_Finalize();
    return 0;
}
