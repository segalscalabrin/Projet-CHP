#include "test_params.h"


bool is_positive_integer(const string str) {
    if (str.empty()) return false; 
    for (char c : str) {
        if (!isdigit(c)) return false; 
    }
    return !str.empty() && stoi(str) > 0; 
}

void check_enter_params(const string Cas, const string Nx, const string Ny) {
    if (!is_positive_integer(Cas)) {
        cerr << "Erreur : Cas doit être un entier strictement positif." << endl;
        exit(EXIT_FAILURE);
    }
    if (!is_positive_integer(Nx)) {
        cerr << "Erreur : Nx doit être un entier strictement positif." << endl;
        exit(EXIT_FAILURE);
    }
    if (!is_positive_integer(Ny)) {
        cerr << "Erreur : Ny doit être un entier strictement positif." << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Tous les paramètres sont valides." << endl;
}