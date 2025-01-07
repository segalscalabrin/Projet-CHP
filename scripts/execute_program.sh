#!/bin/bash

echo "Exécution du programme..."

# Vérification des arguments
if [ "$#" -ne 5 ]; then
    echo "Usage: $0 Nx Ny Cas Recouvrement NombreDeProc"
    exit 1
fi

# Récupération des arguments
Nx=$1
Ny=$2
Cas=$3
Recouvrement=$4
NombreDeProc=$5

# Exécution du programme avec mpiexec
mpirun -np "$NombreDeProc" ./eq_chaleur "$Recouvrement" "$Nx" "$Ny" "$Cas"
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'exécution de ./eq_chaleur avec mpiexec."
    exit 1
fi
echo "Programme exécuté avec succès."
echo ""