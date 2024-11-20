#include "src/init_export/initialisation.h"


int main(int argc, char *argv[])
{
    //MPI_Init(&argc, &argv);
    
    Parameters params;
    Fonctions fonctions;
    int cas = stoi(argv[argc - 1]);

    read_parameters(cas, &params, &fonctions);

    //MPI_Comm_size(MPI_COMM_WORLD, &params.nprocs);
    //MPI_Comm_rank(MPI_COMM_WORLD, &params.rang);

    

    //MPI_Finalize();

    return 0;
}