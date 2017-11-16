/*
    Fichier main qui appelera le menu de lancement du jeu.


*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "moteur.h"

int main(int argc, char *argv[])
{

    SDL_Surface* ecran = NULL, *start_menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer=1;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("RPG_Game", NULL); //insérer le nom du jeu

    start_menu = SDL_LoadBMP("image/Credits.bmp"); //insérer l'artwort du début du jeu ("appuyer sur start")
    positionMenu.x = 0;
    positionMenu.y = 0;


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
                continuer=0;
                break;
            case SDLK_RETURN:
                menu(ecran);
                break;
	    default:
	      break;
            }
            break;
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(start_menu,NULL,ecran, &positionMenu);
        SDL_Flip(ecran);
    }



    SDL_FreeSurface(ecran);
    SDL_Quit();


    return EXIT_SUCCESS;

}
