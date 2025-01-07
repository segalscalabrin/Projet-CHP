#include "main_loop.h"

void init_equation(vector<double> *u, Parameters *para, Fonctions *fct)
{
    for(int j=0; j<para->Ny; j++) {
        for(int i=0; i<para->Nx; i++) {
            (*u)[j*para->Nx + i] = 1;
        }
    }
}


void solve_equation(vector<double> *u, vector<double> *u_exact, Parameters *para, Fonctions *fct)
{
    int k(0);
    double t(0);
    vector<double> rhs;
    vector<double> error;

    rhs.resize(u->size());

    init_equation(u, para, fct);
    save_solution(u, k, para, false);

    double start_time, end_time; // Variables pour mesurer le temps

    // -------------------------------------------------------- //
    if (para->me==0) {cout << "Avancement 0%" << endl;}
    // -------------------------------------------------------- //

    start_time = MPI_Wtime();

    while (t < para->Tmax) {
        t += para->dt;
        k += 1;

        // -------------------------------------------------------- //
        if (para->me==0) {cout << "Avancement " << 100*t/para->Tmax << "%" << endl;}
        // -------------------------------------------------------- //

        // Calcul de u^n+1
        build_rhs_df(&rhs, u, t, para, fct);
        
        gradient_biconjugue(para, fct, t, &rhs, u);
    
        // Sauvegarde des solutions 
        save_solution(u, k, para, false);
    }

    end_time = MPI_Wtime();

    if (para->me == 0) {
        std::cout << "Temps total d'exécution : " << (end_time - start_time) << " secondes." << std::endl;
    }
}
