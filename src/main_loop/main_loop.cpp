#include "main_loop.h"


void init_equation(vector<double> *u, Parameters *para, Fonctions *fct)
{
    for(int j=0; j<para->Ny; j++) {
        for(int i=0; i<para->Nx; i++) {
            (*u)[j*para->Nx + i] = fct->sol_exact(para->xmin + i*para->dx, para->ymin + j*para->dy, 0, para);
        }
    }
}


void compute_sol_exact(vector<double> *u_exact, double t, Parameters *para, Fonctions *fct)
{
    for(int j=0; j<para->Ny; j++) {
        for(int i=0; i<para->Nx; i++) {
            (*u_exact)[j*para->Nx + i] = fct->sol_exact(para->xmin + i*para->dx, para->ymin + j*para->dy, t, para);
        }
    }   
}


double compute_error(vector<double> *u, vector<double> *u_exact, Parameters *para)
{
    double error(0);
    for(int k=0; k<para->Nx*para->Ny; k++) {
        error += ((*u)[k] - (*u_exact)[k])*((*u)[k] - (*u_exact)[k]);
    }

    return error/(para->Nx*para->Ny);
}


void solve_equation(vector<double> *u, vector<double> *u_exact, Parameters *para, Fonctions *fct)
{
    int k(0);
    double t(0);
    vector<double> rhs;
    vector<double> error;
    vector<double> bord_bas(para->Nx, 0.0);
    vector<double> bord_haut(para->Nx, 0.0);
    rhs.resize(u->size());

    init_equation(u, para, fct);
    compute_sol_exact(u_exact, t, para, fct);

    error.push_back(compute_error(u, u_exact, para));

    save_solution(u, k, para, false);
    save_solution(u_exact, k, para, true);

    cout << "Avancement 0%" << endl;

    MPI_Status Status;

    while (t < para->Tmax) {
        // t = t + dt
        t += para->dt;
        k += 1;
        cout << "Avancement " << 100*t/para->Tmax << "%" << endl;
        int tag = 10;
        // récup les conditions de bord dessus et dessous
        if (para->me == 0)
        {
            // envoie la derniere ligne de recouvrement de 0 à 1
            //cout << "Send : " <<  (*u)[para->Nx*(para->Ny_loc-2*para->recouvrement)] << endl;
            MPI_Send(&((*u)[para->Nx*(para->Ny-2*para->recouvrement-1)]), para->Nx, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
            // recoit la première ligne de 1
            //printf("me = %d send u[%d, %d] to %d\n", para->me, para->Nx*(para->Ny_loc-2*para->recouvrement-1), 
            //para->Nx*(para->Ny_loc-2*para->recouvrement-1)+para->Nx, 1);
            //cout << "me = " << para->me << "send u["<< endl;
            MPI_Recv(&(bord_haut[0]), para->Nx, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &Status);
        }
        else if (para->me == para->np-1)
        {
            // envoie la première ligne
            MPI_Send(&((*u)[para->Nx*(2*para->recouvrement)]), para->Nx, MPI_DOUBLE, para->np-2, tag, MPI_COMM_WORLD);
            //printf("me = %d send u[%d, %d] to %d\n", para->me, para->Nx*(2*para->recouvrement), 
            //para->Nx*(2*para->recouvrement)+para->Nx, para->np-2);
            // recoit la dernière ligne de np-2
            MPI_Recv(&(bord_bas[0]), para->Nx, MPI_DOUBLE, para->np-2, tag, MPI_COMM_WORLD, &Status);
        }
        else
        {
            // envoie la derniere ligne de recouvrement de me à me+1
            MPI_Send(&((*u)[para->Nx*(para->Ny-2*para->recouvrement-1)]), para->Nx, MPI_DOUBLE, para->me+1, tag, MPI_COMM_WORLD);
            //printf("me = %d send u[%d, %d] to %d\n", para->me, para->Nx*(para->Ny_loc-2*para->recouvrement-1), 
            //para->Nx*(para->Ny_loc-2*para->recouvrement-1)+para->Nx, para->me+1);
            // recoit la première ligne de 1
            MPI_Recv(&(bord_haut[0]), para->Nx, MPI_DOUBLE, para->me+1, tag, MPI_COMM_WORLD, &Status);

            // envoie la première ligne
            MPI_Send(&((*u)[para->Nx*(2*para->recouvrement)]), para->Nx, MPI_DOUBLE, para->me-1, tag, MPI_COMM_WORLD);
            //printf("me = %d send u[%d, %d] to %d\n", para->me, para->Nx*(2*para->recouvrement), 
            //para->Nx*(2*para->recouvrement)+para->Nx, para->me-1);
            // recoit la dernière ligne de np-2
            MPI_Recv(&(bord_bas[0]), para->Nx, MPI_DOUBLE, para->me-1, tag, MPI_COMM_WORLD, &Status);
        }
        // Calcul de u^n+1
        build_rhs_df(&rhs, u, t, para, fct, &bord_bas, &bord_haut);
        gradient_biconjugue(para, fct, t, &rhs, u);

        // Calcul de u exact
        compute_sol_exact(u_exact, t, para, fct);

        // Calcul de l'erreur quadratique moyenne   
        error.push_back(compute_error(u, u_exact, para));

        // Sauvegarde des solutions et 
        save_solution(u, k, para, false);
        save_solution(u_exact, k, para, true);
    }
    save_error(&error, para);
}
