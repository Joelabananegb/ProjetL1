#include "game.h"

void HomeScreen(SDL_Renderer *render, SDL_Texture *background)
{
  SDL_Rect destRect = {0,0,514,514};
  SDL_RenderCopy(render, background, NULL, &destRect);
}

void RenderPlayer(Player *player, SDL_Renderer *render)
{
  SDL_RenderCopy(render, player->texture, &player->rect,&player->destRect);
}

/*void InitGame(SDL_Renderer *render, Player *player)
{
  player = InitPlayer(render, "./assets/SpaceInvaders.png");
}*/

void Game(SDL_Renderer *render, Player *player)
{
  RenderPlayer(player, render);
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



  SDL_RenderPresent(render);
  SDL_Delay(16);
}

void FreeAll(Player *player){
  free(player);
  player = NULL;
}
