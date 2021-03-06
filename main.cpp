#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>

void Lecture_tableau (char tableau[][33], FILE *fichier );
void pause();


int main(int argc, char *argv[])
{

    char PeuImporte[24][33];

    FILE *fichier = NULL, *fichier_bis =NULL;
    fichier = fopen("C:/Users/MEYER/Desktop/L2-informatique/Projet RPG/terrain.txt","r");
    fichier_bis = fopen("banane","w");

    Lecture_tableau(PeuImporte, fichier);



    SDL_Surface *Cle_Terrain[26]={NULL};
    Cle_Terrain[22]={SDL_LoadBMP("image/Eau.dib.bmp")};
    Cle_Terrain[0]={SDL_LoadBMP("image/Arbre.dib.bmp")};
    Cle_Terrain[6]={SDL_LoadBMP("image/grass.dib.bmp")};
    Cle_Terrain[17]={SDL_LoadBMP("image/road.dib.bmp")};
    Cle_Terrain[2]={SDL_LoadBMP("image/Coffre.dib.bmp")};
    Cle_Terrain[18]={SDL_LoadBMP("image/Dalle.dib.bmp")};


    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *Personnage = NULL;

    SDL_Rect positionFond, positionPerso;

    positionFond.x = 0;
    positionFond.y = 0;
    positionPerso.x = 0;
    positionPerso.y = 0;


    SDL_Init(SDL_INIT_VIDEO); // D�marrage de la SDL (ici : chargement du syst�me vid�o)

    SDL_WM_SetIcon(SDL_LoadBMP("image/sdl_icone.bmp"),NULL);

    ecran = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE);

    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);


    imageDeFond = SDL_LoadBMP("image/grass.dib.bmp");
    Personnage = SDL_LoadBMP("image/Hero.bmp");
    SDL_SetColorKey(Personnage, SDL_SRCCOLORKEY,SDL_MapRGB(Personnage->format,120,195,128));


    for (int i=0; i<24; i++)
    {
        for (int j=0; j<32; j++)
        {
            positionFond.x= j*imageDeFond->w;
            positionFond.y= i*imageDeFond->h;
            SDL_BlitSurface(Cle_Terrain[PeuImporte[i][j]-65], NULL, ecran, &positionFond);

        }
    }

    SDL_BlitSurface(Personnage, NULL, ecran, &positionPerso);



    SDL_Flip(ecran);
    pause();

    SDL_FreeSurface(imageDeFond);
    SDL_Quit(); // Arr�t de la SDL (lib�ration de la m�moire).

    return EXIT_SUCCESS;
}


void pause()
{
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT :
            continuer = 0;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            }
            break;
        }
    }

}

void Lecture_tableau (char tableau[][33], FILE *fichier )
{
    int i,j;
    for (i=0; i< 24; i++)
    {
        for (j=0; j< 33; j++)
        {
            tableau[i][j] = fgetc(fichier);
            printf("%c",tableau[i][j]);

        }
    }
}


