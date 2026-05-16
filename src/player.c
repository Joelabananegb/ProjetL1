#include "player.h"

int LoadHighScore() {
  FILE *file = fopen("bestScore.txt", "r");
  int score = 0;
  if (file)
  {
    unsigned int encrypted;
    if (fscanf(file, "%X", &encrypted) == 1)
    {
      score = encrypted ^ 0xDEADBEEF;
    }
    fclose(file);
  }
  return score;
}


Player *InitPlayer(SDL_Renderer *render, const char *imgpath, const char *imgpathHearth)
{
  Player *player = malloc(sizeof(Player));
  if (!player) return NULL;
  player->rect = (SDL_Rect){64, 0, 16, 16};
  player->destRect = (SDL_Rect){SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 180, 64, 64};
  player->texture = IMG_LoadTexture(render, imgpath);
  player->velocity = 8;
  player->attack = 10;
  player->health = 100;
  player->maxHealth = 100;
  player->score = 0;
  player->highScore = LoadHighScore();
  player->alive = true;
  player->heartTexture = IMG_LoadTexture(render, imgpathHearth);
  player->heartRect = (SDL_Rect){80,96,16,16};
  player->heartDestRect = (SDL_Rect){10,10,64,64};
  return player;
}
void  ResetPlayer(Player *player)
{
  player->destRect = (SDL_Rect){SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 180, 64, 64};
  player->health = 100;
  player->score = 0;
  player->alive = true;
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
  if (player->destRect.x <= SCREEN_WIDTH - 80)
  {
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
  if (player->destRect.y <= SCREEN_HEIGHT - 80)
  {
    player->destRect.y += player->velocity;
  }
}

void FreePlayer(Player **player)
{
  if (!player || !(*player)) return;

  if ((*player)->texture)
    SDL_DestroyTexture((*player)->texture);

  if ((*player)->heartTexture)
    SDL_DestroyTexture((*player)->heartTexture);

  free(*player);
  *player = NULL;
}

void PlayerDamage(Player *player)
{
  if (player->alive && player->health <= 0)
  {
    player->alive = false;
  }else
  {
    player->health -= 25;
  }
}
