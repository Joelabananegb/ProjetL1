#include "flote.h"
#include <stdio.h>
#include <stdlib.h>

Flotte *cree_flotte(int n){
  Flotte *cr_flotte = malloc(sizeof(Flotte));
  cr_flotte->nb_voit = n;
  cr_flotte->TabV = malloc(sizeof(Voiture)*n);
  for (int i = 0; i<n; i++){
    cr_flotte->TabV[i] = NULL;
  }
  return cr_flotte;
}
void initialisee_random(Flotte *flotte){

  for (int i= 0; i<flotte->nb_voit; i++){
    flotte->TabV[i]=malloc(sizeof(Voiture));
    flotte->TabV[i]->=rand() % ();
    flotte->
  }
}
