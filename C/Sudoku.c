#include <stdio.h>
#include <stdlib.h>
#define TAILLE 9

// Constantes
const int CHIFFRE_MAX = 9 ;
const int CHIFFRE_MIN = 1 ;

// Typedef

typedef int tGrille[TAILLE][TAILLE]; 

// Prototype / Entête


// Main

int main (){


    return EXIT_SUCCESS;
}



// Procédures / Fonctions

void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
        fclose(f);
    }
    
}

void afficherGrille(tGrille g){
    int compteur = 1 ;
    int rangeeAffichage ;
    
    printf("\n");
    printf("    1 2 3   4 5 6   7 8 9 \n");
    printf("  +-------+-------+-------+ \n");
    for (int rangee = 0 ; rangee < TAILLE ; rangee++)
    {
        rangeeAffichage = rangee + 1 ;
        if ((rangee % 3) == 0 )
        {
            printf("  +-------+-------+-------+ \n");
        }
        printf("%d  |" , rangeeAffichage);
        for (int emplacement = 0 ; emplacement < TAILLE ; emplacement++)
        {
            if ((compteur % 3) == 0 )
            {
                if (g[rangee][emplacement] >= CHIFFRE_MIN && g[rangee][emplacement] <= CHIFFRE_MAX )
                {
                    printf(" %d |", g[rangee][emplacement]);
                }
                else
                {
                    printf(" . |");
                }
            }
            if (g[rangee][emplacement] >= CHIFFRE_MIN && g[rangee][emplacement] <= CHIFFRE_MAX )
            {
                printf(" %d", g[rangee][emplacement]);
            }
            else
            {
                printf(" .");
            }
            compteur++ ;

        }
    }

}

