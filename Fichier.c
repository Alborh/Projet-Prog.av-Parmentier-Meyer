/*
    fichier contenant :
    - le chargement de la carte
    -

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "fichier.h"
#include "constantes.h"
#include "cle_terrain.h"



int chargerNiveau(struct Tile niveau[][NB_BLOCKS_HAUTEUR], char level[50])
{
    char nom[50] = "niveau/";
    strcat(nom,level);
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
