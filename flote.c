#include "flote.h"
#include <stdio.h>
#include <stdlib.h>

Flotte *CreeFlotte(int n)
{
  Flotte *flotte = malloc(sizeof(Flotte));
  flotte->nb_voit = n;
  flotte->TabV = malloc(sizeof(Voiture)*n);
  for (int i = 0; i<n; i++)
  {
    flotte->TabV[i] = NULL;
  }
  return flotte;
}

void InitialiseeRandom(Flotte *flotte)
{
  for (int i = 0; i<flotte->nb_voit; i++)
  {
    flotte->TabV[i] = malloc(sizeof(Voiture));
    flotte->TabV[i] = rand() % ();
    flotte->
  }
}
