#include "game.h"

bool started = true;
Uint32 delay = 120;
Uint32 move = 0;

void HomeScreen(SDL_Renderer *render, SDL_Texture *background)
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
  SDL_RenderCopy(render, player->texture, &player->rect,&player->destRect);
}
void MoveElements(Flechettes *flechettes, Canars *canars, Uint32 nowMove)
{
  if (nowMove - move >= delay){
    move = nowMove;
    MoveCanar(canars);
  } 
  MoveFlechettes(flechettes);

}

void CollideElements(Flechettes *flechettes, Canars *canars, Player *player)
{
  CollideCanarFlechette(flechettes,canars, player);
  CollideCanarPlayer(player, canars);
}

void RenderAll(SDL_Renderer *render, Player *player, Flechettes *flechettes, Canars *canars, TTF_Font *font)
{
  RenderPlayer(player, render);
  RenderPlayerHeart(player, render, font);
  RenderScore(player, font, render);
  RenderProjectiles(flechettes,render);
  RenderEnnemies(canars, render);
}

void ResetAll(Player *player, Canars *canars)
{
  ResetPlayer(player);
  ResetCanars(canars);
}

void GameOver(SDL_Renderer *render, const char *path)
{
  SDL_Texture *gameOver = IMG_LoadTexture(render, path);
  SDL_Rect rect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(render, gameOver, NULL, &rect);
}

void Pause(SDL_Renderer *render,const char *path)
{
  SDL_Texture *pauseScreen = IMG_LoadTexture(render,path);
  SDL_Rect rect = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(render, pauseScreen, NULL, &rect);
}

bool CheckCollision(SDL_Rect *firstRect, SDL_Rect *secondRect)
{
  return SDL_HasIntersection(firstRect, secondRect);
}

void RenderPlayerHeart(Player *player, SDL_Renderer *render, TTF_Font *font)
{
  char scor[64];
  sprintf(scor, "Live: ");
  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface *fontSurf = TTF_RenderText_Blended(font, scor, color);
  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(render,fontSurf);
  SDL_FreeSurface(fontSurf);

  SDL_Rect fontRect = {10, 10, 0, 0};
  SDL_QueryTexture(fontTexture, NULL, NULL, &fontRect.w, &fontRect.h);
  SDL_RenderCopy(render, fontTexture, NULL, &fontRect);

  for (int i = 0; i < player->health; i+=25)
  {
    player->heartDestRect = (SDL_Rect){i+90, 15, 22, 22};
    SDL_RenderCopy(render,player->heartTexture,&player->heartRect,&player->heartDestRect);
  }
}

void LevelTwo(Canars *canars)
{
  for (int i = 1; i <= 3; i++)
  {
    for (int j = 1; j <= 10-i; j++)
    {
      AddCanar(canars, j*60 + i*30,62*i);
    }
  }
}

void LevelOne(Canars *canars)
{
  for (int i = 0; i <= 12; i++)
  {
    AddCanar(canars, i*60,0);
    AddCanar(canars, i*60,40);
  }
}

void RenderScore(Player *player, TTF_Font *font, SDL_Renderer *render)
{
  char scor[64];
  sprintf(scor, "Score: %d", player->score);
  SDL_Color color = {255, 255, 255, 255};
  SDL_Surface *fontSurf = TTF_RenderText_Blended(font, scor, color);
  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(render,fontSurf);
  SDL_FreeSurface(fontSurf);

  SDL_Rect fontRect = {SCREEN_HEIGHT + 50, 10, 0, 0};
  SDL_QueryTexture(fontTexture, NULL, NULL, &fontRect.w, &fontRect.h);
  SDL_RenderCopy(render, fontTexture, NULL, &fontRect);
}

/*void RenderHightScore(Player *player, TTF_Font *font, SDL_Renderer *render)
{
  ;
}*/

void UpdateScore(Player *player){
  if (player->score >= player->highScore)
  {
    player->highScore = player->score;
  }
  player->score += rand() % 10;
}

void SaveHighScore(int score) {
    FILE *file = fopen("bestScore.txt", "w");
    if (file) {
        int encrypted = score ^ 0xDEADBEEF;
        fprintf(file, "%08X\n", encrypted);
        fclose(file);
    }
}

int LoadHighScore() {
    FILE *file = fopen("bestScore.txt", "r");
    int score = 0;
    if (file) {
        unsigned int encrypted;
        if (fscanf(file, "%X", &encrypted) == 1) {
            score = encrypted ^ 0xDEADBEEF;
        }
        fclose(file);
    }
    return score;
}

void CollideCanarFlechette(Flechettes *flechettes, Canars *canars, Player *player)
{
  Flechette *currentFlechette = flechettes->head;
  Flechette *prevFlechette = NULL;

  while (currentFlechette != NULL)
  {
    Canar *currentCanar = canars->head;
    Canar *prevCanar = NULL;

    int hit = 0;

    while (currentCanar != NULL)
    {
      if (CheckCollision(&currentFlechette->destRect, &currentCanar->destRect))
      {
        // Supprimer le canard
        if (prevCanar == NULL)
            canars->head = currentCanar->next;
        else
            prevCanar->next = currentCanar->next;

        free(currentCanar);
        canars->numberOfCanar--;

        // Supprimer la flechette
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

    if (hit)
    {
        // recommencer depuis le début des fléchettes
        currentFlechette = (prevFlechette == NULL) ? flechettes->head : prevFlechette->next;
    }
    else
    {
        prevFlechette = currentFlechette;
        currentFlechette = currentFlechette->next;
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

void PutOnPause(Player *player, const Uint8 *keystate, SDL_Renderer *render)
{
  if (keystate[SDL_SCANCODE_ESCAPE] && started && player->alive)
  {
    started = false;
  } else
  {
    started = true;
  }
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
      
      static int spacePressed = 0;

      if (keystate[SDL_SCANCODE_SPACE])
      {
        if (!spacePressed)
        {
          AddFlechette(flechettes, player->destRect.x + 4, player->destRect.y - 32);
        }
        spacePressed = 1;
      }
      else
      {
        spacePressed = 0;
      }
}
void Game(SDL_Renderer *render, Player *player, Flechettes *flechettes, Canars *canars, TTF_Font *font)
{
  printf("Score: %d | Health: %d | started %d | numberOfCanar %d\n",player->score,player->health, started, canars->numberOfCanar);

  SDL_Event event;
  Uint32 nowMove = SDL_GetTicks();
  SDL_PollEvent(&event);
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  PutOnPause(player, keystate, render);
  if (started)
  {
    MoveElements(flechettes, canars, nowMove);
    RenderAll(render, player, flechettes, canars, font);
    CollideElements(flechettes, canars, player);
    Input(keystate, player, flechettes);
  }else{
    Pause(render,"./assets/paused.png");
  }
}
