#ifndef FONCTIONS_PERSONNALISE_H
#define FONCTIONS_PERSONNALISE_H

#include "include.h"    

namespace personnalise {

double f(double x, double y, double t, Parameters *params);
double g(double x, double y, double t, Parameters *params);
double h(double x, double y, double t, Parameters *params);
double sol_exact(double x, double y, double t, Parameters *params);

} 

#endif
