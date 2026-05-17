#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

typedef struct Wall {
  SDL_Rect rect;
  SDL_Rect destRect;
  SDL_Texture *texture;
  int health;
  struct Wall *next;
} Wall;

typedef struct walls {
  Wall *head;
  SDL_Texture *textureGen;
} Walls;

Walls *InitWalls(SDL_Texture *);
void CreatWall(Walls *, int);
void ResetWalls(Walls *);
#endif
