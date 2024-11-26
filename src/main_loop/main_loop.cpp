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


void solve_equation(vector<double> *u, vector<double> *u_exact, Parameters *para, Fonctions *fct)
{
    double t=0;
    vector<double> rhs;
    rhs.resize(u->size());

    init_equation(u, para, fct);

    while (t < para->Tmax) {
        cout << "Avancement " << 100*t/para->Tmax << "%" << endl;

        // Calcul de u^n+1
        build_rhs_df(&rhs, u, t, para, fct);
        gradient_biconjugue(para, fct, t, &rhs, u);

        // Calcul de u exact
        compute_sol_exact(u_exact, t, para, fct);

        // Sauvegarde des solutions et t = t + dt
        t += para->dt;
        save_solution(u, int(t/para->dt), para, false);
        save_solution(u_exact, int(t/para->dt), para, true);

    }
}

/*

        cout << "rhs : " << endl;
        for (int j=para->Ny-1; j>=0; j--) {
            for (int i=0; i<para->Nx; i++) {
                cout << rhs[j*para->Nx + i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        */