#ifndef CANON_H
#define CANON_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef struct{
  int velocity;                /* Nombre de cases de déplacement d'un Player à chaque appui */
  int health, max_health;
  int score, high_score;
  int attack;

  SDL_Rect rect;
  SDL_Rect destRect;
  SDL_Texture *texture;

  bool alive;
} Player;

Player *InitPlayer(SDL_Renderer *, const char *);
void MoveLeft(Player *);
void MoveRight(Player *);
void MoveUp(Player *);
void MoveDown(Player *);

//void PlayerDesallouer(Canon **);
//void PlayerAction(Canon *, enum action_canon, ListeFlechette *);
//void PlayerAfficher(Canon *, Affichage* );

#endif 


