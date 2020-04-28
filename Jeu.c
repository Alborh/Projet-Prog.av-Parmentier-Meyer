/*
    fichier contenant le premier niveau de jeu:
    - chargement de la carte
    - deplacement du personnage
    -

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "Jeu.h"
#include "constantes.h"
#include "cle_terrain.h"
#include "maison.h"
#include "fichier.h"



void jeu(SDL_Surface* ecran)
{
    SDL_Surface *Joueur[4] = {NULL};
    SDL_Surface *JoueurActuel = NULL;
    SDL_Surface *Terrain [NB_SPRITES]= {NULL};
    SDL_Rect position, positionJoueur, positionFond;
    SDL_Event event;

    int continuer = 1, i = 0, j = 0;
    struct Tile carte[NB_BLOCKS_LARGEUR][NB_BLOCKS_HAUTEUR]={0}; //tableau de données de la carte du niveau




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
    Terrain[SPAWN]=SDL_LoadBMP("image/runes.bmp");
    Terrain[PORTE]=SDL_LoadBMP("image/Porte.dib.bmp");
    Terrain[GOLEM]=SDL_LoadBMP("image/golem.bmp");

    //chargement des sprites des différentes position du joueur
    Joueur[HAUT] = SDL_LoadBMP("image/Hero.bmp");
    Joueur[BAS] = SDL_LoadBMP("image/Hero.bmp");
    Joueur[GAUCHE] = SDL_LoadBMP("image/Hero.bmp");
    Joueur[DROITE] = SDL_LoadBMP("image/Hero.bmp");
    //mise en transparence du fond
    SDL_SetColorKey(Joueur[HAUT],SDL_SRCCOLORKEY,SDL_MapRGB(Joueur[HAUT]->format,120,195,128));
    SDL_SetColorKey(Joueur[BAS],SDL_SRCCOLORKEY,SDL_MapRGB(Joueur[BAS]->format,120,195,128));
    SDL_SetColorKey(Joueur[GAUCHE],SDL_SRCCOLORKEY,SDL_MapRGB(Joueur[GAUCHE]->format,120,195,128));
    SDL_SetColorKey(Joueur[DROITE],SDL_SRCCOLORKEY,SDL_MapRGB(Joueur[DROITE]->format,120,195,128));



    // preset du joueur dans la position initial
    JoueurActuel = Joueur[BAS];

    //configuration de la position initial des sprites de map
    positionFond.x = 0;
    positionFond.y = 0;



    if(!chargerNiveau(carte, "Terrain"))
        exit(EXIT_FAILURE);

    rechercheSpawn(&positionJoueur, carte);


    SDL_EnableKeyRepeat(100,100);
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
                continuer = 0;
                break;
            case SDLK_RETURN:
                i = positionJoueur.y % NB_PIXELS;
                j = positionJoueur.x % NB_PIXELS;
                if(carte[j][i].sprite== PORTE)
                {
                    Interieur(ecran, Joueur, JoueurActuel, Terrain);
                }
                break;
            }
            break;
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

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

        if(carte[positionJoueur.x][positionJoueur.y].sprite == 'G')
        {
            combat(ecran, &position);
        }



        SDL_BlitSurface(JoueurActuel, NULL, ecran, &position);

        SDL_Flip(ecran);
    }


    SDL_EnableKeyRepeat(0,0);

    for( i = 0; i < 4; i++)
        SDL_FreeSurface(Joueur[i]);

    for( i = 0; i< NB_SPRITES; i++)
        SDL_FreeSurface(Terrain[i]);

}

void deplacerJoueur(SDL_Rect *pos, int direction, struct Tile carte[][NB_BLOCKS_HAUTEUR])
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

void rechercheSpawn(SDL_Rect *pos, struct Tile carte[][NB_BLOCKS_HAUTEUR])
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
