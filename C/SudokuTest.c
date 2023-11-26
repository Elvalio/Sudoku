#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3
#define TAILLE N * N

// Constantes
const int CHIFFRE_MAX = 9;
const int CHIFFRE_MIN = 1;
const int CHIFFRE_VIDE = 0;

// Typedef
typedef int tGrille[TAILLE][TAILLE];

// Prototype / Entête
void chargerGrille(tGrille g);
void afficherGrille(tGrille g);
int verifierGrillePleine(tGrille g);
void saisir(int *valeur);
int possible(tGrille g, int colonne, int ligne, int valeur);

// Main
int main() {
    tGrille grille1;
    int numLigne, numColonne, valeur, grillePleine;

    chargerGrille(grille1);
    while (grillePleine == 0) {
        afficherGrille(grille1);
        printf("Indices de la case ? \n");
        printf("Ligne : \n");
        saisir(&numLigne);
        printf("Colonne : \n");
        saisir(&numColonne);
        if (grille1[numLigne - 1][numColonne - 1] != 0) {
            printf("IMPOSSIBLE, la case n'est pas libre. \n");
        } else {
            printf("Valeur à insérer ? \n");
            printf(" %d %d ", numLigne - 1, numColonne - 1);
            saisir(&valeur);
            printf(" %d %d ", numLigne - 1, numColonne - 1);
            if (possible(grille1, numColonne - 1, numLigne - 1, valeur)) {
                grille1[numLigne - 1][numColonne - 1] = valeur;
            } else {
                printf("Impossible d'insérer la valeur à cet emplacement.\n");
            }
            afficherGrille(grille1);
            grillePleine = verifierGrillePleine(grille1);
        }
    }
    printf("Grille pleine, fin de partie \n");

    return EXIT_SUCCESS;
}

// Procédures / Fonctions

void chargerGrille(tGrille g) {
    char nomFichier[30];
    FILE *f;
    printf("Nom du fichier ? \n");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f == NULL) {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE * TAILLE, f);
        fclose(f);
    }
}

void afficherGrille(tGrille g) {
    int rangeeAffichage;

    printf("\n");
    printf("     1 2 3   4 5 6   7 8 9 \n");
    for (int rangee = 0; rangee < TAILLE; rangee++) {
        rangeeAffichage = rangee + 1;
        if ((rangee % N) == 0) {
            printf("   +-------+-------+-------+ \n");
        }
        printf("%d  |", rangeeAffichage);
        for (int emplacement = 0; emplacement < TAILLE; emplacement++) {
            if ((emplacement % N) == 0 && emplacement != 0) {
                printf(" |");
            }

            if (g[rangee][emplacement] >= CHIFFRE_MIN && g[rangee][emplacement] <= CHIFFRE_MAX) {
                printf(" %d", g[rangee][emplacement]);
            } else {
                printf(" .");
            }
        }
        printf(" |\n");
    }
    printf("   +-------+-------+-------+ \n");
}

int verifierGrillePleine(tGrille g) {
    int grillePleine = 1;
    for (int ligne = 0; ligne < TAILLE; ligne++) {
        for (int colonne = 0; colonne < TAILLE; colonne++) {
            if (g[ligne][colonne] == CHIFFRE_VIDE) {
                grillePleine = 0;
                return grillePleine;
            }
        }
    }
    return grillePleine;
}

void saisir(int *valeur) {
    char saisieUtilisateur[10];
    int saisieUtilisateurEntiere;
    int saisieCorrecte = 0;

    do {
        scanf("%s", saisieUtilisateur);
        if (sscanf(saisieUtilisateur, "%d", &saisieUtilisateurEntiere) == 1) {
            if (saisieUtilisateurEntiere >= CHIFFRE_MIN && saisieUtilisateurEntiere <= TAILLE) {
                saisieCorrecte = 1;
                *valeur = saisieUtilisateurEntiere;
            } else {
                printf("Entrez une valeur entière entre %d et %d \n", CHIFFRE_MIN, TAILLE);
            }
        } else {
            printf("Entrez une valeur entière entre %d et %d \n", CHIFFRE_MIN, TAILLE);
        }

    } while (saisieCorrecte == 0);
}

int possible(tGrille g, int colonne, int ligne, int valeur) {
    // Vérification dans la ligne
    for (int i = 0; i < TAILLE; i++) {
        if (g[ligne][i] == valeur) {
            return 0;
        }
    }

    // Vérification dans la colonne
    for (int i = 0; i < TAILLE; i++) {
        if (g[i][colonne] == valeur) {
            return 0;
        }
    }

    // Vérification dans le bloc
    int debutBlocLigne = N * (ligne / N);
    int debutBlocColonne = N * (colonne / N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (g[debutBlocLigne + i][debutBlocColonne + j] == valeur) {
                return 0;
            }
        }
    }

    return 1;
}
