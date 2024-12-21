#!/bin/bash

# Chemin vers le dossier contenant les scripts auxiliaires
SCRIPTS_DIR="./scripts"

# Vérification des arguments
if [ "$#" -ne 5 ] && [ "$#" -ne 1 ]; then
    echo "Usage: $0 Nx Ny Cas Recouvrement NombreDeProc"
    echo "       ou"
    echo "       $0 clean"
    exit 1
fi

# Mode nettoyage
if [ "$1" == "clean" ]; then
    "$SCRIPTS_DIR/clean.sh"
    exit 0
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

# Définition du dossier de solutions
solutions_dir="solutions/${cas_name}_${Nx}_${Ny}"

# Étape 1 : Vérification des arguments
"$SCRIPTS_DIR/check_args.sh" "$Nx" "$Ny" "$Cas" "$Recouvrement" "$NombreDeProc"
if [ $? -ne 0 ]; then
    echo "Erreur lors de la vérification des arguments."
    exit 1
fi

# Étape 2 : Création des dossiers nécessaires
"$SCRIPTS_DIR/generate_directories.sh" "$Nx" "$Ny" "$Cas" "$Recouvrement" "$NombreDeProc"
if [ $? -ne 0 ]; then
    echo "Erreur lors de la création des répertoires."
    exit 1
fi

# Étape 3 : Génération des scripts Gnuplot
"$SCRIPTS_DIR/generate_gnuplot_scripts.sh" "$Nx" "$Ny" "$Cas" "$Recouvrement" "$NombreDeProc"
if [ $? -ne 0 ]; then
    echo "Erreur lors de la génération des scripts Gnuplot."
    exit 1
fi

# Étape 4 : Compilation du programme
"$SCRIPTS_DIR/compile_program.sh"
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation du programme."
    exit 1
fi

# Étape 5 : Exécution du programme
"$SCRIPTS_DIR/execute_program.sh" "$Nx" "$Ny" "$Cas" "$Recouvrement" "$NombreDeProc"
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'exécution du programme."
    exit 1
fi

# Étape 6 : Concaténation des fichiers solution
"$SCRIPTS_DIR/concatenate_solutions.sh" "$solutions_dir/sol" "$NombreDeProc"
if [ $? -ne 0 ]; then
    echo "Erreur lors de la concaténation des fichiers solution."
    exit 1
fi

echo "Pipeline terminé avec succès !"