/*


*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "cle_terrain.h"
#include "editeur.h"

void editeur(SDL_Surface *ecran)
{
    SDL_Surface *EcranMenu = NULL;
    SDL_Surface *JoueurActuel = NULL;
    SDL_Surface *Terrain [NB_SPRITES]= {NULL};
    SDL_Rect position, positionJoueur, positionFond;
    SDL_Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int i = 0, j = 0;
    char objetActuel = 'G';

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

    if(!chargerNiveau(carte, "Terrain"))
        exit(EXIT_FAILURE);


    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_s:
                //sauvegarderNiveau(carte);
                break;
            case SDLK_1:
                break;
            case SDLK_2:
                break;
            case SDLK_3:
                break;
            case SDLK_4:
                break;
            case SDLK_5:
                break;
            case SDLK_6:
                break;

            }

        }
    }







}
