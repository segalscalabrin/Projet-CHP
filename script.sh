#!/bin/bash

# Dossier contenant les fichiers
input_folder="solutions/stationnaire_1_100_100/sol"
output_folder="solutions/stationnaire_1_100_100/sol_bis"  # Dossier de sortie
mkdir -p "$output_folder"          # Créer le dossier de sortie s'il n'existe pas

# Boucle sur chaque valeur de t
for t in {0..1001}; do
    output_file="$output_folder/sol.${t}.dat"  # Nom du fichier de sortie
    > "$output_file"  # Créer/vider le fichier de sortie
    
    # Boucle sur chaque proc pour ce pas de temps
    for proc in {0..2}; do
        input_file="$input_folder/sol.${t}.${proc}.dat"
        
        # Vérifie si le fichier existe
        if [[ -f "$input_file" ]]; then
            cat "$input_file" >> "$output_file"  # Ajouter le contenu au fichier de sortie
        else
            echo "Fichier $input_file manquant, ignoré."
        fi
    done
done

echo "Consolidation terminée. Les fichiers sont dans $output_folder."
