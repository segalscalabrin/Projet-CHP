#include "differences_finies.h"


void build_rhs_df(double* rhs, double *u, double t, Parameters *para, Fonctions *fonc)
{
    // ----------------------------------------
    // Remplissage de la matrice avec u^n, f(x,y,t)
    // ----------------------------------------
    for (int i=0; i<para->Nx; i++) {
        for (int j=0; j<para->Ny; j++) {
            rhs[j*para->Ny + i] = u[j*para->Ny + i] + para->dt * fonc->f(i*para->dx, j*para->dy, t, para);
        }
    }

    // ----------------------------------------
    // Remplissage des conditions de bord
    // ----------------------------------------
    // Up and down side
    double alpha = para->D * para->dt / (para->dx * para->dx);

    for (int i = 0; i < para->Nx; i++) {
        rhs[i]                         += alpha * fonc->g(i*para->dx, 0, t, para);
        rhs[para->Nx*(para->Ny-1) + i] += alpha * fonc->g(i*para->dx, para->Ly, t, para);
    }

    // Left and right side
    double beta = para->D * para->dt / (para->dy * para->dy);

    for (int j = 0; j < para->Ny; j++) {
        rhs[para->Nx*j]              += beta * fonc->h(0, j*para->dy, t, para);
        rhs[para->Nx*j + para->Nx-1] += beta * fonc->h(para->Lx, j*para->dy, t, para);
    }
}


void matvect_df(double *u_plus_1, double *u, double *rhs, Parameters *para, Fonctions *fonc)
{
    // ----------------------------------------
    // Definition des constante de la matrice
    // ----------------------------------------
    double beta = para->D * para->dt / (para->dx * para->dx);
    double gamma = para->D * para->dt / (para->dy * para->dy);
    double alpha = 1 + 2*alpha + 2*beta;
    
    // ----------------------------------------
    // Produit matrice vecteur 
    // ----------------------------------------
    for (int i=0; i<para->Nx; i++) {
        for (int j=0; j<para->Ny; j++) {
            u_plus_1[j*para->Nx + i] = alpha * u[j*para->Nx + i];
            if (i=!0) {
                u_plus_1[j*para->Nx + i] -= beta * u[j*para->Nx + i - 1];
            }
            if (i=!para->Nx-1) {
                u_plus_1[j*para->Nx + i] -= beta * u[j*para->Nx + i + 1];
            }
            if (j=!0) {
                u_plus_1[j*para->Nx + i] -= gamma * u[j*para->Nx + i - para->Nx];
            }
            if (j=!para->Ny-1) {
                u_plus_1[j*para->Nx + i] -= gamma * u[j*para->Nx + i + para->Nx];
            }
        }
    }
}