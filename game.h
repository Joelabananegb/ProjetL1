#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"

#define SCREEN_WIDTH 514
#define SCREEN_HEIGHT 514

void HomeScreen(SDL_Renderer *, SDL_Texture *);
void Game(SDL_Renderer *, Player *);
void RenderPlayer(Player *, SDL_Renderer *);
void InitGame(SDL_Renderer *, Player *);
void FreeAll(Player *);
#endif 
