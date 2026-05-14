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

  short velocity;
  struct Canar *next;
} Canar;

typedef struct
{
  Canar *head;
  int numberOfCanar;
} Canars;

enum Moves 
{
  LEFT,
  RIGTH,
  BOTTOM
};


Canars *InitCanar();
void UpdateAll(Canars *);
void ResetCanars(Canars *);
void FreeCanar(Canars **);
void AddCanar(Canars *, int, int, SDL_Renderer *);
void MoveCanar(Canars *);
#endif 
