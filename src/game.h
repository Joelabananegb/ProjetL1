#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "projectile.h"
#include "ennemie.h"
#include "wall.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_CHAR 64

typedef struct GameState {
  bool running;
  bool started;
  bool paused;
} GameState;

GameState *InitGameState();
void GameBackground(SDL_Renderer *, SDL_Texture *);
void Game(SDL_Renderer *, Player *, Flechettes *, Canars *, Walls *,TTF_Font *, GameState *);
void GameOver(SDL_Renderer *, const char *);

void InitGame(SDL_Renderer *, Player *);
void HomeScreen(TTF_Font *, SDL_Renderer *);
void FreeAll(Player *, Flechettes *, Canars *);
void LevelTwo(Canars *);
void LevelOne(Canars *);

bool CheckCollision(SDL_Rect *, SDL_Rect *);
bool CheckCollisionByMe(SDL_Rect *, SDL_Rect *);
void CollideProjectile(Flechettes *, Canars *, Player *);
void CollideCanarPlayer(Player *, Canars *);

void UpdateScore(Player *);

void RenderPlayerHeart(Player *,SDL_Renderer *, TTF_Font *);
void Pause(SDL_Renderer *, TTF_Font *, Player *);
void RenderAll(SDL_Renderer *, Player *, Flechettes *, Canars *, Walls *, TTF_Font *);
void RenderScore(Player *, TTF_Font *, SDL_Renderer *);
void MoveElements(Flechettes *, Canars *, Uint32 *, Uint32);
void CollideElements(Flechettes *, Canars *, Player *);
void CreateWalls(Walls *);
void RenderPlayer(Player *, SDL_Renderer *);
void RenderProjectiles(Flechettes *, SDL_Renderer *);
void RenderEnnemies(Canars *, SDL_Renderer *);
void RenderWalls(Walls *, SDL_Renderer *);

void SaveHighScore(int);
void Input(const Uint8 *, Player *, Flechettes *);
#endif 
