#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include <stdlib.h>
#include <stdio.h>


/* Structure necessaire aux fonctions d affichage*/
typedef struct Affichage
{  
  int largeur, hauteur;     /* Largeur, Hauteur de l'affichage */
  char *** tab; /* Tableau à deux dimensions de chaînes de caractères ASCII */
} Affichage;


Affichage *AffichageInit(int, int );   /* Alloue et initialise */
void AffichageDesallouer(Affichage **);           
void AffichageCadre(Affichage *);                /* Place un cadre autour de l'Affichage */
void AffichageVider(Affichage *);                /* Remplit l'Affichage de case noire */
void AffichageDessiner(Affichage *);             /* Affiche le tableau à l'écran */
#endif
