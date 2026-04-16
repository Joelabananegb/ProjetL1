#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include <stdlib.h>
#include <stdio.h>


/* Structure necessaire aux fonctions d affichage*/
typedef struct{  
  int largeur, hauteur;     /* Largeur, Hauteur de l'affichage */
  char *** tab; /* Tableau à deux dimensions de chaînes de caractères ASCII */
} Affichage;


Affichage * Affichage_initialiser(int, int );   /* Alloue et initialise */
void Affichage_desallouer(Affichage **);           
void Affichage_cadre(Affichage *);                /* Place un cadre autour de l'Affichage */
void Affichage_vider(Affichage *);                /* Remplit l'Affichage de case noire */
void Affichage_dessiner(Affichage *);             /* Affiche le tableau à l'écran */
#endif
