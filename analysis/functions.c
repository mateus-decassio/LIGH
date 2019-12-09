#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structs.h"
#include "functions.h"


void read_file(char *file_path, des *description, sample *samples)
{
  FILE *file;
  int total_of_samples, number_of_regions, counter, begin, end, homozygous, regions, i, j;
  char linha[5000], sequence[5000], id[50], allele[50];
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

  //aloca o vetor de amostras para receber os dados
  samples = (sample *) malloc (total_of_samples * sizeof(sample));
  if (!samples)
    fprintf(stderr, "ERRO AO ALOCAR O VETOR DE AMOSTRAS");

  
  //pega o total de regiões para a leitura
  fgets (linha, sizeof(linha), file);
  token = strtok (linha, "/");
  sscanf (token, "%d", &number_of_regions);
  printf("(number)REGIONS = %s\n",token);

  //aloca o vetor de descrição para receber os dados
  description = (des *) malloc (number_of_regions * sizeof(des));
  if (!description)
    fprintf(stderr, "ERRO AO ALOCAR O VETOR DE DESCRIÇÃO");

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
    printf("homzigoto? [1 = SIM][2 = NÃO]: %d\n", homozygous);

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
