#include "include.h"

void build_rhs_df(double* rhs, double *u, double t, Parameters *para, Fonctions *fonc);

void matvect_df(double *u_plus_1, double *u, double *rhs, Parameters *para, Fonctions *fonc);