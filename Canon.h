#ifndef _CANON_H_
#define _CANON_H_

#include"Affichage.h"

enum action_canon {Gauche_canon, Droite_canon, Tir};

typedef struct{
  int largeur, hauteur;   /* Taille du rectangle de la base du canon */
  int pos_min, pos_max;   /* Position min (à gauche) et max (à droite) */
  int xpos, ypos;         /* Case supérieure gauche de la position du Canon */ 
  int pas;                /* Nombre de cases de déplacement d'un Canon à chaque appui */
  int ypos_old;           /* Position précédente du Canon */ 
} Canon;

Canon* Canon_initialiser(int , int , int );
void Canon_desallouer(Canon **);
void Canon_action(Canon *, enum action_canon actC);
void Canon_afficher(Canon *, Affichage *);


#endif 


