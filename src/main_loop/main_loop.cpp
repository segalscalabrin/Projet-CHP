#include "main_loop.h"

#include <unistd.h>

void init_equation(vector<double> *u, Parameters *para, Fonctions *fct)
{
    for(int j=0; j<para->Ny; j++) {
        for(int i=0; i<para->Nx; i++) {
            (*u)[j*para->Nx + i] = 1;
        }
    }
}


void compute_sol_exact(vector<double> *u_exact, double t, Parameters *para, Fonctions *fct)
{
    for(int j=0; j<para->Ny; j++) {
        for(int i=0; i<para->Nx; i++) {
            (*u_exact)[j*para->Nx + i] = fct->sol_exact(para->xmin + i*para->dx, para->ymin + (j+para->iBeg)*para->dy, t, para);
        }
    }   
}


double compute_error(vector<double> *u, vector<double> *u_exact, Parameters *para)
{
    double error(0), error_tot(0);
    for(int k=0; k<para->Nx*para->Ny; k++) {
        error += ((*u)[k] - (*u_exact)[k])*((*u)[k] - (*u_exact)[k]);
    }

    MPI_Allreduce(&error, &error_tot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    return error_tot;
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
    //compute_sol_exact(u_exact, t, para, fct);

    //error.push_back(compute_error(u, u_exact, para)/(para->Nx*para->Ny_global));

    save_solution(u, k, para, false);
    // save_solution(u_exact, k, para, true);

    // -------------------------------------------------------- //
    if (para->me==0) {cout << "Avancement 0%" << endl;}
    // -------------------------------------------------------- //

    while (t < para->Tmax) {
        // t = t + dt
        t += para->dt;
        k += 1;

        // -------------------------------------------------------- //
        if (para->me==0) {cout << "Avancement " << 100*t/para->Tmax << "%" << endl;}
        // -------------------------------------------------------- //

        // Calcul de u^n+1
        build_rhs_df(&rhs, u, t, para, fct);



        
        sleep(1);
        if (para->me == 0) {
            cout << para->me << " u avant: " << endl;
            for (int j=para->Ny-1; j>=0; j--) {
                for (int i=0; i<para->Nx; i++) {
                    cout << (*u)[j*para->Nx + i] << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
        sleep(1);
        if (para->me == 0) {
            cout << para->me << " rhs avant: " << endl;
            for (int j=para->Ny-1; j>=0; j--) {
                for (int i=0; i<para->Nx; i++) {
                    cout << rhs[j*para->Nx + i] << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
        



        gradient_biconjugue(para, fct, t, &rhs, u);
    
        
        sleep(1);
        if (para->me == 0) {
            cout << para->me << " u apres: " << endl;
            for (int j=para->Ny-1; j>=0; j--) {
                for (int i=0; i<para->Nx; i++) {
                    cout << (*u)[j*para->Nx + i] << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
        sleep(1);
        if (para->me == 0) {
            cout << para->me << " rhs apres: " << endl;
            for (int j=para->Ny-1; j>=0; j--) {
                for (int i=0; i<para->Nx; i++) {
                    cout << rhs[j*para->Nx + i] << " ";
                }
                cout << endl;
            }
        }
        cout << endl;
        

        // Calcul de u exact
        //compute_sol_exact(u_exact, t, para, fct);

        // Calcul de l'erreur quadratique moyenne   
        //error.push_back(compute_error(u, u_exact, para)/(para->Nx*para->Ny_global));

        // Sauvegarde des solutions et 
        save_solution(u, k, para, false);
        //save_solution(u_exact, k, para, true);
    }
    if (para->me==0) {
        //save_error(&error, para);
    }
}
