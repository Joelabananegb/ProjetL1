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
  newWall->rect = (SDL_Rect){50,20,27,16};
  newWall->destRect = (SDL_Rect){x * 90, (600 / 2) + 70, 80, 80};
  newWall->texture = walls->textureGen;
  newWall->health = 3;
  newWall->next = walls->head;
  walls->head = newWall;
}

void ChangeWall(Walls *walls)
{
  Wall *current = walls->head;
  while (current != NULL){
    if(current->health < 3)
    {
      current->rect.y += 64;
    }
    current = current->next;
  }
}
