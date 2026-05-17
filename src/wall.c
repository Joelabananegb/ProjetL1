#include "wall.h"

Walls *InitWalls(SDL_Texture *texture)
{
  Walls *walls = malloc(sizeof(Walls));
  walls->textureGen = texture;
  walls->head = NULL;
  return walls;
}

void CreatWall(Walls *walls, int x)
{
  Wall *newWall = malloc(sizeof(Wall));
  newWall->rect = (SDL_Rect){50,16,27,16};
  newWall->destRect = (SDL_Rect){x * 90, (600 / 2) + 70, 80, 80};
  newWall->texture = walls->textureGen;
  newWall->health = 5;
  newWall->next = walls->head;
  walls->head = newWall;
}

void ResetWalls(Walls *walls)
{
  Wall *current = walls->head;
  while (current != NULL)
  {
    Wall *tmp = current;
    current = current->next;
    free(tmp);
  }
  walls->head = NULL;
}
