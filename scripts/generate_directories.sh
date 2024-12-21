#!/bin/bash

echo "Création des répertoires..."

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

# Définition du nom du cas en fonction de l'argument Cas
case $Cas in
    1)
        cas_name="stationnaire_1"
        ;;
    2)
        cas_name="stationnaire_2"
        ;;
    3)
        cas_name="instationnaire"
        ;;
    4)
        cas_name="personnalise"
        ;;
    *)
        echo "Erreur : Cas invalide. Utilisez 1, 2, 3 ou 4."
        exit 1
        ;;
esac

# Chemin du dossier de solutions
solutions_dir="solutions"
output_dir="${solutions_dir}/${cas_name}_${Nx}_${Ny}"

# Création des dossiers
mkdir -p "$output_dir"

mkdir -p "${output_dir}/sol"

echo "Structure de dossiers créée avec succès."
echo ""
