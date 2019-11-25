#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structs.h"
#include "functions.h"


void read_file(char *file_path)
{
  FILE *file;
  int total_of_samples, number_of_regions, counter, begin, end, homozygous, regions, i, j;
  char linha[5000], id[10];
  char *token;

  file = fopen(file_path, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo.\n");
    exit (-1);
  }

  //pega o total de arquivos encontrados para fazer a análise
  fgets (linha, sizeof(linha), file);
	token = strtok (linha, "/");
	sscanf (token, "%d", &total_of_samples);
  printf("(number)SAMPLES = %d\n", total_of_samples);

  //pega o total de regiões para a leitura
  fgets (linha, sizeof(linha), file);
  token = strtok (linha, "/");
  sscanf (token, "%d", &number_of_regions);
  printf("(number)REGIONS = %s\n",token);


  //pega as regiões
  for (counter = 0; counter < number_of_regions; ++counter)
  {
    fgets (linha, sizeof(linha), file);
    token = strtok (linha, ",");
    sscanf (token, "%s", id);

    token = strtok (NULL, ",");
    sscanf (token, "%d", &begin);

    token = strtok (NULL, ",");
    sscanf (token, "%d", &end);

    printf("ID = %s, begin = %d, end = %d\n",id, begin, end);
  }

  //pega as sequências
  for (counter = 0; counter < total_of_samples; ++counter)
  {
    fgets (linha, sizeof(linha), file);
    token = strtok (linha, "/");
    sscanf (token, "%d", &homozygous);
    printf("%d\n", homozygous);

    for (i = 0; i < homozygous; ++i)
    {
      fgets (linha, sizeof(linha), file);
      token = strtok (linha, ",");
      sscanf (token, "%d", &regions);
      printf("%d\n", regions);

      for (j = 0; j < regions; ++j)
      {
        token = strtok (NULL, "~");
        sscanf (token, "%d", &begin);

        token = strtok (NULL, ",");
        sscanf (token, "%d", &end);
        printf("BEGIN = %d, END = %d\n",begin, end);
      }


    }





  }

}; //FAZER
/*
void analysis()
{

}; //FAZER

void results()
{

}; //FAZER
*/
