#!/bin/bash
    
echo "Nettoyage en cours..."

# Définition du dossier à nettoyer
solutions_dir="solutions"

# Vérification de l'existence du dossier
if [ -d "$solutions_dir" ]; then
    echo "Nettoyage du dossier $solutions_dir..."
    rm -rf "$solutions_dir"
    if [ $? -eq 0 ]; then
        echo "Dossier $solutions_dir supprimé avec succès."
    else
        echo "Erreur lors de la suppression du dossier $solutions_dir."
        exit 1
    fi
else
    echo "Le dossier $solutions_dir n'existe pas. Rien à nettoyer."
fi
