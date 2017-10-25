/*
    Fichier du menu.
    Il donne acccès à :
        - Commencer une nouvelle partie
        - Reprendre une ancienne partie
        - Accéder à l'éditeur de niveau
        - Accéder au option du jeu
        - Quitter le jeu

*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "menu.h"
#include "constantes.h"
#include "choixperso.h"
#include "Jeu.h"

void menu(SDL_Surface* ecran)
{
    SDL_Surface* menuJeu = NULL, *Curseur = NULL;
    SDL_Rect positionMenu, positionCurseur;
    SDL_Event event;

    int continuer =1;

    menuJeu = SDL_LoadBMP("image/game-menu.bmp"); // charger l'image du menu du jeu
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

