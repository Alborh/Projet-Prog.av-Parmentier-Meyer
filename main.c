#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 1000




int main()
{
    FILE *fichier = NULL;
    char chaine[TAILLE_MAX] = " ";

    fichier = fopen("C:\\Users\\MEYER\\Desktop\\L2-informatique\\Projet RPG\\terrain.txt","r");

    if(fichier != NULL)
    {
        while(fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
            printf("%s",chaine);
        }

        fclose(fichier);

    }
    else
    {
        printf("Impossible d'ouvrir le fichier terrain.txt");
    }



    return 0;
}
