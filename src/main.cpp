#include "init_export/initialisation.h"
#include "main_loop/main_loop.h"
#include "charge/charge.h"
#include "../test/test_params.h"


int main(int argc, char *argv[])
{    
    if (argc>3) {
        check_enter_params(argv[argc - 1], argv[argc - 3], argv[argc - 2]);
    }
    else {
        cerr << "Erreur : Pas assez d'arguments." << endl;
        exit(EXIT_FAILURE);
    }

    printf("Lecture des paramètres \n\n");

    Parameters params;
    Fonctions fonctions;

    int cas = stoi(argv[argc - 1]);
    int Nx = stoi(argv[argc - 3]);
    int Ny = stoi(argv[argc - 2]);
    int recouvrement = stoi(argv[argc - 4]);

    // initialisation de l'environnement parallele
    int me, np;
    MPI_Init(& argc, &argv);
    
    // Rang du proc
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    //Nombre de proc
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int iBeg, iEnd;
    charge(me, Ny, np, &iBeg, &iEnd);

    int Ny_loc(0);
    if (me ==0)
    {
        iEnd = iEnd + recouvrement;
    }
    else if (me == np-1)
    {
        iBeg = iBeg - recouvrement;
    }
    else
    {
        iEnd = iEnd + recouvrement;
        iBeg = iBeg - recouvrement;
    }
    Ny_loc = iEnd - iBeg +1 ;

    read_parameters(cas, Nx, Ny, Ny_loc, iBeg, iEnd, me, np, recouvrement, &params, &fonctions);

    printf("Résolution de l'équation \n\n");

    vector<double> u(params.Nx*params.Ny), u_exact(params.Nx*params.Ny);

    solve_equation(&u, &u_exact, &params, &fonctions);

    MPI_Finalize();
    return 0;
}