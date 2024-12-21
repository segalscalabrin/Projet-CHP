#!/bin/bash

echo "Compilation du programme..."

# Compilation du programme
make
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation. Vérifiez votre Makefile."
    exit 1
fi
echo "Compilation réussie."
echo ""
