#include "initialisation.h"

void read_parameters(const string& parameters_path, Parameters *params) {
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
            else if (name == "Cas") params->Cas = value;
        }
    }

    params->dx = params->Lx/(params->Nx-1);
    params->dy = params->Ly/(params->Ny-1);

    file.close();
}