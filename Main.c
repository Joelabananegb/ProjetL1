#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
//#include "game.h" // Contient les déclarations liées au jeu (player, monster, etc.)

#define SCREEN_HEIGHT 514
#define SCREEN_WIDTH 514

int main()
{
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

  bool running = true;
  while (running)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    SDL_RenderPresent(render);
  }

  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
