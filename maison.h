/*


*/
#ifndef MAISON_H
#define MAISON_H

void Interieur(SDL_Surface *ecran, SDL_Surface *Joueur[],SDL_Surface *JoueurActuel, SDL_Surface *Terrain[]);
void recherchePorte(SDL_Rect *pos, struct Tile carte[][NB_BLOCKS_HAUTEUR]);

#endif // MAISON_H

