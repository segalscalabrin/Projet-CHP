#include "gradient_biconjugue.h"


std::vector<double> gradient_biconjugue (Parameters *param, Fonctions *fct, double t, std::vector<double> *b, std::vector<double> *x0) //, int np, int me)
{
    //int cas, Nx, Ny, space_scheme, time_scheme;
    //double xmin, xmax, ymin, ymax, Tf, CFL;
    //get_parameters(&cas, &Nx, &Ny, &space_scheme, &time_scheme, &xmin, &xmax, &ymin, &ymax, &Tf, &CFL);

    //parallelisation
    //int iBeg, iEnd;
    //charge(me, (Nx+1)*(Ny+1), np, &iBeg, &iEnd);
    //int n_loc = iEnd-iBeg;
    

    double rho0, alpha, omega, beta;
    double tol(1e-3);

    vector<double> r0((param->Nx+1)*(param->Ny+1)+1,0.0), r1((param->Nx+1)*(param->Ny+1)+1,0.0); // Etape 1 et 2
    vector<double> p0((param->Nx+1)*(param->Ny+1)+1,0.0); // Etape 4
    vector<double> v((param->Nx+1)*(param->Ny+1)+1,0.0); // Etape 5.1
    vector<double> h((param->Nx+1)*(param->Ny+1)+1,0.0); // Etape 5.3
    vector<double> s((param->Nx+1)*(param->Ny+1)+1,1.0); // Etape 5.4
    vector<double> T((param->Nx+1)*(param->Ny+1)+1,0.0); // Etape 5.6
    vector<double> Ax0((param->Nx+1)*(param->Ny+1)+1,0.0);

// initialisation
    matvect_df (x0, &Ax0, param, fct);    

    for (int k = 0 ; k <= (param->Nx+1)*(param->Ny+1) ; k++)
    {
        r0[k] = (*b)[k] - Ax0[k];
        r1[k] = r0[k]; // r1 est le r0chapeau de wikipedia
        p0[k] = r0[k]; 
    }
    rho0 = vector_scalar(&r0, &r1, (param->Nx+1)*(param->Ny+1)); 
    

    
// boucle jusqu'à convergence
    while (sqrt(vector_scalar(&r0, &r0, (param->Nx+1)*(param->Ny+1)))>tol && 
        sqrt(vector_scalar(&s, &s, (param->Nx+1)*(param->Ny+1))>tol))
    {
        matvect_df (&p0, &v, param, fct);
        alpha = rho0/vector_scalar(&r1,&v, (param->Nx+1)*(param->Ny+1));
        for (int k = 0; k <= ((param->Nx+1)*(param->Ny+1)); k++) 
        {
            h[k] = (*x0)[k]+alpha*p0[k]; 
            s[k] = r0[k]-alpha*v[k];
        }
        matvect_df (&s, &T, param, fct);
        omega = vector_scalar(&T,&s, (param->Nx+1)*(param->Ny+1))/vector_scalar(&T,&T, (param->Nx+1)*(param->Ny+1));
        for (int k = 0; k <= (param->Nx+1)*(param->Ny+1); k++) 
        {
            (*x0)[k] = h[k]+omega*s[k]; 
            r0[k] = s[k]-omega*T[k];
        } 
        beta = (vector_scalar(&r1, &r0, (param->Nx+1)*(param->Ny+1))/rho0)*(alpha/omega);
        rho0 = vector_scalar(&r1,&r0, (param->Nx+1)*(param->Ny+1));
        for (int k = 0; k <= (param->Nx+1)*(param->Ny+1); k++) 
        {
            p0[k] = r0[k]+beta*(p0[k]-omega*v[k]); 
        }
    }
    
    if (sqrt(vector_scalar(&s, &s, (param->Nx+1)*(param->Ny+1))<tol))
    {
        return h;
    }
    else
    {
        return (*x0);
    }

}