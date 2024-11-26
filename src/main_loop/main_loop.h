#include "include.h"
#include "solveur/gradient_biconjugue.h"
#include "init_export/save_sol.h"

void init_equation(vector<double> *u, Parameters *para, Fonctions *fct);

void compute_sol_exact(vector<double> *u_exact, double t, Parameters *para, Fonctions *fct);

double compute_error(vector<double> *u, vector<double> *u_exact, Parameters *para);

void solve_equation(vector<double> *u, vector<double> *u_exact, Parameters *para, Fonctions *fct);