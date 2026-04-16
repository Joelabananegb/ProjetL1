#ifndef FLOTE_H
#define FLOTE_H

typedef struct Voiture{
  int imat;
  int nb_km;
  int type;
}Voiture;

typedef struct Flotte{
  int nb_voit;
  Voiture **TabV;
}Flotte;

Flotte *cree_flotte(int);
void initialisee_random(Flotte *);
void afficer(Flotte *);
void desalloue_flotte(Flotte **F);
void afficher_plus_ancienne(Flotte *F);

#endif
