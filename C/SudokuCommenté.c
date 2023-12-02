/**
 * \page Général
 * 
 * \author TROULE Harry
 * \version 1.0
 * \date 3 décembre 2023
 * 
 * 
 * Ce programme permet de jouer au Sudoku en partant d'un fichier de base nommé Grille<numéro>.sud
 * avec les vérifications nécessaires.
 *  
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * \def N
 * \brief Taille d'une ligne d'un bloc
 * 
 * Définit la taille d'une ligne d'un bloc de la grille.
*/
#define N 3

/**
 * \def TAILLE
 * \brief Taille d'une ligne complète de la grille ou d'une colonne complète
 * 
 * Définit la taille d'une ligne complète d'une grille de Sudoku ou colonne.
*/
#define TAILLE N * N

// Constantes

/**
 * \def CHIFFRE_MAX
 * \brief Chiffre maximum acceptable
 * 
 * Définit le chiffre maximum que le programme peut accepter 
*/
const int CHIFFRE_MAX = 9 ;

/**
 * \def CHIFFRE_MIN
 * \brief Chiffre minimum acceptable
 * 
 * Définit le chiffre minimum que le programme peut accepter 
*/
const int CHIFFRE_MIN = 1 ;

/**
 * \def CHIFFRE_VIDE
 * \brief Chiffre correspondant à un vide
 * 
 * Définit le chiffre correspondant à un vide dans la grille du Sudoku
*/
const int CHIFFRE_VIDE = 0 ;

// Typedef

/**
 * \typedef tGrille
 * \brief Structure d'une grille de Sudoku
 * 
 * Permet de jeu de créer un double tableau pour mettre la grille du jeu
*/
typedef int tGrille[TAILLE][TAILLE];


// Prototype / Entête

void chargerGrille(tGrille g);
void afficherGrille(tGrille g);
int verifierGrillePleine(tGrille g);
void saisir(int *valeur);
int possible(tGrille g, int colonne, int ligne, int valeur);

// Main
/**
 * \fn int main()
 * \brief Programme principal
 * \return Code de sortie du programme (0 : sortie normale).
 * 
 * Le programme principal utilise les différentes procédures afin de permettre au joueur de remplir
 * une grille de sudoku, avec de multiples vérifications, tant que la grille n'est pas remplie.  
*/
int main (){
    tGrille grille1 ;
    int numLigne, numColonne, valeur, grillePleine ;


    chargerGrille(grille1);
    while (grillePleine == 0)
    {
        afficherGrille(grille1);
        printf("Indices de la case ? \n");
        printf("Ligne : \n");
        saisir(&numLigne);
        printf("Colonne : \n");
        saisir(&numColonne);
        if (grille1[numLigne - 1][numColonne - 1] != 0)
        {
            printf("IMPOSSIBLE, la case n'est pas libre. \n");
        }
        else
        {
            printf("Valeur à insérer ? \n");
            saisir(&valeur);
            if (possible(grille1, numColonne-1, numLigne-1, valeur))
            {
                grille1[numLigne-1][numColonne-1] = valeur ;
            }
            grillePleine = verifierGrillePleine(grille1);
        }
        
    }
    afficherGrille(grille1);
    printf("Grille pleine, fin de partie \n");

    return EXIT_SUCCESS;
}



// Procédures / Fonctions


/**
 * \fn void chargerGrille(tGrille g)
 * \brief Fonction qui charge la grille de Sudoku
 * \param g : paramètre d'entrée qui représente le fichier d'entrée
 * 
 * Charge une grille sudoku à partir d'un fichier.
*/
void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? \n");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
        exit(EXIT_FAILURE);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
        fclose(f);
    }
    
}


/**
 * \fn void afficherGrille(tGrille g)
 * \brief Fonction qui affiche la grille de Sudoku avec le bon formatage
 * \param g : paramètre d'entrée qui représente le fichier d'entrée
 * 
 * Affiche la grille avec les chiffres d'identification de colonnes et lignes, le formatage avec
 * les lignes de séparation est aussi appliqué
*/
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


/**
 * \fn verifierGrillePleine(tGrille g)
 * \brief Fonction qui vérifie si la grille est remplie 
 * \param g : paramètre d'entrée qui représente la grille de jeu
 * \return 1 si la grille est pleine, 0 sinon
 * 
 * Vérifie après chaque insertion de valeur dans le tableau si celui-ci est rempli
*/
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


/**
 * \fn void saisir(int *valeur)
 * \brief Fonction qui récupère et vérifie une entrée utilisateur
 * \param valeur : paramètre de sortie correspondant à l'entrée utilisateur
 * 
 * Attend une saisie et vérifie si elle correspond au bon format, retourne une erreur correspondante
*/
void saisir(int *valeur)
{
    char saisieUtilisateur[10] ;
    int saisieUtilisateurEntiere;
    int saisieCorrecte = 0 ;
    
    do
    {
        do
        {
            scanf("%s", saisieUtilisateur);
        } while (saisieUtilisateur);
        
        
        if (sscanf(saisieUtilisateur, "%d", &saisieUtilisateurEntiere) != 0)
        {
            printf("Test : %d", saisieUtilisateurEntiere);
            if ((saisieUtilisateurEntiere >= CHIFFRE_MIN) && (saisieUtilisateurEntiere <= TAILLE))
            {
                saisieCorrecte = 1;
                *valeur = saisieUtilisateurEntiere;
            }
            else
            {
                printf("L'entrée attendue est un chiffre entier compris entre %d et %d \n", CHIFFRE_MIN , TAILLE);
            }
            
        }
        else
        {
            printf("L'entrée attendue est un chiffre entier compris entre %d et %d \n", CHIFFRE_MIN , TAILLE);
        }
    
    } while (saisieCorrecte == 0);

}

/**
 * \fn possible(tGrille g, int colonne, int ligne, int valeur)
 * \brief Vérifie la possibilité de l'insertion d'une valeur
 * \param g : paramètre d'entrée qui correspond à la grille de jeu
 * \param colonne : paramètre d'entrée qui correspond à la colonne de l'insertion de la valeur
 * \param ligne : paramètre d'entrée qui correspond à la ligne de l'insertion de la valeur
 * \param valeur : paramètre d'entrée qui correspond à la valeur de l'insertion
 * 
 * Vérifie si une valeur peut être insérée en vérifiant la colonne, la ligne et le bloc de la saisie
*/
int possible(tGrille g, int colonne, int ligne, int valeur) {
    // Vérification dans la ligne
    for (int indiceColonne = 0; indiceColonne < TAILLE; indiceColonne++) {
        if (g[ligne][indiceColonne] == valeur) {
            printf("Erreur : La valeur ne peut pas être inséré dans cet emplacement\n");
            printf("-> Valeur déjà dans la ligne à l'emplacement %d %d \n",ligne + 1 , indiceColonne + 1 );
            return 0;
        }
    }

    // Vérification dans la colonne
    for (int indiceLigne = 0; indiceLigne < TAILLE; indiceLigne++) {
        if (g[indiceLigne][colonne] == valeur) {
            printf("Erreur : La valeur ne peut pas être inséré dans cet emplacement\n");
            printf("-> Valeur déjà dans la colonne à l'emplacement %d %d\n",indiceLigne + 1 , colonne + 1);
            return 0;
        }
    }

    // Vérification dans le bloc
    int debutBlocLigne = N * (ligne / N);
    int debutBlocColonne = N * (colonne / N);
    for (int indiceLigneBloc = 0; indiceLigneBloc < N; indiceLigneBloc++) {
        for (int indiceColonneBloc = 0; indiceColonneBloc < N; indiceColonneBloc++) {
            if (g[debutBlocLigne + indiceLigneBloc][debutBlocColonne + indiceColonneBloc] == valeur) {
                printf("Erreur : La valeur ne peut pas être inséré dans cet emplacement\n");
                printf("-> Valeur déjà dans le bloc");
                printf("-> Valeur déjà dans le bloc à l'emplacement %d %d\n",(debutBlocLigne + indiceLigneBloc) + 1, (debutBlocColonne + indiceColonneBloc) + 1 );
                return 0;
            }
        }
    }

    return 1;
}

