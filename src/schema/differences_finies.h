#include "include.h"

void build_rhs_df(vector<double> *rhs, vector<double> *u, double t, Parameters *para, Fonctions *fonc, vector<double> *bord_bas, vector<double> *bord_haut);

void matvect_df(vector<double> *x, vector<double> *y, Parameters *para, Fonctions *fonc);