#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "projectile.h"
#include "ennemie.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void HomeScreen(SDL_Renderer *, SDL_Texture *);
void Game(SDL_Renderer *, Player *, Flechettes *, Canars *);
void GameOver(SDL_Renderer *);
void RenderPlayer(Player *, SDL_Renderer *);
void RenderProjectiles(Flechettes *, SDL_Renderer *);
void RenderEnnemies(Canars *, SDL_Renderer *);
void InitGame(SDL_Renderer *, Player *);
void FreeAll(Player *, Flechettes *, Canars *);
void LevelOne(SDL_Renderer *, Canars *);
bool CheckCollision(SDL_Rect *, SDL_Rect *);
bool CheckCollisionByMe(SDL_Rect *, SDL_Rect *);
void Collide(Flechettes *, Canars *, Player *);
void CollideWithPlayer(Player *, Canars *);
void UpdateScore(Player *);
void RenderPlayerHeart(Player *,SDL_Renderer *);
#endif 
