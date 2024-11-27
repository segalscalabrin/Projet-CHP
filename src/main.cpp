#include "init_export/initialisation.h"
#include "main_loop/main_loop.h"


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

    read_parameters(cas, Nx, Ny, &params, &fonctions);

    printf("Résolution de l'équation \n\n");

    vector<double> u, u_exact;
    u.resize(params.Nx*params.Ny);
    u_exact.resize(params.Nx*params.Ny);

    solve_equation(&u, &u_exact, &params, &fonctions);

    return 0;
}