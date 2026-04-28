#ifndef CANAR_H
#define CANAR_H

#include <stdbool.h>

typedef struct Canar {
  int x, y;
  int velocity;
  bool alive;
  struct Canar *next;
} Canar;

typedef struct {
  Canar *head;
  int lvl;
} ListeCanar;

ListeCanar *InitCanar(int);
void FreeCanar(ListeCanar **);
void AjouterCanar(ListeCanar *, int, int);
void AfficherCanar(ListeCanar *, Affichage *);
void MouveCanar(ListeCanar *);
#endif 
