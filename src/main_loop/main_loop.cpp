#include "main_loop.h"


void init_equation(vector<double> *u, vector<double> *rhs, Parameters *para, Fonctions *fct)
{
    rhs->resize(u->size());

    for(int i=0; i<para->Nx; i++) {
        for(int j=0; j<para->Ny; j++) {
            (*u)[j*para->Ny + i] = 0.0;
        }
    }
}


void solve_equation(vector<double> *u, Parameters *para, Fonctions *fct)
{
    double t=0;
    vector<double> rhs;

    init_equation(u, &rhs, para, fct);

    while (t < para->Tmax) {
        build_rhs_df(&rhs, u, t, para, fct);
        gradient_biconjugue(para, fct, t, &rhs, u);
        t += para->dt;
        save_solution(u, int(t/para->dt), para, false);
    }
}