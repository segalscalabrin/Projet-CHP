#ifndef INCLUDE_H
#define INCLUDE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <functional>
#include <mpi.h>

// #include "mpi.h"

using namespace std;

struct Parameters {
    // -------------------------------------------- //
    //              Parametres géométrique local
    // -------------------------------------------- //

    // Bords du domaine
    double xmin;
    double ymin;
    double xmax;
    double ymax;

    // Taille du domaine
    double Lx;
    double Ly;

    // Nombre d'éléments par dimension
    int Nx;
    int Ny;
    int Ny_global;

    // -------------------------------------------- //
    //              Parametres de l'équation
    // -------------------------------------------- //

    // Pas d'espace
    double dx;
    double dy;

    // Pas de temps
    double dt;

    // Coefficien D
    double D;

    // Temps max
    double Tmax;

    // -------------------------------------------- //
    //              Autres parametres
    // -------------------------------------------- //

    // Cas
    int Cas;

    // -------------------------------------------- //
    //              Parametres parallele
    // -------------------------------------------- //

    int me;
    int np;
    int recouvrement;
};


struct Fonctions {
    // -------------------------------------------- //
    //                Fonctions
    // -------------------------------------------- //

    // Differentes fonctions f, g, h
    function<double(double, double, double, Parameters*)> f;
    function<double(double, double, double, Parameters*)> g;
    function<double(double, double, double, Parameters*)> h;
    function<double(double, double, double, Parameters*)> sol_exact;
};


#endif // INCLUDE_H