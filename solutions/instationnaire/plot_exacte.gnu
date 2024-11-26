# permet de définir les couleurs d'affichage
set palette defined ( 0 '#F7FBFF',\
                      1 '#DEEBF7',\
                      2 '#C6DBEF',\
                      3 '#9ECAE1',\
                      4 '#6BAED6',\
                      5 '#4292C6',\
                      6 '#2171B5',\
                      7 '#084594' )

# forcer l'étendue de la colorbar. A changer selon les cas.
set cbrange [0:0.1]

# force la mise à l'échelle des axes.
set size ratio -1

# si affichage 3D, force l'étendue de l'axe des z. A changer selon les cas.
set zrange [0:0.1]

# si affichage 3D, fixe le point de vue. A changer selon les cas.
set view 48,132

# Trouver automatiquement le nombre de fichiers
n_files = system("ls sol/sol.*.dat | wc -l")

do for [i = 0:(n_files-1)] {
    t = i * 0.01
    set title "t = ".sprintf("%f", t)." s"." (i = ".sprintf("%d", i).")"
    show title
    ## fait un affichage en 3D et en couleur
    splot "sol_exacte/sol_exacte.".i.".dat" u 1:2:3 palette
    pause 0.1
}
