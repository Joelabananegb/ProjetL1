#ifndef __FLOTE_H__
#define __FLOTE_H__

typedef struct Voiture{
  int imat;
  int nb_km;
  int type;
}Voiture;

typedef struct Flotte{
  int nb_voit;
  Voiture **TabV;
}Flotte;

Flotte *CreeFlotte(int);
void InitialiseeRandom(Flotte *);
void Afficher(Flotte *);
void DesallouerFlotte(Flotte **F);
void AfficherPlusAncienne(Flotte *F);

#endif
