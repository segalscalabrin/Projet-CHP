#include "main_loop.h"


void init_equation(vector<double> *u, Parameters *para, Fonctions *fct)
{
    for(int j=0; j<para->Ny; j++) {
        for(int i=0; i<para->Nx; i++) {
            (*u)[j*para->Nx + i] = (para->dx*i)*(para->dx*i) + (para->dy*j)*(para->dy*j);
        }
    }
}


void compute_sol_exact(vector<double> *u_exact, double t, Parameters *para, Fonctions *fct)
{
    for(int j=0; j<para->Ny; j++) {
        for(int i=0; i<para->Nx; i++) {
            (*u_exact)[j*para->Nx + i] = fct->sol_exact(para->xmin + i*para->dx, para->ymin + j*para->dy, t, para);
        }
    }   
}


double compute_error(vector<double> *u, vector<double> *u_exact, Parameters *para)
{
    double error(0);
    for(int k=0; k<para->Nx*para->Ny; k++) {
        error += ((*u)[k] - (*u_exact)[k])*((*u)[k] - (*u_exact)[k]);
    }

    return error/(para->Nx*para->Ny);
}


void solve_equation(vector<double> *u, vector<double> *u_exact, Parameters *para, Fonctions *fct)
{
    int k(0);
    double t(0);
    vector<double> rhs;
    vector<double> error;
    rhs.resize(u->size());

    init_equation(u, para, fct);
    compute_sol_exact(u_exact, t, para, fct);

    error.push_back(compute_error(u, u_exact, para));

    save_solution(u, k, para, false);
    save_solution(u_exact, k, para, true);

    cout << "Avancement 0%" << endl;

    while (t < para->Tmax) {
        // t = t + dt
        t += para->dt;
        k += 1;
        cout << "Avancement " << 100*t/para->Tmax << "%" << endl;

        // Calcul de u^n+1
        build_rhs_df(&rhs, u, t, para, fct);
        gradient_biconjugue(para, fct, t, &rhs, u);

        // Calcul de u exact
        compute_sol_exact(u_exact, t, para, fct);

        // Calcul de l'erreur quadratique moyenne   
        error.push_back(compute_error(u, u_exact, para));

        // Sauvegarde des solutions et 
        save_solution(u, k, para, false);
        save_solution(u_exact, k, para, true);
    }
    save_error(&error, para);
}
