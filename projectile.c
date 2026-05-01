#include <stdio.h>
#include "projectile.h"

Flechettes *InitFlechettes(){
  Flechettes *projectiles = malloc(sizeof(Flechettes));
  projectiles->head = NULL;
  projectiles->ammo = 0;
  return projectiles;
}

void FreeFlechettes(Flechettes **flechettes)
{
  Flechette *current = (*flechettes)->head;
  while (current != NULL)
  {
    Flechette *tmp = current;
    current = current->next;
    free(tmp);
  }
  free((*flechettes));
  (*flechettes) = NULL;
}

void AddFlechette(Flechettes *flechettes, int x, int y, SDL_Renderer *render)
{
  if (flechettes->ammo <= MAX_AMMO)
  {
    Flechette *newFlechette = malloc(sizeof(Flechette));
    newFlechette->rect = (SDL_Rect){32, 0, 16, 16};
    newFlechette->destRect = (SDL_Rect){x,y,64,64};
    newFlechette->texture = IMG_LoadTexture(render,"./assets/SpaceInvaders.png");
    newFlechette->velocity = 3;
    newFlechette->next = flechettes->head;
    flechettes->head = newFlechette;
    flechettes->ammo++;
  }
}

void MoveFlechettes(Flechettes *flechettes)
{
  Flechette *current = flechettes->head;
  Flechette *prev = NULL;

  while (current != NULL)
  {
    current->destRect.y -= current->velocity; // monte vers le haut

    if (current->destRect.y <= 0)
    {
      if (prev == NULL)
      {
        flechettes->head = current->next;
      }
      else
      {
        prev->next = current->next;
      }

      Flechette *tmp = current;
      current = current->next;
      flechettes->ammo--;
      free(tmp);
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }

}
