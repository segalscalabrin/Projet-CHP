#include "differences_finies.h"

#include <unistd.h>

void build_rhs_df(vector<double> *rhs, vector<double> *u, double t, Parameters *para, Fonctions *fonc)
{
    // Verif OK pour remplissage u et f a verif avec CL
    // ----------------------------------------
    // Remplissage de la matrice avec u^n, f(x,y,t)
    // ----------------------------------------
    for (int j=0; j<para->Ny; j++) {
        for (int i=0; i<para->Nx; i++) {
            (*rhs)[j*para->Nx + i] = (*u)[j*para->Nx + i] + para->dt * fonc->f(i*para->dx, (j+para->iBeg)*para->dy, t, para);
        }
    }

    // ----------------------------------------
    // Remplissage des conditions de bord
    // ----------------------------------------

    // Left and right side
    double dx = para->D * para->dt / (para->dx * para->dx);
    // Up and down side
    double dy = para->D * para->dt / (para->dy * para->dy);


    // ----------------------------------------
    //        Send
    // ----------------------------------------

    MPI_Request send_request[2], recv_request[2]; 
    int send_request_count = 0, recv_request_count = 0;       

    // 1. Envois
    if (para->me != para->np - 1) {
        MPI_Isend(&(*u)[para->Nx * (para->Ny - 1 - 2 * para->recouvrement)], 
                3 * para->Nx, MPI_DOUBLE, para->me + 1, para->Ny_global + para->me + 1, 
                MPI_COMM_WORLD, &send_request[send_request_count]);
        send_request_count++;
    }

    if (para->me != 0) {
        MPI_Isend(&(*u)[2 * para->Nx * (para->recouvrement - 1)], 
                3 * para->Nx, MPI_DOUBLE, para->me - 1, para->me - 1, 
                MPI_COMM_WORLD, &send_request[send_request_count]);
        send_request_count++;
    }

    // Attente des envois
    MPI_Waitall(send_request_count, send_request, MPI_STATUSES_IGNORE);

    // ----------------------------------------
    //        Recv
    // ----------------------------------------

    // 2. Réceptions
    vector<double> recou_bas(3 * para->Nx), recou_haut(3 * para->Nx);

    if (para->me != 0) {
        MPI_Irecv(&recou_bas[0], 3 * para->Nx, MPI_DOUBLE, para->me - 1, para->Ny_global + para->me, 
                MPI_COMM_WORLD, &recv_request[recv_request_count]);
        recv_request_count++;
    }

    if (para->me != para->np - 1) {
        MPI_Irecv(&recou_haut[0], 3 * para->Nx, MPI_DOUBLE, para->me + 1, para->me, 
                MPI_COMM_WORLD, &recv_request[recv_request_count]);
        recv_request_count++;
    }

    // Attente des réceptions
    MPI_Waitall(recv_request_count, recv_request, MPI_STATUSES_IGNORE);

    // ----------------------------------------
    //        Recouvrement
    // ----------------------------------------

    // 3. Traitement des recouvrements

    // Bord bas
    if (para->me != 0) {
        for (int i = 0; i < para->Nx; i++) {
            (*rhs)[i] += dy * (recou_bas[i] - recou_bas[i + 2 * para->Nx])
                        + para->dy * dy * 2 * para->beta * recou_bas[i + para->Nx] / para->alpha;
        }
    } 
    else {
        // Si processeur 0
        for (int i = 0; i < para->Nx; i++) {
            (*rhs)[i] += dy * fonc->g(i * para->dx, 0, t, para);
        }
    }

    // Bord haut
    if (para->me != para->np - 1) {
        for (int i = 0; i < para->Nx; i++) {
            (*rhs)[para->Nx * (para->Ny - 1) + i] += dy * (recou_haut[i + 2 * para->Nx] - recou_haut[i])
                        + para->dy * dy * 2 * para->beta * recou_haut[i + para->Nx]  / para->alpha;
        }
    }
    else {
        // Si dernier processeur
        for (int i = 0; i < para->Nx; i++) {
            (*rhs)[para->Nx * (para->Ny - 1) + i] += dy * fonc->g(i * para->dx, para->Ly, t, para);
        }
    }

    // ----------------------------------------
    // Condition de bords droite et gauche
    // ----------------------------------------

    for (int j = 0; j < para->Ny; j++) {
        (*rhs)[para->Nx*j]              += dx * fonc->h(0, (j+para->iBeg)*para->dy, t, para);
        (*rhs)[para->Nx*j + para->Nx-1] += dx * fonc->h(para->Lx, (j+para->iBeg)*para->dy, t, para);
    }
}


void matvect_df(vector<double> *x, vector<double> *y, Parameters *para, Fonctions *fonc)
{
    // ----------------------------------------
    // Definition des constante de la matrice
    // ----------------------------------------
    double dy = para->D * para->dt / (para->dx * para->dx);
    double dx = para->D * para->dt / (para->dy * para->dy);
    double d = 1 + 2*dx + 2*dx;
    double gamma = para->dy * dy * 2 * para->beta / para->alpha;
    
    // ----------------------------------------
    // Produit matrice vecteur 
    // ----------------------------------------

    for (int i=0; i<para->Nx; i++) {
        for (int j=0; j<para->Ny; j++) {
            (*y)[j*para->Nx + i] = 0;
        }
    }
    
    // MatVect bord domaine bas
    if (para->me != 0) {
        for (int i=0; i<para->Nx; i++) {
            (*y)[i] += (d+gamma) * (*x)[i];
            (*y)[i] -= 2 * dy * (*x)[i + para->Nx];
            if (i!=0) {
                (*y)[i] -= dx * (*x)[i - 1];
            }
            if (i!=(para->Nx-1)) {
                (*y)[i] -= dx * (*x)[i + 1];
            }
        }
    }
    // MatVect si proc 0
    else {
        for (int i=0; i<para->Nx; i++) {
            (*y)[i] += d * (*x)[i];
            (*y)[i] -= dy * (*x)[i + para->Nx];
            if (i!=0) {
                (*y)[i] -= dx * (*x)[i - 1];
            }
            if (i!=(para->Nx-1)) {
                (*y)[i] -= dx * (*x)[i + 1];
            }
        }
    }
    
    // MatVect bord domaine haut
    if (para->me != para->np-1) {
        for (int i=(para->Ny-1)*para->Nx; i<(para->Ny-1)*para->Nx + para->Nx; i++) {
            (*y)[i] += (d+gamma) * (*x)[i];
            (*y)[i] -= 2 * dy * (*x)[i - para->Nx];
            if (i%para->Nx == 0) {
                (*y)[i] -= dx * (*x)[i - 1];
            }
            if (i%para->Nx == para->Nx-1) {
                (*y)[i] -= dx * (*x)[i + 1];
            }
        }
    }
    // MatVect si proc np-1
    else {
        for (int i=(para->Ny-1)*para->Nx; i<(para->Ny-1)*para->Nx + para->Nx; i++) {
            (*y)[i] += d * (*x)[i];
            (*y)[i] -= dy * (*x)[i - para->Nx];
            if (i%para->Nx == 0) {
                (*y)[i] -= dx * (*x)[i - 1];
            }
            if (i%para->Nx == para->Nx-1) {
                (*y)[i] -= dx * (*x)[i + 1];
            }
        }
    }


    // MatVect interieur
    for (int i=0; i<para->Nx; i++) {
        for (int j=1; j<para->Ny-1; j++) {
            (*y)[j*para->Nx + i] += d * (*x)[j*para->Nx + i];
            if (i!=0) {
                (*y)[j*para->Nx + i] -= dx * (*x)[j*para->Nx + i - 1];
            }
            if (i!=(para->Nx-1)) {
                (*y)[j*para->Nx + i] -= dx * (*x)[j*para->Nx + i + 1];
            }
            if (j!=0) {
                (*y)[j*para->Nx + i] -= dy * (*x)[j*para->Nx + i - para->Nx];
            }
            if (j!=(para->Ny-1)) {
                (*y)[j*para->Nx + i] -= dy * (*x)[j*para->Nx + i + para->Nx];
            }
        }
    }
}