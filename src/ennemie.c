#include "ennemie.h"

#define elif else if

Canars *InitCanar()
{
  Canars *canars = malloc(sizeof(Canars));
  canars->head = NULL;
  canars->numberOfCanar = 0;
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
  canars->numberOfCanar++;
}

void ResetCanars(Canars *canars){
  ;
}


enum Moves direction = RIGTH;

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
  Canar *prev = NULL;

  while (current != NULL)
  {
    printf("x = %d\n", current->destRect.x);
    if (direction == RIGTH){
      current->destRect.x += current->velocity;
      if (current->destRect.x == 600){
        UpdateAll(canars);
        direction = LEFT;
      }
    }else{
      current->destRect.x -= current->velocity;
      if (current->destRect.x == 0)
      {
        UpdateAll(canars);
        direction = RIGTH;
      }
    }

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

      SDL_DestroyTexture(tmp->texture);
      free(tmp);
      canars->numberOfCanar--;
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }
}
