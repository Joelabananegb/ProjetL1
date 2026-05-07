#include "game.h"

bool started = true;

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

void RenderPlayerHeart(Player *player, SDL_Renderer *render)
{
  for (int i = 0; i < player->health; i+=25)
  {
    player->heartDestRect = (SDL_Rect){i+10, 10, 16,16};
    SDL_RenderCopy(render,player->heartTexture,&player->hearthRect,&player->heartDestRect);
  }
}

void HomeScreen(SDL_Renderer *render, SDL_Texture *background)
{
  SDL_Rect destRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
  SDL_RenderCopy(render, background, NULL, &destRect);
}

void RenderEnnemies(Canars *canars, SDL_Renderer *render)
{ Canar *current = canars->head;

  while (current != NULL)
  {
    SDL_RenderCopy(render, current->texture, &current->rect, &current->destRect);
    current = current->next;
  }
}

void LevelTwo(SDL_Renderer *render, Canars *canars)
{
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j <= 12-i; j++)
    {
      AddCanar(canars, j*60 + i*30,62*i,render);
    }
  }
}
void LevelOne(SDL_Renderer *render, Canars *canars)
{
  for (int i = 0; i <= 12; i++)
  {
    AddCanar(canars, i*60,0, render);
    AddCanar(canars, i*60,40,render);
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

void UpdateScore(Player *player){
  if (player->score >= player->highScore)
  {
    player->highScore = player->score;
  }
  player->score += rand() % 10;
}

void Collide(Flechettes *flechettes, Canars *canars, Player *player)
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


void CollideWithPlayer(Player *player, Canars *canars)
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
    }
    else
    {
      prevCanar = currentCanar;
      currentCanar = currentCanar->next;
    }
  }
}

void RenderPlayer(Player *player, SDL_Renderer *render)
{
  SDL_RenderCopy(render, player->texture, &player->rect,&player->destRect);
}

void RenderAll(SDL_Renderer *render, Player *player, Flechettes *flechettes, Canars *canars)
{
  RenderPlayer(player, render);
  RenderPlayerHeart(player, render);
  RenderProjectiles(flechettes,render);
  MoveFlechettes(flechettes);
  RenderEnnemies(canars, render);
  MoveCanar(canars);
  Collide(flechettes,canars, player);
  CollideWithPlayer(player, canars);
}


void FreeAll(Player *player, Flechettes *flechettes, Canars *canars){
  FreePlayer(&player);
  FreeFlechettes(&flechettes);
  FreeCanar(&canars);
}

void Game(SDL_Renderer *render, Player *player, Flechettes *flechettes, Canars *canars)
{
  printf("Score: %d | Heatl: %d | started %d\n",player->score,player->health, started);


  SDL_Event event;
  SDL_PollEvent(&event);

  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  
  if (started)
  {
    RenderAll(render, player, flechettes, canars);
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
          AddFlechette(flechettes, player->destRect.x + 4, player->destRect.y - 32, render);
        }
        spacePressed = 1;
      }
      else
      {
        spacePressed = 0;
      }
  }else{
    Pause(render,"./assets/paused.png");
  }

  if (keystate[SDL_SCANCODE_ESCAPE] && started && player->alive)
  {
    started = false;
  } else if (keystate[SDL_SCANCODE_Q] && !started && player->alive)
  {
    started = true;
  }
  SDL_RenderPresent(render);
  SDL_Delay(16);
}

