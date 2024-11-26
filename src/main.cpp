#include "init_export/initialisation.h"
#include "main_loop/main_loop.h"


int main(int argc, char *argv[])
{
    Parameters params;
    Fonctions fonctions;
    int cas = stoi(argv[argc - 1]);

    printf("Lecture des paramètres \n\n");
    read_parameters(cas, &params, &fonctions);


    vector<double> u, u_exact;
    u.resize(params.Nx*params.Ny);
    u_exact.resize(params.Nx*params.Ny);

    printf("Résoudre équation \n\n");
    solve_equation(&u, &u_exact, &params, &fonctions);

    return 0;
}