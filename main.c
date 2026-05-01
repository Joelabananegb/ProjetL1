#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include "game.h" // Contient les déclarations liées au jeu (player, monster, etc.)

int main()
{
  srand(time(NULL));
  Player *player = NULL;
  Flechettes *flechettes = NULL;
  Canars *canars = NULL;

  SDL_Window *window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,0);
  if (!window)
  {
    SDL_Log("Erreur de création fenêtre: %s", SDL_GetError());
    return 1;
  }
  
  SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!window)
  {
    SDL_Log("Erreur de création render: %s", SDL_GetError());
    return 1;
  }
 
  SDL_Texture *background = IMG_LoadTexture(render,"./assets/SpaceInvaders_Background.png");
  if (!background)
  {
    SDL_Log("Erreur de chargement background: %s", SDL_GetError());
    return 1;
  }

  //InitGame(render, player);
  player = InitPlayer(render, "./assets/SpaceInvaders.png");
  flechettes = InitFlechettes();
  canars = InitCanar();
  LevelOne(render, canars);

  bool running = true;
  while (running)
  {
    HomeScreen(render,background);
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    Game(render, player, flechettes, canars);
  }

  FreeAll(player, flechettes, canars);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
