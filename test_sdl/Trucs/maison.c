/*


*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "constantes.h"
#include "cle_terrain.h"
#include "Jeu.h"
#include "maison.h"


void Interieur(SDL_Surface *ecran, SDL_Surface *Joueur[],SDL_Surface *JoueurActuel, SDL_Surface *Terrain[])
{
    int continuer = 1;
    SDL_Rect position, positionJoueur, positionFond;
    SDL_Event event;

    int i=0, j=0;

    struct Tile carte[NB_BLOCKS_LARGEUR][NB_BLOCKS_HAUTEUR]={0};

    if(!chargerNiveau(carte, "Interieur"))
        exit(EXIT_FAILURE);


    recherchePorte(&positionJoueur, carte);

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
                if(carte[j][i].sprite == PORTE)
                {
                    continuer = 0;
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
        SDL_BlitSurface(JoueurActuel, NULL, ecran, &position);

        SDL_Flip(ecran);
    }


}

void recherchePorte(SDL_Rect *pos, struct Tile carte[][NB_BLOCKS_HAUTEUR])
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

