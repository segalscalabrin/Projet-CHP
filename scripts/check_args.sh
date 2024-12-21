#!/bin/bash

echo "Vérification des arguments..."

# Vérification du nombre d'arguments
if [ "$#" -ne 5 ]; then
    echo "Usage: $0 Nx Ny Cas Recouvrement NombreDeProc"
    echo "Arguments attendus :"
    echo "  Nx            : Nombre de points dans la direction X (entier positif)"
    echo "  Ny            : Nombre de points dans la direction Y (entier positif)"
    echo "  Cas           : Identifiant du cas (1, 2, 3 ou 4)"
    echo "  Recouvrement  : Taille du recouvrement (entier positif ou 0)"
    echo "  NombreDeProc  : Nombre de processus (entier > 0)"
    exit 1
fi

# Récupération des arguments
Nx=$1
Ny=$2
Cas=$3
Recouvrement=$4
NombreDeProc=$5

# Vérification que Nx est un entier positif
if ! [[ "$Nx" =~ ^[0-9]+$ ]] || [ "$Nx" -le 0 ]; then
    echo "Erreur : Nx doit être un entier positif."
    exit 1
fi

# Vérification que Ny est un entier positif
if ! [[ "$Ny" =~ ^[0-9]+$ ]] || [ "$Ny" -le 0 ]; then
    echo "Erreur : Ny doit être un entier positif."
    exit 1
fi

# Vérification que Cas est un entier valide
if ! [[ "$Cas" =~ ^[1-4]$ ]]; then
    echo "Erreur : Cas doit être 1, 2, 3 ou 4."
    exit 1
fi

# Vérification que Recouvrement est un entier positif ou 0
if ! [[ "$Recouvrement" =~ ^[0-9]+$ ]]; then
    echo "Erreur : Recouvrement doit être un entier positif ou 0."
    exit 1
fi

# Vérification que NombreDeProc est un entier > 0
if ! [[ "$NombreDeProc" =~ ^[0-9]+$ ]] || [ "$NombreDeProc" -le 0 ]; then
    echo "Erreur : NombreDeProc doit être un entier supérieur à 0."
    exit 1
fi

# Si toutes les vérifications passent
echo "Arguments vérifiés avec succès :"
echo "  Nx = $Nx"
echo "  Ny = $Ny"
echo "  Cas = $Cas"
echo "  Recouvrement = $Recouvrement"
echo "  Nombre De Proc = $NombreDeProc"
echo ""
