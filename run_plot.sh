#!/bin/bash

# Vérification du nombre d'arguments
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 Nx Ny Cas"
    exit 1
fi

# Récupération des arguments
Nx=$1
Ny=$2
Cas=$3

# Définition du nom du cas
case $Cas in
    1)
        cas_name="stationnaire_1"
        zrange="[0:0.1]"
        cbrange="[0:0.1]"
        ;;
    2)
        cas_name="stationnaire_2"
        zrange="[0:2]"
        cbrange="[0:2]"
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

# Création du dossier principal et des sous-dossiers
mkdir -p "solutions"
solutions_dir="solutions"
output_dir="${solutions_dir}/${cas_name}_${Nx}_${Ny}"
mkdir -p "$output_dir"

if [ "$Cas" -eq 1 ] || [ "$Cas" -eq 2 ]; then
    mkdir -p "${output_dir}/sol"
    mkdir -p "${output_dir}/sol_exacte"
else
    mkdir -p "${output_dir}/sol"
fi

# Génération des scripts Gnuplot
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
n_files = system("ls $data_path*.dat | wc -l")

do for [i = 0:(n_files-1)] {
    t = i * 0.01
    set title "t = ".sprintf("%f", t)." s"." (i = ".sprintf("%d", i).")"
    show title
    splot "$data_path".i.".dat" u 1:2:3 palette
    pause 0.1
}
EOF
}

# Génération des scripts spécifiques pour stationnaire_1
if [ "$Cas" -eq 1 ] || [ "$Cas" -eq 2 ]; then
    generate_gnuplot_script "${output_dir}/plot_sol.gnu" "sol/sol." "$zrange" "$cbrange"
    generate_gnuplot_script "${output_dir}/plot_exacte.gnu" "sol_exacte/sol_exacte." "$zrange" "$cbrange"

    cat <<EOF > "${output_dir}/plot_both.gnu"
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
fi

echo "Scripts Gnuplot générés dans : $output_dir"

# Compilation du programme
echo "Compilation en cours..."
make
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation. Vérifiez votre Makefile."
    exit 1
fi
echo "Compilation réussie."

# Exécution du programme
echo "Exécution de ./eq_chaleur $Nx $Ny $Cas..."
./eq_chaleur $Nx $Ny $Cas
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'exécution de ./eq_chaleur."
    exit 1
fi
echo "Programme exécuté avec succès."