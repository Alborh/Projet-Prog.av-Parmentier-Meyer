#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 1000

void lisTable(char** table[32][32])
{
  int i, j = 0;
  for(j=0; j<32; j++)
    {
      for(i=0; i<32; i++)
	{
	  printf("%d", table[i][j]);
	}
      printf("\n");
    }

}


int main()
{
  char **tableTerrain = malloc(sizeof(char[32][32]));
  FILE *fichier = NULL;
  char chaine[TAILLE_MAX] = " ";
  int i, j =0;
  fichier = fopen("Terrain.txt","r");
  
  if(fichier != NULL)
    {
      while(fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
	  printf("%s",chaine);
	  if (i<32)
	    {
	      tableTerrain[i][j] = *chaine;
	      i = i+1;
	    }
	  if ((i==32) && (j<32))
	    {
	      i = 0;
	      j = j+1;
	      tableTerrain[i][j] = *chaine;
	    }
        }
      
      fclose(fichier);
      
    }
  else
    {
      printf("Impossible d'ouvrir le fichier terrain.txt");
    }
   lisTable(tableTerrain);
  /*  i = 0;
  j = 0;
  while(j<32)
    {
      while(i<32)
	{
	  printf("%d",tableTerrain[i][j]);
	  i++;
	}
      printf("\n");
      i = 0;
      j++;
    }
  */
  return 0;
}
