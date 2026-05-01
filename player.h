#ifndef CANON_H
#define CANON_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 896

typedef struct{
  short velocity;                /* Nombre de cases de déplacement d'un Player à chaque appui */
  int health, maxHealth;
  int score, highScore;
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

void FreePlayer(Player **);

#endif 


