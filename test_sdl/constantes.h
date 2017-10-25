/*
    Le fichier des constantes afin de simplifier la gestion des constantes
    tel que :
        - nombre de pixels par sprites
        - nombre de sprites de haut par niveau
        - nombre de sprites de large par niveau



*/

#ifndef CONSTANTES_H
#define CONSTANTES_H

#define NB_PIXELS 32
#define HAUTEUR_FENETRE NB_PIXELS*NB_BLOCKS_HAUTEUR
#define LARGEUR_FENETRE NB_PIXELS*NB_BLOCKS_LARGEUR
#define NB_BLOCKS_HAUTEUR 24
#define NB_BLOCKS_LARGEUR 32



enum {HAUT, BAS, GAUCHE, DROITE};

#endif // CONSTANTES_H
