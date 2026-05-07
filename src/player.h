#ifndef CANON_H
#define CANON_H

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct{
  short velocity;                /* Nombre de cases de déplacement d'un Player à chaque appui */
  int health, maxHealth;
  int score, highScore;
  int attack;

  SDL_Rect rect;
  SDL_Rect destRect;
  SDL_Texture *texture;
  SDL_Texture *heartTexture;
  SDL_Rect hearthRect;
  SDL_Rect heartDestRect;

  bool alive;
} Player;

Player *InitPlayer(SDL_Renderer *, const char *, const char *);
void ResetPlyer(Player *);
void MoveLeft(Player *);
void MoveRight(Player *);
void MoveUp(Player *);
void MoveDown(Player *);
void PlayerDamage(Player *);
void FreePlayer(Player **);
#endif 
