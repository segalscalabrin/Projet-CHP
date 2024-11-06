#include "include/helloworld.h"
#include "include/initialisation.h"


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    
    Parameters params;
    int cas = stoi(argv[argc - 1]);

    read_parameters(cas, &params);

    MPI_Comm_size(MPI_COMM_WORLD, &params.nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &params.rang);

    hello(params.Cas);

    MPI_Finalize();

    return 0;
}