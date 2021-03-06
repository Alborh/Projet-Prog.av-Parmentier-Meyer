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

#define NB_GOB_D 5
#define NB_GOB_I 7
#define TYPE_GOB 1
#define NB_ORC_D 2
#define NB_ORC_I 4
#define TYPE_ORC 2

//Statistiques de base du joueur
#define PV_BASE 30
#define AC_BASE 16
#define ATT_BASE 5
#define DMG_BASE 3
#define NB_D_BASE 1
#define NB_F_BASE 8

//Stats de base d'un Gobelin
#define PV_B_GOB 14
#define AC_B_GOB 13
#define ATT_B_GOB 3
#define DMG_B_GOB 1
#define NB_D_GOB 1
#define NB_F_GOB 6

//Stats de base d'un orc
#define PV_B_ORC 22
#define AC_B_ORC 15
#define ATT_B_ORC 4
#define DMG_B_ORC 2
#define NB_D_ORC 1
#define NB_F_ORC 8

//Stats de base du DRAGON
#define PV_B_DRA 50
#define AC_B_DRA 18
#define ATT_B_DRA 6
#define DMG_B_DRA 4
#define NB_D_DRA 2
#define NB_F_DRA 6

enum {HAUT, BAS, GAUCHE, DROITE};

struct tile
{
    char sprite;
    int marchable;
};

typedef struct tile Tile;

struct ennemi
{
  int col;
  int lig;
  int type;
  int vivant;
  SDL_Rect position;
  SDL_Surface *sprite_picture;
};

typedef struct ennemi ennemi_t;

typedef struct character
{
  int pv_max;
  int pv_act;
  int ac;
  int ac_boost;
  int att;
  int dmg;
  int nb_d;
  int nb_f;
} character_t;


void jeu(SDL_Surface* ecran);
void deplacerJoueur(SDL_Rect *pos, int direction,  Tile carte[][NB_BLOCKS_HAUTEUR]);
void rechercheSpawn(SDL_Rect *pos,  Tile carte[][NB_BLOCKS_HAUTEUR]);

void menu(SDL_Surface* ecran);
void deplacerCurseurMenu(SDL_Rect* pos, int direction);
int Interieur(SDL_Surface *ecran, SDL_Surface *Joueur[],SDL_Surface *JoueurActuel, SDL_Surface *Terrain[], ennemi_t gobelin[], SDL_Surface *sprite_gob, character_t player, int* continuer, ennemi_t orc[], SDL_Surface *sprite_orc);
void recherchePorte(SDL_Rect *pos,  Tile carte[][NB_BLOCKS_HAUTEUR]);
int chargerNiveau( Tile niveau[][NB_BLOCKS_HAUTEUR], char level[50]);
void choix_perso(SDL_Surface* ecran);
void deplacerCurseurChoix(SDL_Rect *pos,int direction);

int JetDe(int nb, int fa);
void create_gob(ennemi_t gob[], Tile carte[][NB_BLOCKS_HAUTEUR], SDL_Surface* sprite_gob, int nb);
void create_orc(ennemi_t orc[], Tile carte[][NB_BLOCKS_HAUTEUR], SDL_Surface* sprite_orc, int nb);
int test_collide(ennemi_t enn, SDL_Rect positionJoueur);
void kill_tab(ennemi_t enn[], int num);
void kill_tab_param(ennemi_t enn[], int nombre, SDL_Rect positionJoueur);
void combat_param(SDL_Surface *ecran, character_t *joueur, ennemi_t enn[], int nombre, SDL_Rect positionJoueur, int *continuer);
int combat(SDL_Surface *ecran, ennemi_t ennemi, character_t* joueur, int win);
character_t creationEnnemi(int TypeEnnemi);
int attaqueNormal(character_t joueur, character_t ennemi);
int attaqueSpe(character_t joueur, character_t ennemi,int* delay);
character_t defense(character_t joueur);
void affiche_pv(character_t perso, SDL_Rect pos_barre, SDL_Surface *PV, SDL_Surface *ecran);
int all_dead(ennemi_t enn[], int nb_max);

#endif
