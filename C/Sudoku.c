#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 3
#define TAILLE N * N

// Constantes
const int CHIFFRE_MAX = 9 ;
const int CHIFFRE_MIN = 1 ;
const int CHIFFRE_VIDE = 0 ;



// Typedef

typedef int tGrille[TAILLE][TAILLE]; 

// Prototype / Entête

void chargerGrille(tGrille g);
void afficherGrille(tGrille g);
int verifierGrillePleine(tGrille g);
void saisir(int *valeur);
int possible(tGrille g, int colonne, int ligne, int valeur);

// Main

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
        if (grille1[numLigne][numColonne] != 0)
        {
            printf("IMPOSSIBLE, la case n'est pas libre. \n");
        }
        else
        {
            printf("Valeur à insérer ? \n");
            printf(" %d %d ", numLigne-1 , numColonne-1);
            saisir(&valeur);
            printf(" %d %d ", numLigne-1 , numColonne-1);
            if (possible(grille1, numLigne, numColonne, valeur))
            {
                grille1[numLigne-1][numColonne-1] = valeur ;
            }
            afficherGrille(grille1);
            grillePleine = verifierGrillePleine(grille1);
        }
        
    }
    printf("Grille pleine, fin de partie \n");

    return EXIT_SUCCESS;
}



// Procédures / Fonctions

void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? \n");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
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

int verifierGrillePleine(tGrille g){
    int ligne = 0;
    int colonne = 0;
    int grillePleine = 1;

    while ((grillePleine = 1) && (ligne <= TAILLE - 1 ))
    {
        while ((grillePleine = 1) && (colonne <= TAILLE - 1 ))
        {
            if ((g[ligne][colonne]) == CHIFFRE_VIDE)
            {
                grillePleine = 0;
            }
            else
            {
                colonne++;
            }
        }
    ligne++ ;
    } 
    return grillePleine ;
}

void saisir(int *valeur)
{
    char saisieUtilisateur ;
    int saisieUtilisateurEntiere;
    int saisieCorrecte = 0 ;
    
    do
    {
        scanf("%s", &saisieUtilisateur);
        if (sscanf(&saisieUtilisateur, "%d", &saisieUtilisateurEntiere) != 0)
        {
            if ((saisieUtilisateurEntiere >= CHIFFRE_MIN) && (saisieUtilisateurEntiere <= TAILLE))
            {
                saisieCorrecte = 1;
                *valeur = saisieUtilisateurEntiere;
            }
            else
            {
                printf("Entrez une valeur entière entre %d et %d \n", CHIFFRE_MIN , TAILLE);
            }
            
        }
        else
        {
            printf("Entrez une valeur entière entre %d et %d \n", CHIFFRE_MIN , TAILLE);
        }
    
    } while (saisieCorrecte == 0);

}

int possible(tGrille g, int colonne, int ligne, int valeur)
{
    int possible = 1 ;
    int parcoursLigne = 0;
    int parcoursColonne = 0;

    while ((parcoursLigne < TAILLE) && (possible = 1))
    {
        if (g[parcoursColonne][ligne] == valeur)
        {
            possible = 0 ;
        }
        else
        {
            parcoursColonne++;
        }
        
    }
    parcoursColonne = 0 ;

    while ((parcoursColonne < TAILLE) && (possible = 1))
    {
        if (g[parcoursLigne][colonne] == valeur)
        {
            possible = 0 ;
        }
        else
        {
            parcoursLigne++;
        }
        
    }
    parcoursLigne = 0 ;


    int bloclocCourrantColonne = colonne / 3 ;
    int blocCourrantLigne = ligne / 3 ;

    
    while ((blocCourrantLigne < N) && (possible = 1))
    {
        while ((bloclocCourrantColonne < N) && (possible = 1))
        {
            if(g[blocCourrantLigne][bloclocCourrantColonne] == valeur)
            {
                possible = 0 ;
            }
            else
            {
                bloclocCourrantColonne++;
            }
        }
        blocCourrantLigne++;
    }
    return possible;
}
