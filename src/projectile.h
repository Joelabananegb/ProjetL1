#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#define MAX_AMMO 3

typedef enum {
  PLAYERBULLET,
  ENEMYBULLET
} bulletType;

typedef struct Flechette
{
  short velocity;
  SDL_Rect rect;
  SDL_Rect destRect;
  SDL_Texture *texture;
  bulletType type;
  struct Flechette *next;
} Flechette;

typedef struct
{
  Flechette *head;
  int ammo;
  SDL_Texture *textureGen;
} Flechettes;

Flechettes *InitFlechettes(SDL_Texture *);
void FreeFlechettes(Flechettes **);
void AddFlechette(Flechettes *, int, int, int, bulletType);
void MoveFlechettes(Flechettes *);
#endif
