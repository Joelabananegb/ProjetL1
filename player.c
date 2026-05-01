#include "player.h"

Player *InitPlayer(SDL_Renderer *render, const char *imgpath)
{
  Player *player = malloc(sizeof(Player));
  if (!player) return NULL;
  player->rect = (SDL_Rect){64, 0, 16, 16};
  player->destRect = (SDL_Rect){150,250,64,64};
  player->texture = IMG_LoadTexture(render,imgpath);
  player->velocity = 2;
  player->attack = 10;
  player->health = 100;
  player->maxHealth = 100;
  player->score = 0;

  return player;
}

void MoveLeft(Player *player)
{
  if (player->destRect.x >= 0)
  {
    player->destRect.x -= player->velocity;
  }
}

void MoveRight(Player *player)
{
  if (player->destRect.x <= SCREEN_HEIGHT)
  {
    printf("%d\n",player->destRect.x);
    player->destRect.x += player->velocity;
  }
}

void MoveUp(Player *player)
{
  if (player->destRect.y >= 0)
  {
    player->destRect.y -= player->velocity;
  }
}

void MoveDown(Player *player)
{
  if (player->destRect.y <= 290)
  {
    player->destRect.y += player->velocity;
  }
}

void FreePlayer(Player **player)
{
  free((*player));
  (*player) = NULL;
};
