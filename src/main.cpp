#include "init_export/initialisation.h"
#include "main_loop/main_loop.h"

#include "charge/charge.h"

#include "../test/test_params.h"


int main(int argc, char **argv)
{    
    // -------------------------------------------------------- //
    //                      Initialisation
    Parameters param;
    Fonctions fct;

    initialisation(&argc, &argv, &param, &fct);

    // -------------------------------------------------------- //
    if (param.me==0) {cout << "Resolution de l'equation" << endl;}
    // -------------------------------------------------------- //

    // -------------------------------------------------------- //
    //                      Resolution de l'equation
    vector<double> u(param.Nx*param.Ny), u_exact(param.Nx*param.Ny);

    solve_equation(&u, &u_exact, &param, &fct);

    MPI_Finalize();
    return 0;
}