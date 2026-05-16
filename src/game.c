#include "game.h"

int spacePressed = 0;

GameState *InitGameState()
{
  GameState *game = malloc(sizeof(GameState));
  game->running = true;
  game->started = false;
  game->paused = false;
  return game;
}

void HomeScreen(TTF_Font *font, SDL_Renderer *render)
{
  char gameName[MAX_CHAR];
  char How[MAX_CHAR];

  sprintf(gameName, "Earth invader");
  sprintf(How,"Press space to play");

  SDL_Color color = {255, 255, 255, 255};

  SDL_Surface *fontSurf = TTF_RenderText_Blended(font, gameName, color);
  SDL_Surface *fontSurfH = TTF_RenderText_Blended(font, How, color);

  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(render,fontSurf);
  SDL_Texture *fontTextureH = SDL_CreateTextureFromSurface(render,fontSurfH);

  SDL_FreeSurface(fontSurf);
  SDL_FreeSurface(fontSurfH);

  SDL_Rect fontRect = {0, 0, 0, 0};
  SDL_Rect fontRectH = {(SCREEN_WIDTH / 2) - 150, SCREEN_HEIGHT / 2 + 100, 0, 0};

  SDL_QueryTexture(fontTexture, NULL, NULL, &fontRect.w, &fontRect.h);
  SDL_QueryTexture(fontTextureH, NULL, NULL, &fontRectH.w, &fontRectH.h);

  fontRect.w *= 3;
  fontRect.h *= 3;
  fontRect.x = (SCREEN_WIDTH - fontRect.w ) / 2;
  fontRect.y = 180;

  SDL_RenderCopy(render, fontTexture, NULL, &fontRect);
  SDL_RenderCopy(render, fontTextureH, NULL, &fontRectH);

  SDL_DestroyTexture(fontTexture);
  SDL_DestroyTexture(fontTextureH);
}

void GameBackground(SDL_Renderer *render, SDL_Texture *background)
{
  SDL_Rect destRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
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
  SDL_RenderCopy(render, player->texture, &player->rect, &player->destRect);
}

void RenderWalls(Walls *walls, SDL_Renderer *render)
{
  Wall *current = walls->head;
  while(current != NULL)
  {
    SDL_RenderCopy(render, current->texture, &current->rect, &current->destRect);
    current = current->next;
  }
}

void MoveElements(Flechettes *flechettes, Canars *canars, Uint32 *nextMove, Uint32 moveDelay)
{
  if (SDL_GetTicks() >= *nextMove)
  {
    MoveCanar(canars);
    *nextMove = SDL_GetTicks() + moveDelay;
  }
  MoveFlechettes(flechettes);

}

void CreateWalls(Walls *walls)
{
  for (int i = 0; i <= 7; i++)
  {
    CreatWall(walls, 2*i+1);
  }
}

void CollideElements(Flechettes *flechettes, Canars *canars, Player *player)
{
  CollideProjectile(flechettes,canars, player);
  CollideCanarPlayer(player, canars);
}

void RenderAll(SDL_Renderer *render, Player *player, Flechettes *flechettes, Canars *canars, Walls *walls,TTF_Font *font)
{
  RenderPlayer(player, render);
  RenderPlayerHeart(player, render, font);
  RenderScore(player, font, render);
  RenderProjectiles(flechettes,render);
  RenderEnnemies(canars, render);
  RenderWalls(walls, render);
}

void ResetAll(Player *player, Canars *canars)
{
  ResetPlayer(player);
}

void GameOver(SDL_Renderer *render, const char *path)
{
  SDL_Texture *gameOver = IMG_LoadTexture(render, path);
  SDL_Rect rect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(render, gameOver, NULL, &rect);
  SDL_DestroyTexture(gameOver);
}

void Pause(SDL_Renderer *render , TTF_Font *font, Player *player)
{
  char scor[MAX_CHAR];
  char Hscor[MAX_CHAR];
  char pause[MAX_CHAR];
  char Epause[MAX_CHAR];

  sprintf(pause,"Pause");
  sprintf(scor, "Score : %d", player->score);
  sprintf(Hscor, "Best Score : %d", player->highScore);
  sprintf(Epause, "Echape pour reprendre");

  SDL_Color color = {255, 255, 255, 255};

  SDL_Surface *fontSurf = TTF_RenderText_Blended(font, scor, color);
  SDL_Surface *fontSurfH = TTF_RenderText_Blended(font, Hscor, color);
  SDL_Surface *fontSurfP = TTF_RenderText_Blended(font, pause, color);
  SDL_Surface *fontSurfPE = TTF_RenderText_Blended(font, Epause, color);

  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(render,fontSurf);
  SDL_Texture *fontTextureH = SDL_CreateTextureFromSurface(render,fontSurfH);
  SDL_Texture *fontTextureP = SDL_CreateTextureFromSurface(render,fontSurfP);
  SDL_Texture *fontTexturePE = SDL_CreateTextureFromSurface(render,fontSurfPE);

  SDL_FreeSurface(fontSurf);
  SDL_FreeSurface(fontSurfH);
  SDL_FreeSurface(fontSurfP);
  SDL_FreeSurface(fontSurfPE);

  SDL_Rect fontRect = {(SCREEN_WIDTH/2) - 80, SCREEN_HEIGHT/2, 0, 0};
  SDL_Rect fontRectH = {(SCREEN_WIDTH/2) - 80, SCREEN_HEIGHT/2 + 50, 0, 0};
  SDL_Rect fontRectP = {0, 0, 0, 0};
  SDL_Rect fontRectPE = {(SCREEN_WIDTH/2) - 150, SCREEN_HEIGHT/2 + 120, 0, 0};

  SDL_QueryTexture(fontTexture, NULL, NULL, &fontRect.w, &fontRect.h);
  SDL_QueryTexture(fontTextureH, NULL, NULL, &fontRectH.w, &fontRectH.h);
  SDL_QueryTexture(fontTextureP, NULL, NULL, &fontRectP.w, &fontRectP.h);
  SDL_QueryTexture(fontTexturePE, NULL, NULL, &fontRectPE.w, &fontRectPE.h);

  fontRectP.w *= 2;
  fontRectP.h *= 2;
  fontRectP.x = (SCREEN_WIDTH - fontRectP.w) / 2;
  fontRectP.y = 180;

  SDL_RenderCopy(render, fontTexture, NULL, &fontRect);
  SDL_RenderCopy(render, fontTextureH, NULL, &fontRectH);
  SDL_RenderCopy(render, fontTextureP, NULL, &fontRectP);
  SDL_RenderCopy(render, fontTexturePE, NULL, &fontRectPE);

  SDL_DestroyTexture(fontTexture);
  SDL_DestroyTexture(fontTextureH);
  SDL_DestroyTexture(fontTextureP);
  SDL_DestroyTexture(fontTexturePE);
}

bool CheckCollision(SDL_Rect *firstRect, SDL_Rect *secondRect)
{
  return SDL_HasIntersection(firstRect, secondRect);
}

void RenderPlayerHeart(Player *player, SDL_Renderer *render, TTF_Font *font)
{
  char scor[MAX_CHAR];
  sprintf(scor, "Live: ");
  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface *fontSurf = TTF_RenderText_Blended(font, scor, color);
  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(render,fontSurf);
  SDL_FreeSurface(fontSurf);

  SDL_Rect fontRect = {10, 10, 0, 0};
  SDL_QueryTexture(fontTexture, NULL, NULL, &fontRect.w, &fontRect.h);
  SDL_RenderCopy(render, fontTexture, NULL, &fontRect);

  for (int i = 0; i <= player->health; i+=25)
  {
    player->heartDestRect = (SDL_Rect){i+90, 15, 22, 22};
    SDL_RenderCopy(render,player->heartTexture,&player->heartRect,&player->heartDestRect);
  }
}

void LevelTwo(Canars *canars)
{
  canars->numberInit = 10;
  for (int i = 1; i <= 3; i++)
  {
    for (int j = 1; j <= canars->numberInit - i; j++)
    {
      AddCanar(canars, j*60 + i*30,62*i);
    }
  }
}

void LevelOne(Canars *canars)
{
  canars->numberInit = 8;
  for (int i = 1; i <= canars->numberInit; i++)
  {
    AddCanar(canars, i*60,40);
    AddCanar(canars, i*60,80);
  }
}

void RenderScore(Player *player, TTF_Font *font, SDL_Renderer *render)
{
  char scor[MAX_CHAR];
  sprintf(scor, "Score: %d", player->score);
  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface *fontSurf = TTF_RenderText_Blended(font, scor, color);
  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(render,fontSurf);
  SDL_FreeSurface(fontSurf);

  SDL_Rect fontRect = {SCREEN_HEIGHT + 50, 10, 0, 0};
  SDL_QueryTexture(fontTexture, NULL, NULL, &fontRect.w, &fontRect.h);
  SDL_RenderCopy(render, fontTexture, NULL, &fontRect);
  SDL_DestroyTexture(fontTexture);
}

void UpdateScore(Player *player)
{
  if (player->score >= player->highScore)
  {
    player->highScore = player->score;
  }
  player->score += rand() % 10;
}

void SaveHighScore(int score) {
  FILE *file = fopen("bestScore.txt", "w");
  if (file)
  {
    int encrypted = score ^ 0xDEADBEEF;
    fprintf(file, "%08X\n", encrypted);
    fclose(file);
  }
}


void CollideProjectile(Flechettes *flechettes, Canars *canars, Player *player)
{
  Flechette *currentFlechette = flechettes->head;
  Flechette *prevFlechette = NULL;

  while (currentFlechette != NULL)
  {
    int hit = 0;

    if (currentFlechette->type == PLAYERBULLET)
    {
      Canar *currentCanar = canars->head;
      Canar *prevCanar = NULL;

      while (currentCanar != NULL)
      {
        if (CheckCollision(&currentFlechette->destRect, &currentCanar->destRect))
        {
          // supprimer canar
          if (prevCanar == NULL)
          {
            canars->head = currentCanar->next;
          }
          else
          {
            prevCanar->next = currentCanar->next;
          }
          free(currentCanar);
          canars->numberOfCanar--;

          // supprimer bullet
          if (prevFlechette == NULL)
          {
            flechettes->head = currentFlechette->next;
          }
          else
          {
            prevFlechette->next = currentFlechette->next;
          }
          free(currentFlechette);
          flechettes->ammo--;

          UpdateScore(player);

          hit = 1;
          break;
        }

        prevCanar = currentCanar;
        currentCanar = currentCanar->next;
      }
    } else if (currentFlechette->type == ENEMYBULLET)
    {
      if (CheckCollision(&currentFlechette->destRect, &player->destRect))
      {
        PlayerDamage(player);

        // supprimer bullet
        if (prevFlechette == NULL)
        {
            flechettes->head = currentFlechette->next;
        }
        else
        {
          prevFlechette->next = currentFlechette->next;
        } 
        free(currentFlechette);
        flechettes->ammo--;

        hit = 1;
      }
    }

    if (!hit)
    {
      prevFlechette = currentFlechette;
      currentFlechette = currentFlechette->next;
    }
    else
    {
      currentFlechette = (prevFlechette == NULL) ? flechettes->head : prevFlechette->next;
    }
  }
}

void CollideCanarPlayer(Player *player, Canars *canars)
{
  Canar *currentCanar = canars->head;
  Canar *prevCanar = NULL;
  while(currentCanar != NULL)
  {
    if(CheckCollision(&player->destRect, &currentCanar->destRect)){
      if (prevCanar == NULL)
      {
        canars->head = currentCanar->next;
      }
      else
      {
        prevCanar->next = currentCanar->next;
      }
      Canar *tmp = currentCanar;
      currentCanar = currentCanar->next;
      PlayerDamage(player);
      free(tmp);
      canars->numberOfCanar--;
    }
    else
    {
      prevCanar = currentCanar;
      currentCanar = currentCanar->next;
    }
  }
}

void FreeAll(Player *player, Flechettes *flechettes, Canars *canars){
  FreePlayer(&player);
  FreeFlechettes(&flechettes);
  FreeCanar(&canars);
}

void Input(const Uint8 *keystate, Player *player, Flechettes *flechettes)
{ 
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

  if (keystate[SDL_SCANCODE_SPACE])
  {
    if (!spacePressed)
    {
      AddFlechette(flechettes, player->destRect.x + 4, player->destRect.y - 32, -8, PLAYERBULLET);
    }
    spacePressed = 1;
  }
  else
  {
      spacePressed = 0;
  }
}

void Game(SDL_Renderer *render, Player *player, Flechettes *flechettes, Canars *canars, Walls *walls, TTF_Font *font, GameState *gameState)
{
  printf("LOG -> |Score: %d | Health: %d | started: %d | numberOfCanar: %d | Space Pressed: %d | Paused: %d |\n",player->score,player->health, gameState->started, canars->numberOfCanar, spacePressed, gameState->paused);

  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      gameState->running = false;
    }

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        gameState->paused = !gameState->paused;
      }

      if (event.key.keysym.sym == SDLK_SPACE && gameState->started != true){
        gameState->started = !gameState->started;
      } 
    }
  }

  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  static Uint32 nextEnemyShot = 0;
  static Uint32 nextMove = 0;
  Uint32 baseDelay = 400;
  Uint32 minDelay = 80;

  float ratio = (float)canars->numberOfCanar / canars->numberInit;
  ratio = ratio * ratio;

  Uint32 moveDelay = minDelay + (baseDelay - minDelay ) * ratio;

  if (gameState->started && !gameState->paused)
  {
    if (SDL_GetTicks() >= nextEnemyShot)
    {
      Attack(canars, flechettes);
      nextEnemyShot = SDL_GetTicks() + 50 + rand() % 1500;
    }

    MoveElements(flechettes, canars, &nextMove, moveDelay);

    RenderAll(render, player, flechettes, canars, walls, font);
    CollideElements(flechettes, canars, player);
    Input(keystate, player, flechettes);
  } else if (!gameState->started)
  {
    HomeScreen(font, render);
  }

  if (gameState->started && gameState->paused){
    Pause(render, font, player);
  }
}
