#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 1000

/*void lisTable(char* table[32][32])
{
  int i, j = 0;
  for(j=0; j<32; j++)
    {
      for(i=0; i<32; i++)
	{
	  printf("%s", &table[i][j]);
	}
      printf("\n");
    }
    }*/


int main()
{
  int i, j =0;
  char **tableTerrain = (char**)malloc(32*sizeof(char*));
  for(i = 0; i>32; i++)
    {
      tableTerrain[i] = (char*)malloc(32*sizeof(char));
    }
  FILE *fichier = NULL;
  char chaine[TAILLE_MAX] = " ";
  fichier = fopen("Terrain.txt","r");
  
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
      printf("Impossible d'ouvrir le fichier Terrain.txt");
    }
  fichier = fopen("Terrain.txt","r");
  while(fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
      for (j=0;j<32;j++)
	{
	  for(i=0;i<32;j++)
	    {
	      tableTerrain[i][j] = fgetc(fichier);
	    }
	}
      fclose(fichier);
    }
  //lisTable(*tableTerrain);
  i = 0;
  j = 0;
  while(j<32)
    {
      while(i<32)
	{
	  printf("%s",&tableTerrain[i][j]);
	  i++;
	}
      printf("\n");
      i = 0;
      j++;
    }
  
  return 0;
}
