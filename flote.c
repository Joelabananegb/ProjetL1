#include "flote.h"
#include <stdio.h>
#include <stdlib.h>

Flotte *CreeFlotte(int n){
  Flotte *flotte = malloc(sizeof(Flotte));
  flotte->nb_voit = n;
  flotte->TabV = malloc(sizeof(Voiture)*n);
  for (int i = 0; i<n; i++){
    flotte->TabV[i] = NULL;
  }
  return flotte;
}
<<<<<<< HEAD

void initialisee_random(Flotte *flotte){
=======
void InitialiseeRandom(Flotte *flotte){
>>>>>>> 3fe4c679bf560a2d756f49712574d4b4f12614c6

  for (int i= 0; i<flotte->nb_voit; i++){
    flotte->TabV[i]=malloc(sizeof(Voiture));
    flotte->TabV[i]->=rand() % ();
    flotte->
  }
}