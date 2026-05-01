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
  player->max_health = 100;
  player->score = 0;

  return player;
}

void MoveLeft(Player *player)
{
  player->destRect.x -= player->velocity;
}

void MoveRight(Player *player)
{
  player->destRect.x += player->velocity;
}

void MoveUp(Player *player)
{
  player->destRect.y -= player->velocity;
}

void MoveDown(Player *player)
{
  player->destRect.y += player->velocity;
}


/*void CanonAction(Canon *canon, enum action_canon actC, ListeFlechette *Flechettes)
{
  canon->ypos_old = canon->ypos; 

  switch (actC)
  {
    case Gauche_canon:
      canon->ypos -= canon->pas;
      break;
    case Droite_canon:
      canon->ypos += canon->pas;
      break;  
    case Tir:
      // Lance une fléchette
      AjouterFlechette(Flechettes, canon->xpos - 3,canon->ypos + canon->largeur / 2);
      break;       
  }

  if ((canon->ypos < canon->pos_min) || (canon->ypos > canon->pos_max - canon->largeur)) // verifier que le canon ne sort pas du cadre de jeu
  {
   canon->ypos = canon->ypos_old;
  }
}

void CanonAfficher(Canon *canon, Affichage* grille)
{ 
  for (int x = canon->xpos; x < canon->xpos + canon->hauteur; x++)
  {
    for (int y = canon->ypos; y < canon->ypos + canon->largeur; y++)
    {
      if (x >= 0 && x < grille->hauteur && y>=0 && y < grille->largeur)
      {
        strcpy(grille->tab[x][y], "♖");//"\33[44m ");
      }
    }

    strcpy(grille->tab[canon->xpos-1][canon->ypos + canon->largeur / 2-1], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-1][canon->ypos + canon->largeur / 2], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-1][canon->ypos + canon->largeur / 2+1], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-2][canon->ypos + canon->largeur / 2-1], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-2][canon->ypos + canon->largeur / 2], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-2][canon->ypos + canon->largeur / 2+1], "♖");//"\33[44m ");
  }
}*/
