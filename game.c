#include "game.h"

void HomeScreen(SDL_Renderer *render, SDL_Texture *background)
{
  SDL_Rect destRect = {0,0,514,514};
  SDL_RenderCopy(render, background, NULL, &destRect);
}

void RenderEnnemies(Canars *canars, SDL_Renderer *render)
{
  Canar *current = canars->head;

  while (current != NULL)
  {
    SDL_RenderCopy(render, current->texture, &current->rect, &current->destRect);
    current = current->next;
  }
}

void LevelOne(SDL_Renderer *render, Canars *canars)
{
  for (int i = 0; i <= 5; i++) {
    AddCanar(canars, i*58,0, render);
    printf("add\n"); }
}

void RenderProjectiles(Flechettes *flechettes, SDL_Renderer *render)
{
  Flechette *current = flechettes->head;
  while(current != NULL)
  {
    SDL_RenderCopy(render, current->texture, &current->rect, &current->destRect);
    current = current->next;
  }
}

void RenderPlayer(Player *player, SDL_Renderer *render)
{
  SDL_RenderCopy(render, player->texture, &player->rect,&player->destRect);
}

void Game(SDL_Renderer *render, Player *player, Flechettes *flechettes, Canars *canars)
{
  RenderPlayer(player, render);
  RenderProjectiles(flechettes,render);
  MoveFlechettes(flechettes);
  RenderEnnemies(canars, render);
  MoveCanar(canars);
  SDL_Event event;
  SDL_PollEvent(&event);
  
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  if(keystate[SDL_SCANCODE_RIGHT])
  {
    MoveRight(player);
  }

  if (keystate[SDL_SCANCODE_LEFT])
  {
    MoveLeft(player);
  }

  if(keystate[SDL_SCANCODE_DOWN])
  {
    MoveDown(player);
  }

  if (keystate[SDL_SCANCODE_UP])
  {
    MoveUp(player);
  }
  
  static int spacePressed = 0;

  if (keystate[SDL_SCANCODE_SPACE])
  {
    if (!spacePressed)
    {
      AddFlechette(flechettes, player->destRect.x + 4, player->destRect.y - 32, render);
    }
    spacePressed = 1;
  }
  else
  {
      spacePressed = 0;
  }

  SDL_RenderPresent(render);
  SDL_Delay(16);
}

void FreeAll(Player *player, Flechettes *flechettes, Canars *canars){
  free(player);
  player = NULL;
  FreeFlechettes(&flechettes);
  FreeCanar(&canars);
}
