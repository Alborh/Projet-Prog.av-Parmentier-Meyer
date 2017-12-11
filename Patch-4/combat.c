
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "combat.h"


void combat(SDL_Surface *ecran, int TypeEnnemi, personnage_t *joueur)
{
    // compteur délai utilisation attaque spécial
    int delay = 0;

    // caractéristiques du personnage déjà créer dans le jeu

    // création de la structure de l'ennemi en fonction de la créature rencontrée
    personnage_t Ennemi;
    Ennemi = creationEnnemi(TypeEnnemi); // inserer le nom de la structure de l'ennemi rencontré

    SDL_Surface *FondCombat, *FondMenu, *Curseur;
    SDL_Event event;
    SDL_Rect positionCurseur, positionMenu, positionCombat, positionPerso, positionEnnemi;

    FondCombat = SDL_LoadBMP("image/combat/fond.bmp");
    FondMenu = SDL_LoadBMP("image/game-menu.bmp"); // charger l'image du menu du jeu
    Curseur = SDL_LoadBMP("image/Hand.bmp");      // charger l'image du curseur de selection

    positionCombat.x = 0;
    positionCombat.y = 0;
    positionMenu.x = 0;
    positionMenu.y = 0;


    int continuer = 1;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_DOWN:
                deplacercurseur(&positionCurseur, BAS);
                break;
            case SDLK_UP:
                deplacercurseur(&positionCurseur, HAUT);
                break;
            case SDLK_RIGHT:
                deplacerCurseur(&positionCurseur, DROITE);
                break;
            case SDLK_LEFT:
                deplacerCurseur(&positionCurseur, GAUCHE);
                break;
            case SDLK_RETURN:
                selection(&positionCurseur, &joueur, &Ennemi,&delay);
                break;
            default:
                break;
            }

        }
        SDL_BlitSurface(FondCombat,NULL,ecran,&positionCombat);
        SDL_BlitSurface(FondMenu,NULL,ecran,&positionMenu);
        SDL_BlitSurface(Curseur, NULL, ecran, &positionCurseur);
        SDL_Flip(ecran);
    }
}

personnage_t creationEnnemi(int TypeEnnemi)
{
    personnage_t Ennemi;

    switch(TypeEnnemi)
    {
    case 1:
        Ennemi = {30,30,15,15,5,3,1,6}; // changer les caractéristiques du gobelin
        break;
    default:
        break;
    }
    return Ennemi;
}

void deplacerCurseur(SDL_Rect *pos, int direction)
{
    switch(direction)
    {
    case HAUT:
        if(pos->y ==/*curseur en Haut */)
        {
            pos->y = /*position la plus basse du menu*/;
        }
        else
        {
            pos->y--; // déplacer le curseur vers le haut
        }
        break;
    case BAS:
        if(pos->y ==/*curseur en Bas */)
        {
            pos->y = /*position la plus haute du menu*/;
        }
        else
        {
            pos->y++; // déplacer le curseur vers le bas
        }
        break;
    case DROITE:
        break;
    case GAUCHE:
        break;
    }
}

void selection(SDL_Rect *pos,personnage_t *joueur, personnage_t *ennemi,int *delay)
{
    int chanceEnnemi;
    joueur->ac_boost = joueur->ac_normal;

    if(pos->x == /**/&& pos->x == /**/) // choix de l'attaque normal
    {
        attaqueNormal(&joueur,&ennemi);
    }
    else if(pos->x == /**/&& pos->x == /**/ && delay <= 0) // choix de l'attaque spécial
    {
        attaqueSpe(&joueur,&ennemi,&delay);
    }
    else if(pos->x == /**/&& pos->x == /**/) // choix de la défense
    {
        defense(&joueur);
    }

    chanceEnnemi = rand()%100;
    if (chanceEnnemi < 25)
    {
        defense(&Ennemi);
    }
    else
    {
        attaqueNormal(&ennemi, &joueur);
    }

    delay--;
}

void attaqueNormal(personnage_t *joueur, personnage_t *ennemi)
{
    int chance;
    chance = jetDe(1,20)+joueur->point_attaque;
    if(chance >= ennemi->ac_boost)
    {
        // affichage de la réussite de l'attaque
        int degats;
        degats = jetDe(joueur->nb_de,joueur->nb_face)+joueur->bonus_dommage;
        ennemi->pv_act -= degats;
        // animation de l'attaque
    }
    else
    {
        //affichage de l'échec
        //animation de l'échec
    }
}


void attaqueSpe(personnage_t *joueur, personnage_t *ennemi,int *delay)
{
    int chance;
    chance = jetDe(1,20)+joueur->point_attaque;
    delay = 4;
    if(chance >= ennemi->ac_boost)
    {
        // affichage de la réussite de l'attaque
        int degats;
        degats = 2*(jetDe(joueur->nb_de,joueur->nb_face)+joueur->bonus_dommage);
        ennemi->pv_act -= degats;
        // animation de l'attaque
    }
    else
    {
        //affichage de l'échec
        //animation de l'échec
    }
}

void defense(personnage_t *joueur)
{
    joueur->ac_boost += 5;
    joueur->pv_act += 10;
    if(joueur->pv_act > joueur->pv_max)
    {
        joueur->pv_act = joueur->pv_max;
    }
}
