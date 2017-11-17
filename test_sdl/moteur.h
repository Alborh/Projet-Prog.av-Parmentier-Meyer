#ifndef MOTEUR_H
#define MOTEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <string.h>
#define NB_PIXELS 32
#define HAUTEUR_FENETRE NB_PIXELS*NB_BLOCKS_HAUTEUR
#define LARGEUR_FENETRE NB_PIXELS*NB_BLOCKS_LARGEUR
#define NB_BLOCKS_HAUTEUR 24
#define NB_BLOCKS_LARGEUR 32

#define NB_SPRITES 100

#define MUR 'M'
#define _MUR 0

#define DALLE 'D'
#define _DALLE 1

#define HERBE 'G'
#define _HERBE 1

#define ARBRE 'T'
#define _ARBRE 0

#define COFFRE 'C'
#define _COFFRE 1

#define EAU 'W'
#define _EAU 0

#define PONT_V 'B'
#define _PONT_V 1

#define PONT_H 'A'
#define _PONT_H 1

#define BORD 'Z'
#define _BORD 0

#define ROUTE 'R'
#define _ROUTE 1

#define SPAWN 'S'
#define _SPAWN 1

#define PORTE 'P'
#define _PORTE 1

#define GOLEM 'E'
#define _GOLEM 1

#define VIDE 'V'
#define _VIDE 0

#define MONT 'N'
#define _MONT 0


enum {HAUT, BAS, GAUCHE, DROITE};

struct Tile
{
    char sprite;
    int marchable;
};



void jeu(SDL_Surface* ecran);
void deplacerJoueur(SDL_Rect *pos, int direction, struct Tile carte[][NB_BLOCKS_HAUTEUR]);
void rechercheSpawn(SDL_Rect *pos, struct Tile carte[][NB_BLOCKS_HAUTEUR]);

void menu(SDL_Surface* ecran);
void deplacerCurseurMenu(SDL_Rect* pos, int direction);
void Interieur(SDL_Surface *ecran, SDL_Surface *Joueur[],SDL_Surface *JoueurActuel, SDL_Surface *Terrain[]);
void recherchePorte(SDL_Rect *pos, struct Tile carte[][NB_BLOCKS_HAUTEUR]);
int chargerNiveau(struct Tile niveau[][NB_BLOCKS_HAUTEUR], char level[50]);
void choix_perso(SDL_Surface* ecran);
void deplacerCurseurChoix(SDL_Rect *pos,int direction);

#endif