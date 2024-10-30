#include "include/helloworld.h"


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rang;
    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    hello(rang);

    MPI_Finalize();

    return 0;
}