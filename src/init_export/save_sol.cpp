#include "save_sol.h"

void save_solution (std::vector<double> *U, int ite, Parameters *param, bool exacte)
{
    //int cas, Nx, Ny, space_scheme, time_scheme;
    //double xmin, xmax, ymin, ymax, Tf, CFL;
    //get_parameters(&cas, &Nx, &Ny, &space_scheme, &time_scheme, &xmin, &xmax, 
    //&ymin, &ymax, &Tf, &CFL);

    double x, y;
    int k(0), iBeg(0), iEnd(0), i, j;

    //charge(me, (Nx)*(Ny), np, &iBeg, &iEnd);
    //int n_loc = iEnd-iBeg;
    int n_loc = (param->Nx)*(param->Ny);

    string ps, str_me;
    ps = to_string(ite);
    //str_me = to_string(me);
    string name_file;
    if (exacte)
    {
        name_file = ("output/sol_exacte."+ps+".dat");  // Le nom de mon fichier
    }
    else 
    {
        name_file = ("output/sol_exacte."+ps+".dat");  // Le nom de mon fichier
    }
    ofstream mon_flux;
    mon_flux.open(name_file, ios::out);  // Ouvre un fichier appelé name_file

    if (mon_flux)                        // Vérifie que le fichier est bien ouvert
    {
        for (int k = 0; k<= n_loc ; k++)
        {
            j = (k+iBeg)/(param->Nx);
            i = (k+iBeg)-j*(param->Nx);
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
