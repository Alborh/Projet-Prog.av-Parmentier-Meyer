

#ifndef COMBAT_H
#define COMBAT_H

enum {HAUT,BAS,GAUCHE,DROITE};

typedef struct ennemi
{
    int Type;
}ennemi_t;

typedef struct personnage
{
    int pv_max;
    int pv_act;
    int ac_normal;
    int ac_boost;
    int point_attaque; // chance de toucher l'adversaire
    int bonus_dommage; // nombre de points de dégat bonus
    int nb_de;
    int nb_face;
}personnage_t;


personnage_t creationEnnemi(int TypeEnnemi);
void deplacerCurseur(SDL_Rect *pos, int direction);
void selection(SDL_Rect *pos,personnage_t *joueur, personnage_t *ennemi, int *delay);



#endif // COMBAT_H
