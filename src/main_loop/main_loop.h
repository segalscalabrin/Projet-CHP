#include "include.h"
#include "../solveur/gradient_biconjugue.h"
#include "../init_export/save_sol.h"


void init_equation(vector<double> *u, vector<double> *rhs, Parameters *para, Fonctions *fct);

void solve_equation(vector<double> *u, Parameters *para, Fonctions *fct);