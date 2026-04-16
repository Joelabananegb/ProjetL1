#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Affichage.h"

/* Alloue et initialise une grille */
Affichage * AffichageInit(int largeur, int hauteur){
  int x, y;
  Affichage *grille;
  grille = malloc(sizeof(Affichage));
  grille->largeur=largeur; 
  grille->hauteur=hauteur;
  grille->tab=malloc(hauteur*sizeof(char **));
  for(x=0;x<hauteur;x++){
    grille->tab[x]=malloc(largeur*sizeof(char *));
    for (y=0;y<largeur;y++)
       grille->tab[x][y]=malloc(7*sizeof(char)); // Une case peut faire 6 caractères ASCII pour les séquences d'échappement
  }
  return grille;
}

/* Desallocation de la grille */
void AffichageDesallouer(Affichage **grille){
  int x,y;
  for (x=0;x<(*grille)->H;x++){
    for (y=0;y<(*grille)->L;y++)
       free((*grille)->tab[x][y]);    
    free((*grille)->tab[x]);
     }
  free((*grille)->tab);
  free(*grille);
  *grille=NULL;
}


/* Remplit une grille de vide */
void Affichage_vider(Affichage *grille){
  int x,y;
  for (x=0; x<grille->hauteur; x++)
    for (y=0; y<grille->largeur; y++){
       strcpy(grille->tab[x][y], " "); /* met une case vide */
    }
}

void Affichage_cadre(Affichage *A){
  int x,y;
   
  /* Cadre */
  for (x=0;x<grille->hauteur;x++){
      strcpy(grille->tab[x][0],"\33[42m ");
      strcpy(grille->tab[x][A->largeur-1],"\33[42m ");
  }
  for (y=0;y<grille->largeur;y++){
      strcpy(grille->tab[0][y],"\33[42m ");
      strcpy(grille->tab[grille->hauteur-1][y],"\33[42m ");
  }

}


/* Affiche une grille dans le terminal */
void Affichage_dessiner(Affichage *grille){
  int x, y;
  
  printf("\33[2J"); /* Efface tout l'ecran */
  printf("\33[H");  /* Deplace le curseur en position (0,0) */ 
  
  for (x=0;x<grille->hauteur;x++){
    for (y=0;y<grille->largeur;y++)  /* Affiche les cases de la grille */
      printf("%s\033[00m", A->tab[x][y]);          
    printf("\33[1E");     /* Retour à la ligne */
 }

  printf("\033[00m"); /* Declare le fond noir pour la suite */
  printf("\33[1E");
}