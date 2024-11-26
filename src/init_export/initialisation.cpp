#include "initialisation.h"

#include "../../test/instationnaire/fonctions.h"
#include "../../test/personnalise/fonctions.h"
#include "../../test/stationnaire_1/fonctions.h"
#include "../../test/stationnaire_2/fonctions.h"

void init_functions(Fonctions* fonctions,
                   function<double(double, double, double, Parameters*)> f,
                   function<double(double, double, double, Parameters*)> g,
                   function<double(double, double, double, Parameters*)> h,
                   function<double(double, double, double, Parameters*)> sol_exact) {
    fonctions->f = f;
    fonctions->g = g;
    fonctions->h = h;
    fonctions->sol_exact = sol_exact;
}

void read_parameters(int cas, Parameters *params, Fonctions *fonctions) {
    string parameters_path;

    if (cas == 0) {
        parameters_path = "test/personnalise/parametres.txt";
        params->Cas = 0;
        init_functions(fonctions, personnalise::f, personnalise::g, personnalise::h, personnalise::sol_exact);
    }
    else if (cas == 1) {
        parameters_path = "test/stationnaire_1/parametres.txt";
        params->Cas = 1;
        init_functions(fonctions, stationnaire_1::f, stationnaire_1::g, stationnaire_1::h, stationnaire_1::sol_exact);
    }
    else if (cas == 2) {
        parameters_path = "test/stationnaire_2/parametres.txt";
        params->Cas = 2;
        init_functions(fonctions, stationnaire_2::f, stationnaire_2::g, stationnaire_2::h, stationnaire_1::sol_exact);
    }
    else if (cas == 3) {
        parameters_path = "test/instationnaire/parametres.txt";
        params->Cas = 3;
        init_functions(fonctions, instationnaire::f, instationnaire::g, instationnaire::h, instationnaire::sol_exact);
    }
    else {
        cerr << "Erreur dans le choix du cas" << endl;
        exit(1);
    }
    
    ifstream file(parameters_path);
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << parameters_path << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name;
        double value;

        // Parse the line as "name=value"
        if (getline(iss, name, '=') && iss >> value) {
            if (name == "Lx") params->Lx = value;
            else if (name == "Ly") params->Ly = value;
            else if (name == "xmin") params->xmin = value;
            else if (name == "ymin") params->ymin = value;
            else if (name == "Nx") params->Nx = value;
            else if (name == "Ny") params->Ny = value;
            else if (name == "dt") params->dt = value;
            else if (name == "D") params->D = value;
            else if (name == "Tmax") params->Tmax = value;
        }
    }

    params->dx = params->Lx/(params->Nx-1);
    params->dy = params->Ly/(params->Ny-1);

    file.close();
}