#include <stdio.h>
#include <stdlib.h>
//#define TAILLE_MAX 1000

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
  /*char **tableTerrain = (char**)malloc(32*sizeof(char*));
  for(i = 0; i>32; i++)
    {
      tableTerrain[i] = (char*)malloc(32*sizeof(char));
    }
  */
  char* tableTerrain[32][32];
  FILE *file = NULL;
  //char chaine[TAILLE_MAX] = " ";
  /* file = fopen("Terrain.txt","r");
  
  if(file != NULL)
    {
      while(fgets(chaine, TAILLE_MAX, file) != NULL)
        {
	  printf("%s",chaine);
        }
      
      fclose(file);
      
    }
  else
    {
      printf("Impossible d'ouvrir le fichier Terrain.txt");
      }*/
  file = fopen("Terrain.txt","r");
  char c;
  while((c != EOF) && (j<32))
    {
      printf("i = %d et j = %d",i,j);
      c = fgetc(file);
      printf(" c = %d\n",c);
      if( c != '\n')
	{
	  tableTerrain[i][j] = c;
	  i++;
	}
      if (i > 31)
	{
	  i = 0;
	  j++;
	}
	
    }
  fclose(file);
  //lisTable(*tableTerrain);
   i = 0;
  j = 0;
  while(j<32)
    {
      while(i<32)
	{
	  printf("%s",tableTerrain[i][j]);
	  i++;
	}
      printf("\n");
      i = 0;
      j++;
    }
  
  return 0;
}
