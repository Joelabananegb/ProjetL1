#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Canon.h"

Canon* Canon_initialiser(int pos_min, int pos_max, int hauteur_aff){
   Canon *canon= malloc(sizeof(Canon));
   canon->hauteur=2;
   canon->largeur=11;
   canon->ypos=(pos_min+pos_max)/2; 
   canon->ypos_old=C->xpos; 
   canon->xpos= hauteur_aff-C->hauteur-1;
   canon->pos_min=pos_min+3; 
   canon->pos_max=pos_max-3;
   canon->pas=5;
   return canon;
}

void CanonDesallouer(Canon** canon){
  free(*canon);
  *canon=NULL;
}


void CanonAction(Canon *canon, enum action_canon actC){

  canon->ypos_old= canon->ypos; 

  switch (actC){
    case Gauche_canon:
      caonon->ypos-=canon->pas;
      break;
    case Droite_canon:
      canon->ypos+=canon->pas;
      break;  
    case Tir:
      // Lance une fléchette
      break;       
  }

  if ((C->ypos<C->pos_min)||(C->ypos>C->pos_max-C->largeur)){
   C->ypos=C->ypos_old;
  }

}

void Canon_afficher(Canon *C, Affichage* A){ 
  int x,y;
  for(x=C->xpos; x<C->xpos+C->hauteur; x++)
    for (y=C->ypos; y<C->ypos+C->largeur; y++)
      strcpy(A->tab[x][y],"\33[44m ");
  strcpy(A->tab[C->xpos-1][C->ypos+C->largeur/2-1],"\33[44m ");
  strcpy(A->tab[C->xpos-1][C->ypos+C->largeur/2],"\33[44m ");
  strcpy(A->tab[C->xpos-1][C->ypos+C->largeur/2+1],"\33[44m ");
  strcpy(A->tab[C->xpos-2][C->ypos+C->largeur/2-1],"\33[44m ");
  strcpy(A->tab[C->xpos-2][C->ypos+C->largeur/2],"\33[44m ");
  strcpy(A->tab[C->xpos-2][C->ypos+C->largeur/2+1],"\33[44m ");

}



