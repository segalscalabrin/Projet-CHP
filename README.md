# Projet Calcul Parallèle 3A
Mise en œuvre d’une méthode de décomposition de domaine de type Schwarz sur maillage cartésien régulier.

## Prérequis
Avant d'exécuter le projet, assurez-vous que **mpic++** et **mpiexec** sont installés et disponibles dans votre **$PATH**.

## Compilation et execution

### Compilation
Pour compiler le projet, exécutez :
```bash
make
```

### Exécution
Lancer l’exécution avec la commande :
```bash
mpiexec -np <nombre_de_processus> ./run <numero_du_cas>
```

`<nombre_de_processus>` : le nombre de processus souhaité.

`<numero_du_cas>` : numero du cas (1, 2, 0)

## Paramètres

### Choix du cas
**Cas de test 1 et 2** : Les fichiers de paramètres sont disponibles dans les dossiers `./test/stationnaire` et `./test/instationnaire`.

**Autres cas de test** : Utilisez le fichier `parametres.txt` situé à la racine du projet.

### Modification des Paramètres
Pour ajuster les valeurs des paramètres, ouvrez le fichier de paramètres correspondant et modifiez les valeurs souhaitées.