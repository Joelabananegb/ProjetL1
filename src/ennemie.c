#include "ennemie.h"

enum Moves direction = RIGTH;

Canars *InitCanar(SDL_Texture *texture)
{
  Canars *canars = malloc(sizeof(Canars));
  canars->head = NULL;
  canars->numberOfCanar = 0;
  canars->numberInit = 0;
  canars->textureGen = texture;
  return canars;
}

void FreeCanar(Canars **canars)
{
  Canar *current = (*canars)->head;

  while(current != NULL)
  {
    Canar *tmp = current;
    current = current->next;
    free(tmp);
  }
  free((*canars));
  (*canars) = NULL;
}

void AddCanar(Canars *canars, int x, int y)
{
  Canar *newCanar = malloc(sizeof(Canar));
  newCanar->rect = (SDL_Rect){0,0, 16, 16};
  newCanar->destRect = (SDL_Rect){x,y,64,64};
  newCanar->texture = canars->textureGen;
  newCanar->velocity = 16;
  newCanar->next = canars->head;
  canars->head = newCanar;
  canars->numberOfCanar++;
}


void UpdateAll(Canars *canars)
{
  Canar *current = canars->head;
  while(current!=NULL){
    current->destRect.y += 10;
    current = current->next;
  }
}

void MoveCanar(Canars *canars)
{
  Canar *current = canars->head;

  while (current != NULL)
  {
    current->destRect.x += current->velocity * direction;
    current = current->next;
  }

  bool hitEdge = false;

  current = canars->head;

  while (current != NULL)
  {
    if (current->destRect.x <= 0 || current->destRect.x >= 700)
    {
      hitEdge = true;
      break;
    }
    current = current->next;
  }

  if (hitEdge)
  {
    direction *= -1;
    current = canars->head;
    while (current != NULL)
    {
      current->destRect.y += 16;
      current = current->next;
    }
  }
}

Canar *GetRandomCanar(Canars *canars)
{
  if (canars->head == NULL) return NULL;

  int target = rand() % canars->numberOfCanar;

  Canar *current = canars->head;

  for (int i = 0; i < target; i++)
  {
    current = current->next;
  }

  return current;
}

void Attack(Canars *canars, Flechettes *flechettes)
{
    Canar *shooter = GetRandomCanar(canars);

    if (shooter == NULL) return;

    AddFlechette(flechettes, shooter->destRect.x + shooter->destRect.w / 2 - 8, shooter->destRect.y + shooter->destRect.h + 10, 8, ENEMYBULLET);
}
