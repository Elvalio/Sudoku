#include <stdio.h>
#include <stdlib.h>
#define TAILLE 9

// Constantes

// Typedef

typedef int tGrille[TAILLE][TAILLE]; 

// Prototype / Entête


// Main

int main (){

    afficherGrille();

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

void afficherGrille(){

    printf("     1 2 3   4 5 6   7 8 9");
    printf("   +-------+-------+-------+ ");
    printf("1  | 9 . . | . . . | . . . |");


}

