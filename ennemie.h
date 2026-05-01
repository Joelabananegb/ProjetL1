#ifndef ENNEMIE_H
#define ENNEMIE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Canar
{
  SDL_Rect rect;
  SDL_Rect destRect;
  SDL_Texture *texture;

  float velocity;
  struct Canar *next;
} Canar;

typedef struct
{
  Canar *head;
} Canars;

Canars *InitCanar();
void FreeCanar(Canars **);
void AddCanar(Canars *, int, int, SDL_Renderer *);
void MoveCanar(Canars *);
#endif 
