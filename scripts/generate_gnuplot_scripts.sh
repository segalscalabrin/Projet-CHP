#!/bin/bash

echo "Génération des scripts Gnuplot..."

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
        zrange="[0:0.1]"
        cbrange="[0:0.1]"
        ;;
    2)
        cas_name="stationnaire_2"
        zrange="[0:3]"
        cbrange="[0:3]"
        ;;
    3)
        cas_name="instationnaire"
        zrange="[0:1]"
        cbrange="[0:1]"
        ;;
    4)
        cas_name="personnalise"
        zrange="[0:1]"  # À ajuster selon vos besoins
        cbrange="[0:1]" # À ajuster selon vos besoins
        ;;
    *)
        echo "Erreur : Cas invalide. Utilisez 1, 2, 3 ou 4."
        exit 1
        ;;
esac

# Chemin du dossier de solutions
solutions_dir="solutions"
output_dir="${solutions_dir}/${cas_name}_${Nx}_${Ny}"

# Fonction pour générer un script Gnuplot
generate_gnuplot_script() {
    local filename=$1
    local data_path=$2
    local zrange=$3
    local cbrange=$4

    cat <<EOF > "$filename"
# Définir la palette des couleurs
set palette defined ( 0 '#F7FBFF',\
                      1 '#DEEBF7',\
                      2 '#C6DBEF',\
                      3 '#9ECAE1',\
                      4 '#6BAED6',\
                      5 '#4292C6',\
                      6 '#2171B5',\
                      7 '#084594' )

# Forcer l'étendue de la colorbar
set cbrange $cbrange

# Forcer la mise à l'échelle des axes
set size ratio -1

# Étendue de l'axe des z
set zrange $zrange

# Fixer le point de vue
set view 48,132

# Trouver automatiquement le nombre de fichiers
n_files = system("ls sol/sol.*.dat | wc -l")

do for [i = 0:(n_files-1)] {
    t = i * 0.01
    set title "t = ".sprintf("%f", t)." s"." (i = ".sprintf("%d", i).")"
    show title
    splot "sol/sol.".i.".dat" u 1:2:3 palette, \
          "sol_exacte/sol_exacte.".i.".dat" u 1:2:3 palette
    pause 0.1
}
EOF
}

# Génération du script pour les solutions calculées
generate_gnuplot_script "${output_dir}/plot_sol.gnu" "sol/sol." "$zrange" "$cbrange"

echo "Scripts Gnuplot générés avec succès dans $output_dir."
echo ""
