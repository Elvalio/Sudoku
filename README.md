# SudokuAlgorithme
===

```

// Fonction principale 

programme Sudoku c'est


// Procédures
procédure afficherRegles();
procédure afficherGrille(entE tableauGrille : tableau[] de entier );
procédure bloquerGrille(entE tableauGrille : tableau[] de entier );
procédure entreeSaisie(entE listeEmplacementBloque : tableau[] de entier , sortE emplacementUtil : tableau[] de entier , sortE chiffreUser : entier );
procédure modifieGrille(entE emplacementUtil : tableau[] de entier , entE chiffreUser : entier , entE/sortE tableauGrille : tableau[] de entier);
procédure verifierGrille(entE tableauGrille : tableau[] de entier);
procédure afficherComptage(entE compteur : entier);


// Fonctions
fonction creerGrille(entE fichierGrille) délivre tableau[] de entier ;
fonction bloquerGrille(entE tableauGrille : tableau[] de entier) délivre tableau[] de entier ;


// Déclaration des constantes 

constante chaine COLONNE_MIN := 'A';
constante chaine COLONNE_MAX := 'I';
constante chaine CHAR_COLONNE := 12;
constante entier RANGEE_MIN := 1;
constante entier RANGEE_MAX := 9;
constante entier CHAR_RANGEE := 25;
constante entier TAILLE_SAISIE := 2;
constante chaîne EMPLACEMENT_VIDE := '.';
constante entier REPRE_EMPLACEMENT_VIDE := -1;
constante entier NBR_ELEMENT := 81;

début
    // Déclaration variables
    jeuEnCours : booléen ;
    emplacementUtil : tableau[TAILLE_SAISIE] de entier ;
    chiffreUser : entier ;
    tableauGrille : tableau[RANGEE_MAX] de entier;
    listeEmplacementBloque : tableau[NBR_ELEMENT] de entier;
    entier compteur := 0 ;

    // Initialisation variables
    jeuEnCours := vrai;
    tableauGrille := creerGrille(entE fichierGrille);
    listeEmplacementBloque := bloquerGrille(entE tableauGrille);

    afficherRegles();

    tant que (jeuEnCours) faire
        afficherGrille(entE tableauGrille);
        entreeSaisie(entE listeEmplacementBloque , sortE emplacementUtil , sortE chiffreUser);
        modifieGrille(entE emplacementUtil , entE chiffreUser , entE/sortE tableauGrille);
        jeuEnCours := verifierGrille(entE tableauGrille);
        compteur = compteur + 1 ;
    finfaire

    afficherComptage(entE compteur);

fin
```
---
# Listage Procédure/Fonctions


**Procédure :** _afficherRegles_

Affiche les règles du jeu EnCours.

**Paramètres:**

Aucun

---

**Fonction :** _creerGrille_

Crée une double liste des chiffres provenant d'un fichier contenant les chiffres de la grille du Sudoku.
Le fichier sera choisi aléatoirement parmi différents fichiers.
Tous les vides seront représentés par un -1.

**Paramètres:**

- `fichierGrille` (Entrée) : fichier de base pour créer une table de Sudoku.

**Résultat:**

Double tableau d'entiers.

---

**Fonction :** _bloquerGrille_

Crée une liste contenant les emplacements, sous forme de sous-liste ((a,b)(c,d)), des chiffres déjà présents afin de ne pas modifier la liste de base.

**Paramètres:**

- `tableauGrille` (Entrée) : tableau, liste contenant tous les chiffres de la table de sudoku avec tous les emplacements vides représentés par des -1.

**Résultat:**

Tableau d'entiers.

---

**Procédure :** _afficherGrille_

Affiche de manière plus lisible, avec les chiffres pour les rangées et les lettres pour les colonnes, ainsi que les traits de séparation.
Les emplacements vides (ou -1) seront représentés par des '.'.

**Paramètres:**

- `tableauGrille` (Entrée) : tableau, liste contenant tous les chiffres de la table de sudoku avec tous les emplacements vides représentés par des -1.

---

**Procédure :** _entreeSaisie_

Demande à l'utilisateur de rentrer l'emplacement à modifier sous forme (<RANGEE> <espace> <COLONNE>).
Fait les vérifications nécessaires :
- Si l'emplacement existe.
- Si l'emplacement est déjà occupé, propose de remplacer ou d'annuler.
- Si l'emplacement est hors de la limite de la grille.
- Si la saisie est correcte (entre 1 et 9).
- Si le chiffre saisi est déjà dans la case (3 par 3).
- Si le chiffre saisi est déjà dans la rangée/colonne.

**Paramètres:**

- `listeEmplacementBloque` (Entrée) : tableau , liste des emplacement natifs qui ne peuvent pas changer.

**Retourne:**

- `emplacementUtil` (Sortie) : tableau, liste contenant l'emplacement que l'utilisateur veut modifier.
- `chiffreUser` (Sortie) : entier, chiffre que l'utilisateur veut insérer.

---

**Procédure :** _modifieGrille_

Prend le tableau actuel et le modifie avec la demande de l'utilisateur.
Remplace si nécessaire.

**Paramètres:**

- `emplacementUtil` (Sortie) : tableau, liste contenant l'emplacement que l'utilisateur veut modifier.
- `chiffreUser` (Sortie) : entier, chiffre que l'utilisateur veut insérer.
- `tableauGrille` (Entrée) : tableau, la liste donnée en paramètres mais modifiée.

**Retourne:**

- `tableauGrille` (Entrée) : tableau, la liste donnée en paramètres mais modifiée.

---

**Procédure :** _verifieGrille_

Vérifie le tableau s'il est complet et retourne en conséquence si la partie continue.

**Paramètres:**

- `tableauGrille` (Entrée) : tableau, liste contenant tous les chiffres de la table de sudoku avec tous les emplacements vides représentés par des -1.

**Retourne:**

Booléen, vrai pour continuer la partie, faux sinon.

---

**Procédure :** _afficherComptage_

Permet d'afficher le nombre de coups utilisés pour remplir la table de Sudoku.

**Paramètres:**

- `compteur` (Entrée) : entier, incrémenté à chaque tour, donnant à la fin le nombre de coups.
---