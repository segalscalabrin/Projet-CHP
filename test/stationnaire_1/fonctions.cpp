#include "fonctions.h"

namespace stationnaire_1 {

double f(double x, double y, double t, Parameters *params)
{
    return 2*(x-x*x + y-y*y);
}

double g(double x, double y, double t, Parameters *params)
{
    return 0;
}

double h(double x, double y, double t, Parameters *params)
{
    return 0;
}

}