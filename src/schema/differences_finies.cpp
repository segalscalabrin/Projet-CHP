#include "differences_finies.h"


void build_rhs_df(vector<double> *rhs, vector<double> *u, double t, Parameters *para, Fonctions *fonc, vector<double> *bord_bas, vector<double> *bord_haut)
{
    // Verif OK pour remplissage u et f a verif avec CL
    // ----------------------------------------
    // Remplissage de la matrice avec u^n, f(x,y,t)
    // ----------------------------------------
    for (int j=0; j<para->Ny; j++) {
        for (int i=0; i<para->Nx; i++) {
            (*rhs)[j*para->Nx + i] = (*u)[j*para->Nx + i] + para->dt * fonc->f(i*para->dx, j*para->dy, t, para);
        }
    }

    // ----------------------------------------
    // Remplissage des conditions de bord
    // ----------------------------------------

    // Up and down side
    double alpha = para->D * para->dt / (para->dx * para->dx);

    if (para->me == 0)
    {
        for (int i = 0; i < para->Nx; i++) 
        {
            //cout << (*bord_haut)[i] << endl;
            // bas
            (*rhs)[i]                             += alpha * fonc->g(i*para->dx, 0, t, para);
            //haut
            (*rhs)[para->Nx*(para->Ny-1) + i] += alpha * (*bord_haut)[i]; 
        }
    }
    else if (para->me == para->np-1)
    {
        for (int i = 0; i < para->Nx; i++) 
        {
            (*rhs)[i]                             += alpha * (*bord_bas)[i];
            (*rhs)[para->Nx*(para->Ny-1) + i] += alpha * fonc->g(i*para->dx, para->Ly, t, para);
        }
    }
    else
    {
        for (int i = 0; i < para->Nx; i++) 
        {
            (*rhs)[i]                             += alpha * (*bord_bas)[i];
            (*rhs)[para->Nx*(para->Ny-1) + i] += alpha * (*bord_haut)[i];
        }
    }

    /*for (int i = 0; i < para->Nx; i++) {
        (*rhs)[i]                         += alpha * fonc->g(i*para->dx, 0, t, para);
        (*rhs)[para->Nx*(para->Ny-1) + i] += alpha * fonc->g(i*para->dx, para->Ly, t, para);
    }*/

    // Left and right side
    double beta = para->D * para->dt / (para->dy * para->dy);

    for (int j = 0; j < para->Ny; j++) {
        (*rhs)[para->Nx*j]              += beta * fonc->h(0, j*para->dy, t, para);
        (*rhs)[para->Nx*j + para->Nx-1] += beta * fonc->h(para->Lx, j*para->dy, t, para);
    }
}


void matvect_df(vector<double> *x, vector<double> *y, Parameters *para, Fonctions *fonc)
{
    // ----------------------------------------
    // Definition des constante de la matrice
    // ----------------------------------------
    double beta = para->D * para->dt / (para->dx * para->dx);
    double gamma = para->D * para->dt / (para->dy * para->dy);
    double alpha = 1 + 2*beta + 2*gamma;
    
    // ----------------------------------------
    // Produit matrice vecteur 
    // ----------------------------------------
    for (int i=0; i<para->Nx; i++) {
        for (int j=0; j<para->Ny; j++) {
            (*y)[j*para->Nx + i] = alpha * (*x)[j*para->Nx + i];
            if (i!=0) {
                (*y)[j*para->Nx + i] -= beta * (*x)[j*para->Nx + i - 1];
            }
            if (i!=(para->Nx-1)) {
                (*y)[j*para->Nx + i] -= beta * (*x)[j*para->Nx + i + 1];
            }
            if (j!=0) {
                (*y)[j*para->Nx + i] -= gamma * (*x)[j*para->Nx + i - para->Nx];
            }
            if (j!=(para->Ny-1)) {
                (*y)[j*para->Nx + i] -= gamma * (*x)[j*para->Nx + i + para->Nx];
            }
        }
    }
}