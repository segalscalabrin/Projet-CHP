#include "src/init_export/initialisation.h"
#include "src/main_loop/main_loop.h"


int main(int argc, char *argv[])
{
    //MPI_Init(&argc, &argv);
    
    Parameters *params(0);
    Fonctions *fonctions(0);
    int cas = stoi(argv[argc - 1]);

    printf ("lecture des paramètres \n");
    read_parameters(cas, params, fonctions);

    vector<double> u;
    u.resize(params->Nx*params->Ny);

    solve_equation(&u, params, fonctions);


    //MPI_Comm_size(MPI_COMM_WORLD, &params.nprocs);
    //MPI_Comm_rank(MPI_COMM_WORLD, &params.rang);

    

    //MPI_Finalize();

    return 0;
}