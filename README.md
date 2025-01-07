# Projet Calcul Parallèle 3A
Mise en œuvre d’une méthode de décomposition de domaine de type Schwarz sur maillage cartésien régulier.

## Prérequis
Avant d'exécuter le projet, assurez-vous que **mpic++**, **mpiexec** et **mpirun** sont installés et disponibles dans votre **$PATH**.

## Compilation et execution

Lancer la compilation et l’exécution avec la commande :
```bash
./main.sh Nx Ny Cas Recouvrement NombreDeProc
```

`<Nx>` : le nombre de point dans la direction x.

`<Ny>` : le nombre de point dans la direction y.

`<Cas>` : numero du cas (**0**: personnalise, **1**: stationnaire 1, **2**: stationnaire 2, **3**: instationnaire)

`<Recouvrement>` : le nombre de ligne de recouvrement

`<NombreDeProc>` : le nombre de processeur

### Attention ###

Si vous avez une erreur au niveau de la concaténation, il est possible que cela soit dû au **mpiexec**, il faudra alors changer le **mpiexec** par un **mpirun** dans le script `/scripts/execute_program.sh` à la ligne 19.

## Paramètres

### Choix du cas
**Cas de test 1, 2 et 3** : Les fichiers de paramètres sont disponibles dans les dossiers `/test/stationnaire_1`, `/test/stationnaire_2` et `/test/instationnaire`.

**Autres cas de test** : Utilisez le fichier `/test/personnalise/parametres.txt`.

### Modification des Paramètres
Pour ajuster les valeurs des paramètres, ouvrez le fichier de paramètres correspondant et modifiez les valeurs souhaitées.

Pour le cas personnalisé, modifier les fonctions dans les fichiers `/test/personnalise/fonctions.cpp`.
