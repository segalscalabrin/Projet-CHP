#include "fonctions.h"

namespace stationnaire_2 {

double f(double x, double y, double t, Parameters *params)
{
    return sin(x) + cos(y);
}

double g(double x, double y, double t, Parameters *params)
{
    return sin(x) + cos(y);
}

double h(double x, double y, double t, Parameters *params)
{
    return sin(x) + cos(y);
}

double sol_exact(double x, double y, double t, Parameters *params)
{
    return sin(x) + cos(y);
}

}