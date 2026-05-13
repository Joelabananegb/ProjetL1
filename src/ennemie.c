#include "ennemie.h"

Canars *InitCanar()
{
  Canars *canars = malloc(sizeof(Canars));
  canars->head = NULL;
  return canars;
}

void FreeCanar(Canars **canars)
{
  Canar *current = (*canars)->head;

  while(current != NULL)
  {
    Canar *tmp = current;
    current = current->next;
    if (tmp->texture)
    {
      SDL_DestroyTexture(tmp->texture);
    }
    free(tmp);
  }
  
  free((*canars));
  (*canars) = NULL;
}

void AddCanar(Canars *canars, int x, int y, SDL_Renderer *render)
{
  Canar *newCanar = malloc(sizeof(Canar));
  newCanar->rect = (SDL_Rect){0,0, 16, 16};
  newCanar->destRect = (SDL_Rect){x,y,64,64};
  newCanar->texture = IMG_LoadTexture(render, "./assets/SpaceInvaders.png");
  newCanar->velocity = 1;
  newCanar->next = canars->head;
  canars->head = newCanar;
}
void ResetCanars(Canars *canars){
}

void MoveCanar(Canars *canars)
{
  Canar *current = canars->head;
  Canar *prev = NULL;

  while (current != NULL)
  {
    current->destRect.y += current->velocity;

    // suppression si hors écran
    if (current->destRect.y >= 514)
    {
      Canar *tmp = current;

      if (prev == NULL)
      {
        canars->head = current->next;
        current = canars->head;
      }
      else
      {
        prev->next = current->next;
        current = current->next;
      }

      free(tmp);
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }
}
