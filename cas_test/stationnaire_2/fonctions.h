#ifndef FONCTIONS_STATIONNAIRE_2_H
#define FONCTIONS_STATIONNAIRE_2_H

#include "include.h"    

namespace stationnaire_2 {

double f(double x, double y, double t, Parameters *params);
double g(double x, double y, double t, Parameters *params);
double h(double x, double y, double t, Parameters *params);
double sol_exact(double x, double y, double t, Parameters *params);

} 

#endif
