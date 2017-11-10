/*
    header contenant les prototypes du fichier Jeu.c

*/

#ifndef JEU_H
#define JEU_H
#include "constantes.h"
#include <stdio.h>
#include <stdlib.h>

struct Tile
{
    char sprite;
    int marchable;
};



void jeu(SDL_Surface* ecran);
void deplacerJoueur(SDL_Rect *pos, int direction, struct Tile carte[][NB_BLOCKS_HAUTEUR]);
void rechercheSpawn(SDL_Rect *pos, struct Tile carte[][NB_BLOCKS_HAUTEUR]);



#endif // JEU_H
