#include "algebre.h"


void vector_sum(double* x, double* u, double* v, int n)
// Sum of u+v = x
{
    for (int i = 0; i < n; i++) {
        x[i] = u[i] + v[i];
    }
}


void vector_substract(double* x, double* u, double* v, int n)
// Substraction of u-v = x
{
    for (int i = 0; i < n; i++) {
        x[i] = u[i] - v[i];
    }
}


void vector_coef(double* x, double* u, double c, int n)
// Apply coefficient to c*u = x
{
    for (int i = 0; i < n; i++) {
        x[i] = c * u[i];
    }
}


double vector_scalar(double* u, double* v, int n)
// Dot product of u and v
{
    double x = 0;

    for (int i = 0; i < n; i++) {
        x += u[i] * v[i];
    }

    return x;
}