#!/bin/bash

echo "Concaténation des fichiers solution..."

# Vérification des arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 solutions_dir NombreDeProc"
    echo "  solutions_dir : Chemin du dossier où les fichiers sont stockés"
    echo "  NombreDeProc  : Nombre de processus utilisés"
    exit 1
fi

# Récupération des arguments
solutions_dir=$1
NombreDeProc=$2

# Vérification que le dossier solutions/sol existe
solutions_sol_dir="${solutions_dir}"
if [ ! -d "$solutions_sol_dir" ]; then
    echo "Erreur : Le dossier $solutions_sol_dir n'existe pas."
    exit 1
fi

# Calcul du nombre de pas de temps (TempsMax)
num_files=$(ls ${solutions_sol_dir}/sol.*.*.dat 2>/dev/null | wc -l)
if [ $num_files -eq 0 ]; then
    echo "Erreur : Aucun fichier trouvé dans $solutions_sol_dir."
    exit 1
fi

TempsMax=$((num_files / NombreDeProc - 1))

# Concaténation des fichiers pour chaque pas de temps
for t in $(seq 0 $TempsMax); do
    concat_file="${solutions_sol_dir}/sol.${t}.dat"

    # Concaténer les fichiers des processus pour le temps `t`
    for proc in $(seq 0 $(($NombreDeProc - 1))); do
        proc_file="${solutions_sol_dir}/sol.${t}.${proc}.dat"
        if [ -f "$proc_file" ]; then
            cat "$proc_file" >> "$concat_file"
            rm "$proc_file" # Supprimer le fichier intermédiaire
        else
            echo "Attention : Fichier $proc_file manquant, il sera ignoré."
        fi
    done

done

echo "Concaténation terminée pour tous les fichiers."
echo ""
