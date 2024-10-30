#include "include/helloworld.h"
#include "include/initialisation.h"


int main(int argc, char *argv[])
{
    Parameters params;
    const string path = argv[argc - 1];

    read_parameters(path, &params);

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &params.nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &params.rang);

    hello(params.rang);

    MPI_Finalize();

    return 0;
}