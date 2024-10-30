#ifndef INCLUDE_H
#define INCLUDE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "mpi.h"

using namespace std;

struct Parameters {
    // -------------------------------------------- //
    //              Parametres du schema
    // -------------------------------------------- //

    // Taille du domaine
    double Lx;
    double Ly;

    // Nombre d'éléments par dimension
    int Nx;
    int Ny;

    // Pas d'espace
    double dx;
    double dy;

    // Pas de temps
    double dt;

    // Cas
    int Cas;

    // -------------------------------------------- //
    //              Parametres de MPI
    // -------------------------------------------- //

    // Nombre de proc
    int nprocs;

    // Numéro du proc
    int rang;
};

#endif // INCLUDE_H