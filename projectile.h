#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#define MAX_AMMO 2

typedef struct Flechette
{
  int velocity;
  SDL_Rect rect;
  SDL_Rect destRect;
  SDL_Texture *texture;
  struct Flechette *next;
} Flechette;

typedef struct
{
  Flechette *head;
  int ammo;
} Flechettes;

Flechettes *InitFlechettes();
void FreeFlechettes(Flechettes **);
void AddFlechette(Flechettes *, int, int, SDL_Renderer *);
void MoveFlechettes(Flechettes *);
#endif
