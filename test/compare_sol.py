import numpy as np

def read_solution(file_path):
    """
    Lit un fichier solution et retourne un tableau numpy des valeurs.

    Args:
        file_path (str): Chemin du fichier.

    Returns:
        np.ndarray: Tableau numpy contenant les valeurs du fichier.
    """
    return np.loadtxt(file_path)

def calculate_mse(file1, file2):
    """
    Calcule l'erreur quadratique moyenne entre deux fichiers solution.

    Args:
        file1 (str): Chemin du premier fichier.
        file2 (str): Chemin du second fichier.

    Returns:
        float: L'erreur quadratique moyenne (MSE).
    """
    # Lire les solutions
    sol1 = read_solution(file1)
    sol2 = read_solution(file2)

    # Vérifier que les fichiers ont le même nombre de points
    if sol1.shape != sol2.shape:
        raise ValueError("Les fichiers ne contiennent pas le même nombre de points.")

    # Extraire les colonnes correspondant aux valeurs (troisième colonne)
    values1 = sol1[:, 2]
    values2 = sol2[:, 2]

    # Calculer l'erreur quadratique moyenne
    mse = np.mean((values1 - values2) ** 2)
    return mse

if __name__ == "__main__":
    # Chemins des fichiers
    file1 = "sol.100.dat"
    file2 = "sol_exacte1.100.dat"

    try:
        # Calcul de l'erreur quadratique moyenne
        mse = calculate_mse(file1, file2)
        print(f"Erreur quadratique moyenne (MSE) entre {file1} et {file2}: {mse:.6e}")
    except Exception as e:
        print(f"Une erreur s'est produite : {e}")
