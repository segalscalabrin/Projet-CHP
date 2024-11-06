#include "initialisation.h"

void read_parameters(int cas, Parameters *params) {
    string parameters_path;

    if (cas == 0) {
        parameters_path = "parameters.txt";
    }
    else if (cas == 1) {
        parameters_path = "test/instationnaire/parametres.txt";
        params->Cas = 1;
    }
    else if (cas == 2) {
        parameters_path = "test/stationnaire/parametres.txt";
        params->Cas = 2;
    }
    else {
        cerr << "Erreur dans le choix du cas" << endl;
        exit(1);
    }
    
    ifstream file(parameters_path);
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << parameters_path << endl;
        return;
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
            else if (name == "Nx") params->Nx = value;
            else if (name == "Ny") params->Ny = value;
            else if (name == "dt") params->dt = value;
            else if (name == "D") params->D = value;
            else if (name == "Cas") params->Cas = value;
        }
    }

    params->dx = params->Lx/(params->Nx-1);
    params->dy = params->Ly/(params->Ny-1);

    file.close();
}