#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define MAP_SIZE 32
#define SPRITE_TERRAIN_SIZE 32

int main()
{
  SDL_Surface *screen, *temp, *vide;
  int gameover;
  //lecture du fichier terrain
  int i, j =0;
  char **tableTerrain = (char**)malloc(MAP_SIZE*sizeof(char*));
  for(i = 0; i<MAP_SIZE; i++)
    {
      tableTerrain[i] = (char*)malloc(MAP_SIZE*sizeof(char));
    }  
  FILE *file = NULL; 
  file = fopen("Terrain.txt","r");
  char c='a';
  i = 0;
  while((c != EOF) && (j<32))
    {
      c = fgetc(file);      
      if( c != '\n')
	{
	  tableTerrain[i][j] = c;
	  i++;
	}
      if (i > 31)
	{
	  i = 0;
	  j++;
	}      
    }
  fclose(file);
  i = 0;
  j = 0;
  while(j<32)
    {
      while(i<32)
	{
	  printf("%c ",tableTerrain[i][j]);
	  i++;
	}
      printf("\n");
      i = 0;
      j++;
    }
  //affichage de la fenetre
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Projet","Projet");
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  //chargement des sprites
  temp = SDL_LoadBMP("Vide.bmp");
  vide = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *grass;
  temp = SDL_LoadBMP("grass.bmp");
  grass = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *arbre;
  temp = SDL_LoadBMP("Arbre.bmp");
  arbre = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *road;
  temp = SDL_LoadBMP("road.dib.bmp");
  road = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *dalle;
  temp = SDL_LoadBMP("Dalle.bmp");
  dalle = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *coffre;
  temp = SDL_LoadBMP("Coffre.bmp");
  coffre = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *eau;
  temp = SDL_LoadBMP("Eau.bmp");
  eau = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *bridge_v;
  temp = SDL_LoadBMP("Bridge_V.bmp");
  bridge_v = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *bridge_h;
  temp = SDL_LoadBMP("Bridge_H.bmp");
  bridge_h = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *wall;
  temp = SDL_LoadBMP("Mur.bmp");
  wall = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *door;
  temp = SDL_LoadBMP("Porte.bmp");
  door = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  SDL_Surface *mont;
  temp = SDL_LoadBMP("Montagne.bmp");
  mont = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  gameover = 0;

  while(!gameover)
    {
      SDL_Event event;
      //Uint8 *keystate;
      //événement pour quitter la fenetre
      if (SDL_PollEvent(&event)) 
	{          
	  switch (event.type) 
	    {
	    case SDL_QUIT:
	      gameover = 1;
	      break;               
	    case SDL_KEYDOWN:
	      switch (event.key.keysym.sym) {
	      case SDLK_ESCAPE:
	      case SDLK_q:
		gameover = 1;
		break;
	      default:
		break;
	      }
	      break;
            }
        }
      for(int x = 0; x<MAP_SIZE; x++)
	{
	  for(int y = 0; y<MAP_SIZE; y++)
	    {
	      SDL_Rect position;
	      position.x = x * SPRITE_TERRAIN_SIZE;
	      position.y = y * SPRITE_TERRAIN_SIZE;
	      SDL_BlitSurface(vide, NULL, screen, &position);
	      if(tableTerrain[x][y]=='g')
		{
		  SDL_BlitSurface(grass, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='t')
		{
		  SDL_BlitSurface(arbre, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='r')
		{
		  SDL_BlitSurface(road, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='s')
		{
		  SDL_BlitSurface(dalle, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='C')
		{
		  SDL_BlitSurface(coffre, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='w')
		{
		  SDL_BlitSurface(eau, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='B')
		{
		  SDL_BlitSurface(bridge_v, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='b')
		{
		  SDL_BlitSurface(bridge_h, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='M')
		{
		  SDL_BlitSurface(wall, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='p')
		{
		  SDL_BlitSurface(door, NULL, screen, &position);
		}
	      if(tableTerrain[x][y]=='m')
		{
		  SDL_BlitSurface(mont, NULL, screen, &position);
		}
	    }
	}
      SDL_UpdateRect(screen,0,0,0,0);
    }
  
  return 0;
}
