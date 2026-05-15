#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "projectile.h"
#include "ennemie.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void HomeScreen(SDL_Renderer *, SDL_Texture *);
void Game(SDL_Renderer *, Player *, Flechettes *, Canars *, TTF_Font *);
void GameOver(SDL_Renderer *, const char *);

void InitGame(SDL_Renderer *, Player *);
void FreeAll(Player *, Flechettes *, Canars *);
void LevelTwo(Canars *);
void LevelOne(Canars *);

bool CheckCollision(SDL_Rect *, SDL_Rect *);
bool CheckCollisionByMe(SDL_Rect *, SDL_Rect *);
void CollideProjectile(Flechettes *, Canars *, Player *);
void CollideCanarPlayer(Player *, Canars *);

void UpdateScore(Player *);

void RenderPlayerHeart(Player *,SDL_Renderer *, TTF_Font *);
void Pause(SDL_Renderer *, const char *, TTF_Font *, Player *);
void RenderAll(SDL_Renderer *, Player *, Flechettes *, Canars *, TTF_Font *);
void RenderScore(Player *, TTF_Font *, SDL_Renderer *);
void MoveElements(Flechettes *, Canars *);
void CollideElements(Flechettes *, Canars *, Player *);
void RenderPlayer(Player *, SDL_Renderer *);
void RenderProjectiles(Flechettes *, SDL_Renderer *);
void RenderEnnemies(Canars *, SDL_Renderer *);

void SaveHighScore(int score);
int LoadHighScore();
void RenderHightScore(Player *, TTF_Font *, SDL_Renderer *);
void Input(const Uint8 *, Player *, Flechettes *);
#endif 
