#include "initialisation.h"


void init_domaine(Parameters *param, int Nx, int Ny, int recou, int me, int np)
{
    param->Nx = Nx;
    param->Ny_global = Ny;
    param->recouvrement = recou;
    param->me = me;
    param->np = np;

    int iBeg, iEnd;
    charge(me, Ny, np, &iBeg, &iEnd);

    int Ny_loc(0);
    if (me == 0)
    {
        iEnd = iEnd + recou;
    }
    else if (me == np-1)
    {
        iBeg = iBeg - recou;
    }
    else
    {
        iEnd = iEnd + recou;
        iBeg = iBeg - recou;
    }
    Ny_loc = iEnd - iBeg + 1;

    param->Ny = Ny_loc;
    param->iBeg = iBeg;
    param->iEnd = iEnd;
}


void initialisation(int *argc, char ***argv, Parameters *param, Fonctions *fct)
{
    // -------------------------------------------------------- //
    //                 Initialisation de MPI

    int me, np;
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    // -------------------------------------------------------- //
    //                 Recuperation des parametres d'entrees
    int cas = stoi((*argv)[(*argc) - 1]);
    int Nx  = stoi((*argv)[(*argc) - 3]);
    int Ny  = stoi((*argv)[(*argc) - 2]);
    int recouvrement = stoi((*argv)[(*argc) - 4]);

    // -------------------------------------------------------- //
    //                 Initialisation des domaines parallele
    init_domaine(param, Nx, Ny, recouvrement, me, np);

    // -------------------------------------------------------- //
    //                 Initialisation des parametres

    read_parameters(cas, param, fct);
}