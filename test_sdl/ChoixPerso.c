/*
    fichier de choix du personnage (au cas où)



*/




#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "constantes.h"
#include "choixperso.h"


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
