#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structs.h"
#include "functions.h"

void insert_description(des *description, unsigned int pos, char *id, int begin, int end)
{
  unsigned int size = (unsigned int)strlen(id);
  description[pos].id = (char *) malloc (size * sizeof(char));
  
  strncpy(description[pos].id, id, size);
  description[pos].begin = begin;
  description[pos].end = end;

  printf("ID = %s, begin = %d, end = %d\n",description[pos].id, description[pos].begin, description[pos].end);
};

void insert_sample(des *description, unsigned int pos, char *id, int begin, int end)
{
  unsigned int size = (unsigned int)strlen(id);
  description[pos].id = (char *) malloc (size * sizeof(char));
  
  strncpy(description[pos].id, id, size);
  description[pos].begin = begin;
  description[pos].end = end;

  printf("ID = %s, begin = %d, end = %d\n",description[pos].id, description[pos].begin, description[pos].end);
};


















void read_file(char *file_path, des *description, sample *samples)
{
  FILE *file;
  int begin, end, homozygous, regions, i, j;
  unsigned int counter, total_of_samples, number_of_regions;
  char linha[5000], sequence[5000], id[50], allele[50];
  char *token;

  file = fopen(file_path, "r");
  if (file == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo.\n");
    exit (-1);
  }
  
  //-----------------------------------------------------------------
  //pega o total de arquivos encontrados para fazer a análise
  fgets (linha, sizeof(linha), file);
	token = strtok (linha, "/");
	sscanf (token, "%d", &total_of_samples);
  printf("(number)SAMPLES = %d\n", total_of_samples);

  //aloca o vetor de amostras para receber os dados
  samples = (sample *) malloc (total_of_samples * sizeof(sample));
  if (!samples)
    fprintf(stderr, "ERRO AO ALOCAR O VETOR DE AMOSTRAS");
  //-----------------------------------------------------------------

  //-----------------------------------------------------------------
  //pega o total de regiões para a leitura
  fgets (linha, sizeof(linha), file);
  token = strtok (linha, "/");
  sscanf (token, "%d", &number_of_regions);
  printf("(number)REGIONS = %s\n",token);

  //aloca o vetor de descrição para receber os dados
  description = (des *) malloc (number_of_regions * sizeof(des));
  if (!description)
    fprintf(stderr, "ERRO AO ALOCAR O VETOR DE DESCRIÇÃO");
  //-----------------------------------------------------------------

  //leitura das regiões
  for (counter = 0; counter < number_of_regions; ++counter)
  {
    fgets (linha, sizeof(linha), file);
    token = strtok (linha, ",");
    sscanf (token, "%s", id);

    token = strtok (NULL, ",");
    sscanf (token, "%d", &begin);

    token = strtok (NULL, ",");
    sscanf (token, "%d", &end);

    //inserção no vetor de descrição
    insert_description(description, counter, id, begin, end);
  }

  //leitura das sequências
  for (counter = 0; counter < total_of_samples; ++counter)
  {
    fgets (linha, sizeof(linha), file);
    token = strtok (linha, "/");
    sscanf (token, "%d", &homozygous);
    printf("homozigoto? [1 = SIM][2 = NÃO]: %d\n", homozygous);

    for (i = 0; i < homozygous; ++i)
    {
      fgets (linha, sizeof(linha), file);
      token = strtok (linha, ",");
      sscanf (token, "%d", &regions);
      printf("DIVIDIDO EM %d REGIÕES\n", regions);

      for (j = 0; j < regions; ++j)
      {
        token = strtok (NULL, "~");
        sscanf (token, "%d", &begin);

        token = strtok (NULL, ",");
        sscanf (token, "%d", &end);
        printf("BEGIN = %d, END = %d\n",begin, end);
      }

      fgets (linha, sizeof(linha), file);
      token = strtok (linha, "/");
      sscanf (token, "%s", id);
      printf("ID =  %s\n", id);

      fgets (linha, sizeof(linha), file);
      token = strtok (linha, "/");
      sscanf (token, "%s", allele);
      printf("ALELO =  %s\n", allele);

      fgets (linha, sizeof(linha), file);
      token = strtok (linha, "/");
      sscanf (token, "%s", sequence);
      printf("SEQUÊNCIA =  %s\n", sequence);
    }
  }

}; //FINALIZAR (colocar na estrutura de dados)


/*
void analysis()
{

}; //FAZER

void results()
{

}; //FAZER
*/
