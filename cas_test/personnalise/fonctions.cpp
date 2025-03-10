#include "fonctions.h"

namespace personnalise {

double f(double x, double y, double t, Parameters *params)
{
    return exp(-(x - params->Lx / 2) * (x - params->Lx / 2)) *
           exp(-(y - params->Ly / 2) * (y - params->Ly / 2)) *
           cos(acos(-1) * t / 2);
}

double g(double x, double y, double t, Parameters *params)
{
    return sol_exact(x, y, t, params);
}

double h(double x, double y, double t, Parameters *params)
{
    return sol_exact(x, y, t, params);
}

double sol_exact(double x, double y, double t, Parameters *params)
{
    return exp(-(x - params->Lx / 2) * (x - params->Lx / 2)) *
           exp(-(y - params->Ly / 2) * (y - params->Ly / 2)) *
           cos(acos(-1) * t / 2);
}

} 