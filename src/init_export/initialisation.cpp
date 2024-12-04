#include "initialisation.h"

#include "../../cas_test/instationnaire/fonctions.h"
#include "../../cas_test/personnalise/fonctions.h"
#include "../../cas_test/stationnaire_1/fonctions.h"
#include "../../cas_test/stationnaire_2/fonctions.h"

void init_functions(Fonctions* fct,
                   function<double(double, double, double, Parameters*)> f,
                   function<double(double, double, double, Parameters*)> g,
                   function<double(double, double, double, Parameters*)> h,
                   function<double(double, double, double, Parameters*)> sol_exact) {
    fct->f = f;
    fct->g = g;
    fct->h = h;
    fct->sol_exact = sol_exact;
}


string select_case(int cas, Parameters *params, Fonctions *fct)
// Initialise les données spécial du cas choisis
{
    string parameters_path;

    if (cas == 4) {
        parameters_path = "cas_test/personnalise/parametres.txt";
        params->Cas = 0;
        init_functions(fct, personnalise::f, personnalise::g, personnalise::h, personnalise::sol_exact);
    }
    else if (cas == 1) {
        parameters_path = "cas_test/stationnaire_1/parametres.txt";
        params->Cas = 1;
        init_functions(fct, stationnaire_1::f, stationnaire_1::g, stationnaire_1::h, stationnaire_1::sol_exact);
    }
    else if (cas == 2) {
        parameters_path = "cas_test/stationnaire_2/parametres.txt";
        params->Cas = 2;
        init_functions(fct, stationnaire_2::f, stationnaire_2::g, stationnaire_2::h, stationnaire_2::sol_exact);
    }
    else if (cas == 3) {
        parameters_path = "cas_test/instationnaire/parametres.txt";
        params->Cas = 3;
        init_functions(fct, instationnaire::f, instationnaire::g, instationnaire::h, instationnaire::sol_exact);
    }
    else {
        cerr << "Erreur: le choix du cas ne correspond à aucun cas" << endl;
        cerr << "CAS 1: Stationnaire 1" << endl;
        cerr << "CAS 2: Stationnaire 2" << endl;
        cerr << "CAS 3: Instationnaire" << endl;
        cerr << "CAS 4: Personnalise" << endl;
        exit(1);
    }

    return parameters_path;
}


void read_parameters(int cas, int Nx, int Ny, int Ny_loc, int iBeg, int iEnd, int me, int np, int recouvrement, Parameters *params, Fonctions *fct) 
// Lis les parametres en fonctions du cas choisi
{
    string parameters_path;
    parameters_path = select_case(cas, params, fct);
    
    ifstream file(parameters_path);
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << parameters_path << endl;
        cerr << "Fonction : read_parameters " << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name;
        double value;

        // Parse the line as "name=value"
        if (getline(iss, name, '=') && iss >> value) {
            if (name == "xmin") params->xmin = value;
            else if (name == "ymin") params->ymin = value;
            else if (name == "xmax") params->xmax = value;
            else if (name == "ymax") params->ymax = value;
            else if (name == "dt") params->dt = value;
            else if (name == "D") params->D = value;
            else if (name == "Tmax") params->Tmax = value;
        }
    }

    params->Nx = Nx;
    params->Ny_global = Ny;
    params->recouvrement = recouvrement;
    params->Ny = Ny_loc;
    params->me = me;
    params->np = np;
    params->iBeg = iBeg;
    params->iEnd = iEnd;
    
    params->Lx = params->xmax - params->xmin;
    params->Ly = params->ymax - params->ymin;

    params->dx = params->Lx/(params->Nx-1);
    params->dy = params->Ly/(params->Ny_global-1);


    file.close();
}