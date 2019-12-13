#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structs.h"
#include "functions.h"

/* =========================== FUNÇÕES UTILIZADAS PARA TRATAR A LEITURA =========================== */

void insert_description(des *description, unsigned int pos, char *id, int begin, int end)
{
  unsigned int size = (unsigned int)strlen(id);
  description[pos].id = (char *) malloc (size * sizeof(char));
  
  strncpy(description[pos].id, id, size);
  description[pos].begin = begin;
  description[pos].end = end;

  printf("ID = %s, begin = %d, end = %d\n",description[pos].id, description[pos].begin, description[pos].end);
}; //FINALIZADO

void allocate_alleles(sample *samples, unsigned int pos, unsigned int size)
{
   samples[pos].allele = (alleles *) malloc (size * sizeof(alleles));
}; //TESTAR


void allocate_region(sample *samples, unsigned int pos, unsigned int al, unsigned int size)
{
  samples[pos].allele[al].regions = (divisions *) malloc (size * sizeof(divisions));
  samples[pos].allele[al].size = size;
}; //TESTAR


void insert_region(sample *samples, unsigned int pos, unsigned int al, unsigned int posic, int begin, int end)
{
  samples[pos].allele[al].regions[posic].begin = begin;
  samples[pos].allele[al].regions[posic].end = end;

  printf("BEGIN = %d, END = %d\n",samples[pos].allele[al].regions[posic].begin, samples[pos].allele[al].regions[posic].end);
}; //TESTAR

void insert_allele(sample *samples, unsigned int pos, unsigned int al, char *id, char *name, char *sequence)
{
  unsigned int size;
  
  size = (unsigned int)strlen(id);
  samples[pos].id = (char *) malloc (size * sizeof(char));
  strncpy(samples[pos].id, id, size);
  printf("ID =  %s\n", samples[pos].id);

  size = (unsigned int)strlen(name);
  samples[pos].allele[al].name = (char *) malloc (size * sizeof(char));
  strncpy(samples[pos].allele[al].name, name, size);
  printf("NOME DO ALELO =  %s\n", samples[pos].allele[al].name);


  size = (unsigned int)strlen(sequence);
  samples[pos].allele[al].sequence = (char *) malloc (size * sizeof(char));
  strncpy(samples[pos].allele[al].sequence, sequence, size);
  printf("SEQUÊNCIA =  %s\n", samples[pos].allele[al].sequence);
}; //TESTAR

/* ================================================================================================ */

void read_file(char *file_path, des *description, sample *samples)
{
  FILE *file;
  int begin, end;
  unsigned int counter, total_of_samples, number_of_regions, homozygous, i, j, region;
  char linha[9000], sequence[9000], id[100], allele[100];
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
  printf("TOTAL OF SAMPLES = %d\n", total_of_samples);

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
  //printf("(number)REGIONS = %s\n",token);

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
    //printf("homozigoto? [1 = SIM][2 = NÃO]: %d\n", homozygous);

    //aloca a quantidades de alelos para aquela amostra
    allocate_alleles(samples, counter, homozygous);

    for (i = 0; i < homozygous; ++i) //i varia de 0 a 1
    {
      fgets (linha, sizeof(linha), file);
      token = strtok (linha, ",");
      sscanf (token, "%d", &region);
      //printf("DIVIDIDO EM %d REGIÕES\n", region);

      //aloca a quantidade de regiões que a sequência do alelo i tem 
      allocate_region(samples, counter, i, region);

      for (j = 0; j < region; ++j)
      {
        token = strtok (NULL, "~");
        sscanf (token, "%d", &begin);

        token = strtok (NULL, ",");
        sscanf (token, "%d", &end);
        //printf("BEGIN = %d, END = %d\n",begin, end);

        insert_region(samples, counter, i, j, begin, end);
      }

      fgets (linha, sizeof(linha), file);
      token = strtok (linha, "/");
      sscanf (token, "%s", id);
      //printf("ID =  %s\n", id);

      fgets (linha, sizeof(linha), file);
      token = strtok (linha, "/");
      sscanf (token, "%s", allele);
      //printf("ALELO =  %s\n", allele);

      fgets (linha, sizeof(linha), file);
      token = strtok (linha, "/");
      sscanf (token, "%s", sequence);
      //printf("SEQUÊNCIA =  %s\n", sequence);

      insert_allele(samples, counter, i, id, allele, sequence);
    }
  }

}; //FINALIZAR


/*
void analysis()
{

}; //FAZER

void results()
{

}; //FAZER
*/
