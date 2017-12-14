#include "moteur.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>
#include <math.h>
//#include <SDL_ttf/SDL_ttf.h>

void choix_perso(SDL_Surface* ecran)
{
    SDL_Surface *menuChoix = NULL, *Curseur = NULL;
    SDL_Rect positionMenu, positionCurseur;
    SDL_Event event;

    int continuer = 1;

    menuChoix = SDL_LoadBMP("image/");  //charger l'image du menu de selection du personnage
    Curseur = SDL_LoadBMP("image/");    //charger l'image du curseur de selection


    positionMenu.x = 0;
    positionMenu.y = 0;
    positionCurseur.x = 0; //coordonées à modifier en fonction du menu
    positionCurseur.y = 0;


    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_RIGHT:
                //deplacerCurseurChoix(&positionCurseur,DROITE);
                break;
            case SDLK_LEFT:
                //deplacerCurseurChpix(&positionCurseur,GAUCHE);
                break;
            case SDLK_RETURN:
                break;
            }
            break;
        }

        SDL_BlitSurface(menuChoix, NULL, ecran, &positionMenu);
        SDL_BlitSurface(Curseur, NULL, ecran, &positionCurseur);
        SDL_Flip(ecran);
    }


    SDL_FreeSurface(menuChoix);
    SDL_FreeSurface(Curseur);
}


void deplacerCurseurChoix(SDL_Rect *pos,int direction)
{
    switch (direction)
    {
    case DROITE:
        break;
    case GAUCHE:
        break;
    }
}

int chargerNiveau(Tile niveau[][NB_BLOCKS_HAUTEUR], char level[50])
{
  char nom[50] = "niveau/";
    strcat(nom, level);
    strcat(nom,".txt");

    FILE *fichier = NULL;
    fichier = fopen(nom,"r");

    rewind(fichier);

    int i=0, j=0;


    for(i = 0; i < NB_BLOCKS_HAUTEUR; i++)
    {
        for(j = 0; j < NB_BLOCKS_LARGEUR; j++)
        {
            niveau[j][i].sprite = fgetc(fichier);
            switch(niveau[j][i].sprite)
            {
            case MUR:
                niveau[j][i].marchable = _MUR;
                break;
            case DALLE:
                niveau[j][i].marchable = _DALLE;
                break;
            case HERBE:
                niveau[j][i].marchable = _HERBE;
                break;
            case ARBRE:
                niveau[j][i].marchable = _ARBRE;
                break;
            case COFFRE:
                niveau[j][i].marchable = _COFFRE;
                break;
            case EAU:
                niveau[j][i].marchable = _EAU;
                break;
            case PONT_H:
                niveau[j][i].marchable = _PONT_H;
                break;
            case PONT_V:
                niveau[j][i].marchable = _PONT_V;
                break;
            case BORD:
                niveau[j][i].marchable = _BORD;
                break;
            case ROUTE:
                niveau[j][i].marchable = _ROUTE;
                break;
            case SPAWN:
                niveau[j][i].marchable = _SPAWN;
                break;
	    case PORTE:
	      niveau[j][i].marchable = _PORTE;
	      break;
	    case VIDE:
	      niveau[j][i].marchable = _VIDE;
	      break;
	    case MONT:
	      niveau[j][i].marchable = _MONT;
	      break;
	    case GOLEM:
	      niveau[j][i].marchable = _GOLEM;
	      break;
            }

        }
        fseek(fichier,2,SEEK_CUR);
    }
    fclose(fichier);
    return 1;
}

void jeu(SDL_Surface* ecran)
{
    SDL_Surface *Joueur[4] = {NULL};
    SDL_Surface *JoueurActuel = NULL;
    SDL_Surface *Terrain [NB_SPRITES]= {NULL};
    SDL_Rect position, positionJoueur, positionFond;
    SDL_Event event;
    SDL_Surface* tmp;
    ennemi_t gobelin[NB_GOB_D], orc[NB_ORC_D];
    SDL_Surface *sprite_gob, *sprite_orc;
    int continuer = 1, i = 0, j = 0;
    Tile carte[NB_BLOCKS_LARGEUR][NB_BLOCKS_HAUTEUR]={0}; //tableau de données de la carte du niveau
    character_t player;
    player.pv_max = PV_BASE;
    player.pv_act = player.pv_max;
    player.ac = AC_BASE;
    player.ac_boost = player.ac;
    player.att = ATT_BASE;
    player.dmg = DMG_BASE;
    player.nb_d = NB_D_BASE;
    player.nb_f = NB_F_BASE;
    /* TTF_Font *font = TTF_OpenFont("image/04B_30__.TTF",32);
       char affichage_pv[25] = "Affichage des pv";
       SDL_Color color = {255, 255, 255};
       SDL_Surface *textsurface = TTF_RenderUTF8_Solid(font, affichage_pv, color);
       sprintf(affichage_pv, "Points de vie : %d", player.pv);
       SDL_BlitSurface(textsurface, NULL, ecran, NULL);
       SDL_FreeSurface(textsurface);*/
    // chargement des sprites des différents terrains 
    Terrain[MUR]=SDL_LoadBMP("image/Mur.dib.bmp"); //sprite du mur
    Terrain[DALLE]=SDL_LoadBMP("image/Dalle.dib.bmp");
    Terrain[HERBE]=SDL_LoadBMP("image/grass.dib.bmp");
    Terrain[ARBRE]=SDL_LoadBMP("image/Arbre.dib.bmp");
    Terrain[COFFRE]=SDL_LoadBMP("image/Coffre.dib.bmp");
    Terrain[EAU]=SDL_LoadBMP("image/eau.dib.bmp");
    Terrain[PONT_H]=SDL_LoadBMP("image/Bridge_H.dib.bmp");
    Terrain[PONT_V]=SDL_LoadBMP("image/Bridge_V.dib.bmp");
    Terrain[BORD]=SDL_LoadBMP("image/Vide.dib.bmp");
    Terrain[ROUTE]=SDL_LoadBMP("image/road.bmp");
    Terrain[SPAWN]=SDL_LoadBMP("image/Spawn.bmp");
    Terrain[PORTE]=SDL_LoadBMP("image/Porte.bmp");
    Terrain[VIDE]=SDL_LoadBMP("image/Vide.dib.bmp");
    Terrain[MONT]=SDL_LoadBMP("image/Montagne.bmp");
    Terrain[GOLEM]=SDL_LoadBMP("image/golem.bmp");
    //chargement des sprites des différentes position du joueur
    tmp = SDL_LoadBMP("image/Hero_h.bmp");
    Joueur[HAUT] = SDL_DisplayFormat(tmp);
    tmp = SDL_LoadBMP("image/Hero.bmp");
    Joueur[BAS] = SDL_DisplayFormat(tmp);
    tmp = SDL_LoadBMP("image/Hero_g.bmp");
    Joueur[GAUCHE] = SDL_DisplayFormat(tmp);
    tmp = SDL_LoadBMP("image/Hero.bmp");
    Joueur[DROITE] = SDL_DisplayFormat(tmp);
    tmp = SDL_LoadBMP("image/Gobelin.bmp");
    sprite_gob = SDL_DisplayFormat(tmp);
    tmp = SDL_LoadBMP("image/Orc.bmp");
    sprite_orc = SDL_DisplayFormat(tmp);
    int colorkey;
    colorkey = SDL_MapRGB(ecran->format, 255, 0, 255);
    SDL_SetColorKey(Joueur[HAUT], SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(Joueur[BAS], SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(Joueur[GAUCHE], SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(Joueur[DROITE], SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
    JoueurActuel = Joueur[HAUT];
    SDL_SetColorKey(sprite_gob, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
    SDL_SetColorKey(sprite_orc, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);




    // preset du joueur dans la position initial
    JoueurActuel = Joueur[GAUCHE];

    //configuration de la position initial des sprites de map
    positionFond.x = 0;
    positionFond.y = 0;

    rechercheSpawn(&positionJoueur, carte);

    if(!chargerNiveau(carte, "Terrain"))
      exit(EXIT_FAILURE);

    rechercheSpawn(&positionJoueur, carte);
    create_gob(gobelin, carte, sprite_gob, NB_GOB_D);
    create_orc(orc, carte, sprite_orc, NB_ORC_D);
    int u;
    SDL_EnableKeyRepeat(100,100);
    while(continuer)
      {
	SDL_BlitSurface(JoueurActuel, NULL, ecran, &position);
	SDL_Flip(ecran);
        SDL_WaitEvent(&event);
        switch(event.type)
	  {
	  case SDL_QUIT:
            continuer = 0;
            break;
	  case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
	      {
	      case SDLK_ESCAPE:
		continuer = 0;
		break;
	      case SDLK_UP:
                JoueurActuel = Joueur[HAUT];
                deplacerJoueur(&positionJoueur, HAUT, carte);
                break;
	      case SDLK_DOWN:
                JoueurActuel = Joueur[BAS];
                deplacerJoueur(&positionJoueur,BAS,carte);
                break;
	      case SDLK_RIGHT:
                JoueurActuel = Joueur[DROITE];
                deplacerJoueur(&positionJoueur,DROITE,carte);
                break;
	      case SDLK_LEFT:
                JoueurActuel = Joueur[GAUCHE];
                deplacerJoueur(&positionJoueur,GAUCHE,carte);
                break;
	      case SDLK_RETURN:
		i = positionJoueur.y % NB_PIXELS;
		j = positionJoueur.x % NB_PIXELS;
		if(carte[j][i].sprite==PORTE && all_dead(gobelin,NB_GOB_D) && all_dead(orc, NB_ORC_D))
		  {
		   continuer = Interieur(ecran, Joueur, JoueurActuel, Terrain, gobelin, sprite_gob, player, &continuer, orc, sprite_orc);
		  }
		break;
		/* case SDLK_SPACE:
		   
		   kill_tab_param(gobelin, NB_GOB_D, positionJoueur);
		   break;*/
	      default:
		break;
	      }
	    
            break;
	  }
	
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
	combat_param(ecran, &player, gobelin, NB_GOB_D, positionJoueur, &continuer);
	combat_param(ecran, &player, orc, NB_ORC_D, positionJoueur, &continuer);
        for(i = 0; i < NB_BLOCKS_HAUTEUR; i++)
	  {
            for(j =0; j < NB_BLOCKS_LARGEUR; j++)
	      {
                positionFond.x = j*NB_PIXELS;
                positionFond.y = i*NB_PIXELS;
                SDL_BlitSurface(Terrain[carte[j][i].sprite],NULL, ecran, &positionFond);
	      }
	  }
        position.x = positionJoueur.x*NB_PIXELS;
        position.y = positionJoueur.y*NB_PIXELS;
        SDL_BlitSurface(JoueurActuel, NULL, ecran, &position);

	for(i=0; i<NB_GOB_D; i++)
	  {
	    if(gobelin[i].vivant == 1)
	      { 
		SDL_BlitSurface(gobelin[i].sprite_picture, NULL, ecran, &gobelin[i].position);
	      }
	  }
	for(i=0; i<NB_ORC_D; i++)
	  {
	    if(orc[i].vivant == 1)
	      { 
		SDL_BlitSurface(orc[i].sprite_picture, NULL, ecran, &orc[i].position);
	      }
	  }


        SDL_Flip(ecran);
      }


    SDL_EnableKeyRepeat(0,0);

    /*for( i = 0; i < 4; i++)
      SDL_FreeSurface(Joueur[i]);

      for( i = 0; i< NB_SPRITES; i++)
      SDL_FreeSurface(Terrain[i]);
      // TTF_CloseFont(font);
      SDL_FreeSurface(JoueurActuel);
      SDL_FreeSurface(sprite_gob);*/

}

void deplacerJoueur(SDL_Rect *pos, int direction,Tile carte[][NB_BLOCKS_HAUTEUR])
{
    switch (direction)
    {
    case HAUT:
        if(carte[pos->x][pos->y-1].marchable == 0)
        {
            break;
        }
        else
        {
            pos->y--;
            break;
        }
    case BAS:
        if(carte[pos->x][pos->y+1].marchable == 0)
        {
            break;
        }
        else
        {
            pos->y++;
            break;
        }
    case DROITE:
        if(carte[pos->x+1][pos->y].marchable == 0)
        {
            break;
        }
        else
        {
            pos->x++;
            break;
        }
    case GAUCHE:
        if(carte[pos->x-1][pos->y].marchable == 0)
        {
            break;
        }
        else
        {
            pos->x--;
            break;
        }
    }
}

void rechercheSpawn(SDL_Rect *pos,Tile carte[][NB_BLOCKS_HAUTEUR])
{
    int i,j;
    for(i = 0; i < NB_BLOCKS_HAUTEUR; i++)
        {
            for(j =0; j < NB_BLOCKS_LARGEUR; j++)
            {
                if(carte[j][i].sprite == 'S')
                {
                    pos->x = j;
                    pos->y = i;
                }
            }
        }
}

void menu(SDL_Surface* ecran)
{
    SDL_Surface* menuJeu = NULL, *Curseur = NULL;
    SDL_Rect positionMenu, positionCurseur;
    SDL_Event event;

    int continuer =1;

    menuJeu = SDL_LoadBMP("image/Menu.bmp"); // charger l'image du menu du jeu
    Curseur = SDL_LoadBMP("image/Hand.bmp");      // charger l'image du curseur de selection
    SDL_SetColorKey(Curseur, SDL_SRCCOLORKEY, SDL_MapRGB(Curseur->format,0,255,0));
    //mise en transparence du fond vert du curseur

    positionMenu.x = 0;
    positionMenu.y = 0;
    positionCurseur.x = 300; // coordonnées à modifier en fonction de la configuration du menu
    positionCurseur.y = 450;



    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
	    case SDLK_ESCAPE:
	      continuer = 0;
	      break;
            case SDLK_UP:
                deplacerCurseurMenu(&positionCurseur,HAUT);
                break;
            case SDLK_DOWN:
                deplacerCurseurMenu(&positionCurseur,BAS);
                break;
            case SDLK_RETURN:
                if(positionCurseur.y == 450)
                {
                    jeu(ecran);
                    break;
                }
                if(positionCurseur.y == 500)
                {
                    continuer = 0;
                    break;
                }
            }
            break;

        }
        SDL_BlitSurface(menuJeu, NULL, ecran, &positionMenu);
        SDL_BlitSurface(Curseur, NULL, ecran, &positionCurseur);
        SDL_Flip(ecran);

    }

    SDL_FreeSurface(menuJeu);
    SDL_FreeSurface(Curseur);

}

void deplacerCurseurMenu(SDL_Rect* pos, int direction)
{
    switch(direction) //coordonées à modifier en fonction de la configuration du menu
    {
    case HAUT:
        if(pos->y == 450) //le curseur est en haut du menu
        {
            pos->y = 500; //on descend le curseur en bas du menu
            break;
        }
        else
        {
            pos->y = 450;
            break;
        }
    case BAS:
        if(pos->y == 500) //le curseur est en bas du menu
        {
            pos->y = 450; //on remonte le curseur en haut du menu
            break;
        }
        else
        {
            pos->y = 500;
            break;
        }
    }
}

int Interieur(SDL_Surface *ecran, SDL_Surface *Joueur[],SDL_Surface *JoueurActuel, SDL_Surface *Terrain[], ennemi_t gobelin[], SDL_Surface *sprite_gob, character_t player, int* continuer, ennemi_t orc[], SDL_Surface *sprite_orc)
{
  SDL_Rect position, positionJoueur, positionFond;
  SDL_Event event;
  int nb_gob = NB_GOB_I;
  int i=0, j=0;
  player.pv_max = 35;
  player.ac = 18;
  player.att = 6;
  player.dmg = 4;
  player.nb_f = 10;
  Tile carte[NB_BLOCKS_LARGEUR][NB_BLOCKS_HAUTEUR]={0};

  if(!chargerNiveau(carte, "Interieur"))
    exit(EXIT_FAILURE);


  recherchePorte(&positionJoueur, carte);
  create_gob(gobelin, carte, sprite_gob, NB_GOB_I);
  create_gob(orc, carte, sprite_orc, NB_ORC_I);
  while(continuer)
    {
      if(all_dead(gobelin,NB_GOB_I) && all_dead(orc, NB_ORC_I) && continuer)
	{
	  player.pv_max = 40;
	  player.pv_act = 40;
	  player.ac = 20;
	  player.att = 8;
	  player.dmg = 5;
	  player.nb_d = 2;
	  player.nb_f = 2;
	  int win = -1;
	  ennemi_t dragon;
	  dragon.type = 3;
	  if(win == -1)
	    {
	      win = combat(ecran, dragon, &player, win);
	    }
	  if(win == 1)
	    {
	      printf("Felicitaion, vous avez gagne !!!\n");
	    }
	  else
	    {
	      printf("Vous avez perdu.\n");
	    }
	  return 0;

	    *continuer = 0;
	  }
        SDL_WaitEvent(&event);	
        switch(event.type)
        {
        case SDL_QUIT:
	  return 0;
            *continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                JoueurActuel = Joueur[HAUT];
                deplacerJoueur(&positionJoueur, HAUT, carte);
                break;
            case SDLK_DOWN:
                JoueurActuel = Joueur[BAS];
                deplacerJoueur(&positionJoueur,BAS,carte);
                break;
            case SDLK_RIGHT:
                JoueurActuel = Joueur[DROITE];
                deplacerJoueur(&positionJoueur,DROITE,carte);
                break;
            case SDLK_LEFT:
                JoueurActuel = Joueur[GAUCHE];
                deplacerJoueur(&positionJoueur,GAUCHE,carte);
                break;
            case SDLK_ESCAPE:
	      return 0;
                continuer = 0;
                break;
		/*case SDLK_RETURN:
                i = positionJoueur.y % NB_PIXELS;
                j = positionJoueur.x % NB_PIXELS;
                if(carte[j][i].sprite == PORTE)
                {
                    continuer = 0;
                }
                break;*/
	    /*case SDLK_SPACE:
	      kill_tab_param(gobelin, NB_GOB_I, positionJoueur);
	      break;*/
	    default:
	      break;
            }
            break;
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
	combat_param(ecran, &player, gobelin, NB_GOB_I, positionJoueur, continuer);
	combat_param(ecran, &player, orc, NB_ORC_I, positionJoueur, continuer);
	
        for(i = 0; i < NB_BLOCKS_HAUTEUR; i++)
        {
            for(j =0; j < NB_BLOCKS_LARGEUR; j++)
            {
                positionFond.x = j*NB_PIXELS;
                positionFond.y = i*NB_PIXELS;
                SDL_BlitSurface(Terrain[carte[j][i].sprite],NULL, ecran, &positionFond);
            }
        }
        position.x = positionJoueur.x*NB_PIXELS;
        position.y = positionJoueur.y*NB_PIXELS;
	int i;
        for(i=0; i<NB_GOB_I; i++)
	  {
	    if(gobelin[i].vivant == 1)
	      { 
		SDL_BlitSurface(gobelin[i].sprite_picture, NULL, ecran, &gobelin[i].position);
	      }
	  }
	for(i=0; i<NB_ORC_I; i++)
	  {
	    if(orc[i].vivant == 1)
	      { 
		SDL_BlitSurface(orc[i].sprite_picture, NULL, ecran, &orc[i].position);
	      }
	  }
	SDL_BlitSurface(JoueurActuel, NULL, ecran, &position);

        SDL_Flip(ecran);
    }
    
}

void recherchePorte(SDL_Rect *pos, Tile carte[][NB_BLOCKS_HAUTEUR])
{
    int i,j;
    for(i = 0; i < NB_BLOCKS_HAUTEUR; i++)
        {
            for(j =0; j < NB_BLOCKS_LARGEUR; j++)
            {
                if(carte[j][i].sprite == 'P')
                {
                    pos->x = j;
                    pos->y = i;
                }
            }
        }
}

int jetDe(int nb, int fa)
{
  int res = 0;
  int i;
  for(i=0; i<nb; i++)
    {
      res = res + rand()%fa +1;
    }
  return res;
}

void create_gob(ennemi_t gob[], Tile carte[][NB_BLOCKS_HAUTEUR], SDL_Surface* sprite_gob, int nb)
{
  int i;
  int col, lig;
  for (i=0; i<nb; i++)
    {
      col = rand()%NB_BLOCKS_LARGEUR;
      lig = rand()%NB_BLOCKS_HAUTEUR;
      while(carte[col][lig].marchable == 0 || carte[col][lig].sprite==PORTE || carte[col][lig].sprite==COFFRE || carte[col][lig].sprite==SPAWN)
	{
	  col = rand()%NB_BLOCKS_LARGEUR;
	  lig = rand()%NB_BLOCKS_HAUTEUR;
	}
      gob[i].col = col;
      gob[i].lig = lig;
      gob[i].vivant = 1;
      gob[i].position.x = col*NB_PIXELS;
      gob[i].position.y = lig*NB_PIXELS;
      gob[i].sprite_picture = sprite_gob;
      gob[i].type = TYPE_GOB;
    }
}

void create_orc(ennemi_t orc[], Tile carte[][NB_BLOCKS_HAUTEUR], SDL_Surface* sprite_orc, int nb)
{
  int i;
  int col, lig;
  for (i=0; i<nb; i++)
    {
      col = rand()%NB_BLOCKS_LARGEUR;
      lig = rand()%NB_BLOCKS_HAUTEUR;
      while(carte[col][lig].marchable == 0 || carte[col][lig].sprite==PORTE || carte[col][lig].sprite==COFFRE || carte[col][lig].sprite==SPAWN )
	{
	  col = rand()%NB_BLOCKS_LARGEUR;
	  lig = rand()%NB_BLOCKS_HAUTEUR;
	}
      orc[i].col = col;
      orc[i].lig = lig;
      orc[i].vivant = 1;
      orc[i].position.x = col*NB_PIXELS;
      orc[i].position.y = lig*NB_PIXELS;
      orc[i].sprite_picture = sprite_orc;
      orc[i].type = TYPE_ORC;
    }
}

int test_collide(ennemi_t enn, SDL_Rect positionJoueur)
{
  if(enn.position.x/32==positionJoueur.x && enn.position.y/32==positionJoueur.y)
    {
      // printf("pouet");
      return 1;
    }
  else
    {  
      //printf("prout");
      return 0;
    }
}

void kill_tab(ennemi_t enn[], int num)
{
  enn[num].vivant = 0;
}

void kill_tab_param(ennemi_t enn[], int nombre, SDL_Rect positionJoueur)
{
  int i;
  for(i=0; i<nombre; i++)
    {
      //printf("ennemi nu %d : %d %d\n",i, enn[i].position.x/32, enn[i].position.y/32);
      if(test_collide(enn[i],positionJoueur)==1)
	{
	  kill_tab(enn, i);
	}
    }
}

void combat_param(SDL_Surface *ecran, character_t* joueur, ennemi_t enn[], int nombre, SDL_Rect positionJoueur, int* continuer)
{
int i;
 int win;
  for(i=0; i<nombre; i++)
    {
      if(test_collide(enn[i],positionJoueur)==1 && enn[i].vivant == 1 && joueur->pv_act >0)
	{
	  win = combat(ecran, enn[i], joueur, win);
	  if(win)
	    {
	      kill_tab(enn, i);
	    }
	  else
	    {
	      *continuer = 0;
	    }
	}
    }
}

int combat(SDL_Surface *ecran, ennemi_t ennemi, character_t* joueur, int win)
{
  printf("combat\n");
  // compteur délai utilisation attaque spécial
  int delay = 0;
  // caractéristiques du personnage déjà créer dans le jeu

  // création de la structure de l'ennemi en fonction de la créature rencontrée
  character_t Ennemi;
  Ennemi = creationEnnemi(ennemi.type); // inserer le nom de la structure de l'ennemi rencontré

  SDL_Surface *FondCombat, *bouton_att, *bouton_deff, *bouton_spe, *barre_vie, *PV, *sprite_joueur, *sprite_ennemi ;
  SDL_Event event;
  SDL_Rect positionCombat, pos_b_att, pos_b_deff, pos_b_spe, positionPerso, positionEnnemi, pos_barre_vie_j, pos_barre_vie_e;

  SDL_Surface* tmp;
  FondCombat = SDL_LoadBMP("image/Fond_combat.bmp");
  bouton_att = SDL_LoadBMP("image/Bouton_attaque.bmp");
  bouton_deff = SDL_LoadBMP("image/Bouton_deffendre.bmp");
  bouton_spe = SDL_LoadBMP("image/Bouton_special.bmp");
  barre_vie = SDL_LoadBMP("image/Barre_vie.bmp");
  PV = SDL_LoadBMP("image/PV.bmp");
  if(ennemi.type == 1)
    {
      tmp = SDL_LoadBMP("image/Gobelin_battle.bmp");
      sprite_ennemi = SDL_DisplayFormat(tmp);
    }
  if(ennemi.type == 2)
    {
      tmp = SDL_LoadBMP("image/Orc_battle.bmp");
      sprite_ennemi = SDL_DisplayFormat(tmp);
    }
  if(ennemi.type == 3)
    {
      tmp = SDL_LoadBMP("image/Dragon_battle.bmp");
      sprite_ennemi = SDL_DisplayFormat(tmp);
    }
  tmp = SDL_LoadBMP("image/Hero_battle.bmp");
  sprite_joueur = SDL_DisplayFormat(tmp);
  int colorkey;
  colorkey = SDL_MapRGB(ecran->format, 255, 0, 255);
  SDL_SetColorKey(sprite_joueur, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
  SDL_SetColorKey(sprite_ennemi, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);

  positionCombat.x = 0;
  positionCombat.y = 0;
  pos_barre_vie_j.x = 10;
  pos_barre_vie_j.y = 10;
  pos_barre_vie_e.x = LARGEUR_FENETRE - 10 -64;
  pos_barre_vie_e.y = 10;
  positionPerso.x = 200;
  positionPerso.y = 200;
  if(ennemi.type == 3)
    {
      positionEnnemi.x = LARGEUR_FENETRE - 200;
      positionEnnemi.y = 200-88;
    }
  else
    {
      positionEnnemi.x = LARGEUR_FENETRE - 200;
      positionEnnemi.y = 200;
    }
  pos_b_spe.x = 10;
  pos_b_spe.y = HAUTEUR_FENETRE - 52;
  pos_b_deff.x = 10;
  pos_b_deff.y = HAUTEUR_FENETRE - 94;
  pos_b_att.x = 10;
  pos_b_att.y = HAUTEUR_FENETRE - 94 -42;
  int continuer = 1;
  int chanceEnnemi;
  int turn = 1;
  int i;
  while (continuer)
    {
      joueur->ac_boost = joueur->ac;
      Ennemi.ac_boost = Ennemi.ac;
      if(turn)
	{
	  SDL_WaitEvent(&event);
	  switch (event.type)
	    {
	    case SDL_KEYDOWN:
	      switch (event.key.keysym.sym)
		{
		case SDLK_a:
		  printf("a\n");
		  Ennemi.pv_act = attaqueNormal(*joueur,Ennemi);
		  positionPerso.x = positionEnnemi.x - 72;
		  break;
		case SDLK_d:
		  printf("d\n");
		  *joueur = defense(*joueur);
		  break;
		case SDLK_s:
		  printf("s\n");
		  Ennemi.pv_act = attaqueSpe(*joueur,Ennemi,&delay);
		  positionPerso.x = positionEnnemi.x - 72;
		  break;
		case SDLK_k:
		  Ennemi.pv_act = 0;
		  break;
		default:
		  break;
		}
	      delay --;
	      turn = 0;
	    }
	}
      else
	{
	  printf("debut tour ennemi\n");
	  chanceEnnemi = rand()%100;
	  if (chanceEnnemi < 25)
	    {
	      Ennemi = defense(Ennemi);
	      positionEnnemi.x = positionPerso.x + 72;
	    }
	  else
	    {
	      joueur->pv_act = attaqueNormal(Ennemi, *joueur);
	    }
	  printf("tour ennemi fini\n");
	  turn = 1;
        }
      SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

      SDL_BlitSurface(FondCombat,NULL,ecran,&positionCombat);
      SDL_BlitSurface(bouton_att,NULL,ecran,&pos_b_att);
      SDL_BlitSurface(bouton_deff, NULL, ecran, &pos_b_deff);
      if(delay<1)
	{
	  SDL_BlitSurface(bouton_spe, NULL, ecran, &pos_b_spe);
	}
      SDL_BlitSurface(barre_vie, NULL, ecran, &pos_barre_vie_j);
      SDL_BlitSurface(barre_vie, NULL, ecran, &pos_barre_vie_e);
      SDL_BlitSurface(sprite_joueur, NULL, ecran, &positionPerso);
      SDL_BlitSurface(sprite_ennemi, NULL, ecran, &positionEnnemi);
      affiche_pv(*joueur,pos_barre_vie_j, PV, ecran);
      affiche_pv(Ennemi,pos_barre_vie_e, PV, ecran);
      SDL_Flip(ecran);
      SDL_Delay(250);
      positionPerso.x = 200;
      positionEnnemi.x = LARGEUR_FENETRE - 200;
      if (Ennemi.pv_act < 1)
	{
	  win = 1;
	  printf("win = %d\n", win);
	  continuer = 0;
	  return win;
	}
      if (joueur->pv_act < 1)
	{
	  win = 0;
	  printf("win = %d\n", win);
	  continuer = 0;
	  return win;
	}
    }
}

character_t creationEnnemi(int TypeEnnemi)
{
    character_t Ennemi;

    switch(TypeEnnemi)
    {
    case 1:
      // Ennemi = {PV_B_GOB,PV_B_GOB,AC_B_GOB,AC_B_GOB,ATT_B_GOB,DMG_B_GOB,NB_D_GOB,NB_F_GOB}; // changer les caractéristiques du gobelin
      Ennemi.pv_max = PV_B_GOB;
      Ennemi.pv_act = PV_B_GOB;
      Ennemi.ac = AC_B_GOB;
      Ennemi.ac_boost = AC_B_GOB;
      Ennemi.att = ATT_B_GOB;
      Ennemi.dmg = DMG_B_GOB;
      Ennemi.nb_d = NB_D_GOB;
      Ennemi.nb_f = NB_F_GOB;
        break;
    case 2:
      Ennemi.pv_max = PV_B_ORC;
      Ennemi.pv_act = PV_B_ORC;
      Ennemi.ac = AC_B_ORC;
      Ennemi.ac_boost = AC_B_ORC;
      Ennemi.att = ATT_B_ORC;
      Ennemi.dmg = DMG_B_ORC;
      Ennemi.nb_d = NB_D_ORC;
      Ennemi.nb_f = NB_F_ORC;
      break;
    case 3:
      Ennemi.pv_max = PV_B_DRA;
      Ennemi.pv_act = PV_B_DRA;
      Ennemi.ac = AC_B_DRA;
      Ennemi.ac_boost = AC_B_DRA;
      Ennemi.att = ATT_B_DRA;
      Ennemi.dmg = DMG_B_DRA;
      Ennemi.nb_d = NB_D_DRA;
      Ennemi.nb_f = NB_F_DRA;
      break;
    default:
        break;
    }
    return Ennemi;
}

int attaqueNormal(character_t joueur, character_t ennemi)
{
  printf("attaque\n");
  int chance;
  chance = jetDe(1,20)+joueur.att;
  if(chance >= ennemi.ac_boost)
    {
      // affichage de la réussite de l'attaque
      int degats;
      degats = jetDe(joueur.nb_d,joueur.nb_f)+joueur.dmg;
      ennemi.pv_act -= degats;
      printf("reussi\n");
      // animation de l'attaque
    }
  else
    {
      printf("echec\n");
      //affichage de l'échec
      //animation de l'échec
    }
  return ennemi.pv_act;
}

int attaqueSpe(character_t joueur, character_t ennemi,int* delay)
{
  printf("attaque spe\n");
    int chance;
    chance = jetDe(1,20)+joueur.att;
    *delay = 4;
    if(chance >= ennemi.ac_boost)
    {
        // affichage de la réussite de l'attaque
        int degats;
        degats = 2*(jetDe(joueur.nb_d,joueur.nb_f)+joueur.dmg);
        ennemi.pv_act -= degats;
	printf("reussi\n");
        // animation de l'attaque
    }
    else
    {
      printf("echec\n");
        //affichage de l'échec
        //animation de l'échec
    }
    return ennemi.pv_act;
}

character_t defense(character_t joueur)
{
  printf("defense\n");
    joueur.ac_boost += 5;
    joueur.pv_act += 10;
    if(joueur.pv_act > joueur.pv_max)
    {
        joueur.pv_act = joueur.pv_max;
    }
    return joueur;
}

void affiche_pv(character_t perso, SDL_Rect pos_barre, SDL_Surface *PV, SDL_Surface *ecran)
{
  float nb_pv, pv_act = perso.pv_act, pv_max = perso.pv_max;
  nb_pv = pv_act/pv_max;
  nb_pv = nb_pv*64; 
  int i;
  SDL_Rect pos;
  pos.y = pos_barre.y+2;
  for(i = 0; i<nb_pv; i++)
    {
      pos.x = pos_barre.x+2+i;
      SDL_BlitSurface(PV, NULL, ecran, &pos);
    }
}

int all_dead(ennemi_t enn[], int nb_max)
{
  int i;
  for(i=0;i<nb_max;i++)
    {
      if (enn[i].vivant)
	{
	  return 0;
	}
    }
  return 1;
}
