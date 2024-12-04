#include "save_sol.h"

void save_solution(vector<double> *U, int ite, Parameters *param, bool exacte)
{
    string str_ite, str_Nx, str_Ny;
    str_ite = to_string(ite);
    str_Nx = to_string(param->Nx);
    str_Ny = to_string(param->Ny_global);
    string name_file;

    name_file = "solutions/";

    if (param->Cas == 4) {
        name_file += "personnalise_"+str_Nx+"_"+str_Ny+"/";
    }
    else if (param->Cas == 1) {
        name_file += "stationnaire_1_"+str_Nx+"_"+str_Ny+"/";
    }
    else if (param->Cas == 2) {
        name_file += "stationnaire_2_"+str_Nx+"_"+str_Ny+"/";
    }
    else if (param->Cas == 3) {
        name_file += "instationnaire_"+str_Nx+"_"+str_Ny+"/";
    }

    if (exacte)
    {
        name_file += ("sol_exacte/sol_exacte."+str_ite+"."+to_string(param->me)+".dat");  // Le nom de mon fichier
    }
    else 
    {
        name_file += ("sol/sol."+str_ite+"."+to_string(param->me)+".dat");  // Le nom de mon fichier
    }

    int y_debut(0), y_fin(param->Ny);
    if (param->me == 0)
    {
        y_fin -= param->recouvrement;
    }
    else if (param->me == param->np-1)
    {
        y_debut -= param->recouvrement;
    }

    ofstream mon_flux;
    mon_flux.open(name_file, ios::out);  // Ouvre un fichier appelé name_file

    if (mon_flux)                        // Vérifie que le fichier est bien ouvert
    {
        double x, y;
        for (int j = y_debut; j<y_fin; j++) 
        {
            for (int i = 0; i<param->Nx; i++) 
            {
                x = param->xmin + i*param->dx;
                y = param->ymin + j*param->dy;
                mon_flux << x << " " << y << " " << (*U)[j*param->Nx + i] << endl;
            }
        }        
    }
    else // Renvoie un message d'erreur si ce n'est pas le cas
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier de solution :" << name_file << std::endl;
    }
    mon_flux.close(); // Ferme le fichier
}


void save_error (vector<double> *error, Parameters *param)
{
    string str_Nx, str_Ny;
    str_Nx = to_string(param->Nx);
    str_Ny = to_string(param->Ny_global);
    string name_file;

    name_file = "solutions/";

    if (param->Cas == 0) {
        name_file += "personnalise_"+str_Nx+"_"+str_Ny+"/";
    }
    else if (param->Cas == 1) {
        name_file += "stationnaire_1_"+str_Nx+"_"+str_Ny+"/";
    }
    else if (param->Cas == 2) {
        name_file += "stationnaire_2_"+str_Nx+"_"+str_Ny+"/";
    }
    else if (param->Cas == 3) {
        name_file += "instationnaire_"+str_Nx+"_"+str_Ny+"/";
    }

    name_file += "error.dat";

    ofstream mon_flux;
    mon_flux.open(name_file, ios::out);  // Ouvre un fichier appelé name_file

    if (mon_flux)                        // Vérifie que le fichier est bien ouvert
    {
        double t(0);
        int k(0);
        
        while(t < param->Tmax) {
            mon_flux << t << " " << (*error)[k] << endl;
            t += param->dt;
            k += 1;
        }   
    }
    else // Renvoie un message d'erreur si ce n'est pas le cas
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier d'erreur." << std::endl;
    }
    mon_flux.close(); // Ferme le fichier
}

