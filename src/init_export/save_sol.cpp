#include "save_sol.h"

void save_solution (std::vector<double> *U, int ite, Parameters *param, bool exacte)
{
    //int cas, Nx, Ny, space_scheme, time_scheme;
    //double xmin, xmax, ymin, ymax, Tf, CFL;
    //get_parameters(&cas, &Nx, &Ny, &space_scheme, &time_scheme, &xmin, &xmax, 
    //&ymin, &ymax, &Tf, &CFL);

    double x, y;
    int k(0), iBeg, iEnd, i, j;

    //charge(me, (Nx+1)*(Ny+1), np, &iBeg, &iEnd);
    //int n_loc = iEnd-iBeg;
    int n_loc = (param->Nx+1)*(param->Ny+1);

    string ps, str_me;
    ps = to_string(ite);
    //str_me = to_string(me);
    string name_file;
    if (exacte)
    {
        name_file = ("sol_exacte."+ps+".dat");  // Le nom de mon fichier
    }
    else 
    {
        name_file = ("sol_exacte."+ps+".dat");  // Le nom de mon fichier
    }
    ofstream mon_flux;
    mon_flux.open(name_file, ios::out);  // Ouvre un fichier appelé name_file

    if (mon_flux)                        // Vérifie que le fichier est bien ouvert
    {
        for (int k = 0; k<= n_loc ; k++)
        {
            j = (k+iBeg)/(param->Nx+1);
            i = (k+iBeg)-j*(param->Nx+1);
            x = param->xmin + i*param->dx;
            y = param->ymin + j*param->dy;
            mon_flux << x << " " << y << " " << (*U)[k] << std::endl;
            x += param->dx;
        }
        
    }
    else // Renvoie un message d'erreur si ce n'est pas le cas
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
    mon_flux.close(); // Ferme le fichier
}

/*void save_solution_exacte (std::vector<double> U, int ite, double dx, double dy, int np, int me)
{
    int cas, Nx, Ny, space_scheme, time_scheme;
    double xmin, xmax, ymin, ymax, Tf, CFL;
    get_parameters(&cas, &Nx, &Ny, &space_scheme, &time_scheme, &xmin, &xmax, 
    &ymin, &ymax, &Tf, &CFL);

    double x, y;
    int k(0), iBeg, iEnd, i, j;

    charge(me, (Nx+1)*(Ny+1), np, &iBeg, &iEnd);
    int n_loc = iEnd-iBeg+1;

    string ps, str_me;
    ps = to_string(ite);
    str_me = to_string(me);
    string name_file("sol_exacte."+ps+".00"+str_me+".dat");  // Le nom de mon fichier
    ofstream mon_flux;
    mon_flux.open(name_file, ios::out);  // Ouvre un fichier appelé name_file

    if (mon_flux)                        // Vérifie que le fichier est bien ouvert
    {
        for (int k = 0; k<= n_loc ; k++)
        {
            j = (k+iBeg)/(Nx+1);
            i = (k+iBeg)-j*(Nx+1);
            x = xmin + i*dx;
            y = ymin + j*dy;
            mon_flux << x << " " << y << " " << U[k] << std::endl;
            x += dx;
        }
        
    }
    else // Renvoie un message d'erreur si ce n'est pas le cas
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
    mon_flux.close(); // Ferme le fichier
}*/