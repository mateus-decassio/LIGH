#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data_structs.h"
#include "functions.h"

/* ======================= FUNÇÕES/PROCEDIMENTOS PARA ALOCAÇÃO / DESALOCAÇÃO ======================= */

des* allocate_desc(unsigned int size)
{
  des *description = (des *) malloc (size * sizeof(des));
    if (!description)
  {
    fprintf(stderr, "ERRO AO ALOCAR O VETOR DE DESCRIÇÃO!");
    return NULL;
  }
  return (description);
}; //FINALIZADO


sample* allocate_samp(unsigned int size)
{
  sample *samples = (sample *) malloc (size * sizeof(sample));
  if (!samples)
  {
    fprintf(stderr, "ERRO AO ALOCAR O VETOR DE AMOSTRAS!");
    return NULL;
  }
  return (samples);
}; //FINALIZADO


void allocate_alleles(sample *samples, unsigned int pos, unsigned int size)
{
   samples[pos].allele = (alleles *) malloc (size * sizeof(alleles));
   if (size == 1)
      samples[pos].homozygous = true;
    else
      samples[pos].homozygous = false;
}; //FINALIZADO


void allocate_region(sample *samples, unsigned int pos, unsigned int al, unsigned int size)
{
  samples[pos].allele[al].regions = (divisions *) malloc (size * sizeof(divisions));
  samples[pos].allele[al].size = size;
}; //FINALIZADO

/* ================================================================================================= */



/* ====================== FUNÇÕES/PROCEDIMENTOS PARA IMPRESSÃO DOS RESULTADOS ====================== */

void impressao_d(des *description, unsigned int size)
{
  unsigned int counter;

  for (counter = 0; counter < size; ++counter)
  {
    printf("ID = %s, begin = %d, end = %d\n",description[counter].id, description[counter].begin, description[counter].end);
  }
}; //FINALIZADO


void impressao_s(sample *samples, unsigned int size)
{
  unsigned int counter, i;

  for (counter = 0; counter < size; ++counter)
  {
     printf("ID da amostra = %s\n\n", samples[counter].id);

     if (samples[counter].homozygous == true)
     {
      printf("O INDIVÍDUO É HOMOZIGOTO.\n");
      printf("ID do alelo: %s\n", samples[counter].allele[0].name);
      printf("Esse alelo é divido em %d regiões.\n", samples[counter].allele[0].size);

      for (i = 0; i < samples[counter].allele[0].size; ++i)
      {
        printf("BEGIN = %d, END = %d\n",samples[counter].allele[0].regions[i].begin, samples[counter].allele[0].regions[i].end);
      }
      printf("SEQUÊNCIA do alelo: %s\n", samples[counter].allele[0].sequence);
     }
     else
     {
      printf("O INDIVÍDUO É HETEROZIGOTO.\n");
      printf("ID do alelo 1: %s\n", samples[counter].allele[0].name);
      printf("Esse alelo é divido em %d regiões.\n", samples[counter].allele[0].size);

      for (i = 0; i < samples[counter].allele[0].size; ++i)
      {
        printf("BEGIN = %d, END = %d\n",samples[counter].allele[0].regions[i].begin, samples[counter].allele[0].regions[i].end);
      }
      printf("SEQUÊNCIA do alelo1: %s\n\n", samples[counter].allele[0].sequence);

      printf("ID do alelo 2: %s\n", samples[counter].allele[1].name);
      printf("Esse alelo é divido em %d regiões.\n", samples[counter].allele[1].size);

      for (i = 0; i < samples[counter].allele[1].size; ++i)
      {
        printf("BEGIN = %d, END = %d\n",samples[counter].allele[1].regions[i].begin, samples[counter].allele[1].regions[i].end);
      }
      printf("SEQUÊNCIA do alelo2: %s\n", samples[counter].allele[1].sequence);
     }
     printf("\n\n\n");
  }
}; //FINALIZADO

/* ================================================================================================= */



/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A LEITURA ========================== */

void insert_description(des *description, unsigned int pos, char *id, int begin, int end)
{
  unsigned int size = (unsigned int)strlen(id);
  description[pos].id = (char *) malloc (size+1 * sizeof(char));
  
  strncpy(description[pos].id, id, size);
  description[pos].begin = begin;
  description[pos].end = end;

  //printf("ID = %s, begin = %d, end = %d\n",description[pos].id, description[pos].begin, description[pos].end);
}; //FINALIZADO


void insert_region(sample *samples, unsigned int pos, unsigned int al, unsigned int posic, int begin, int end)
{
  samples[pos].allele[al].regions[posic].begin = begin;
  samples[pos].allele[al].regions[posic].end = end;

  //printf("BEGIN = %d, END = %d\n",samples[pos].allele[al].regions[posic].begin, samples[pos].allele[al].regions[posic].end);
}; //FINALIZADO


void insert_allele(sample *samples, unsigned int pos, unsigned int al, char *id, char *name, char *sequence)
{
  unsigned int size;
  
  size = (unsigned int)strlen(id);
  samples[pos].id = (char *) malloc (size+1 * sizeof(char));
  strncpy(samples[pos].id, id, size);
  //printf("ID =  %s\n", samples[pos].id);

  size = (unsigned int)strlen(name);
  samples[pos].allele[al].name = (char *) malloc (size+1 * sizeof(char));
  strncpy(samples[pos].allele[al].name, name, size);
  //printf("NOME DO ALELO =  %s\n", samples[pos].allele[al].name);

  //obs: strlen retorna o tamanho da string sem o caractere nulo no final

  size = (unsigned int)strlen(sequence);
  samples[pos].allele[al].sequence = (char *) malloc (size+1 * sizeof(char));
  strncpy(samples[pos].allele[al].sequence, sequence, size);
  samples[pos].allele[al].sequence[size] = '\0';
  //printf("SEQUÊNCIA =  %s\n", samples[pos].allele[al].sequence);

}; //FINALIZADO


void read_parameters(global *parameters, char *file_path)
{
  FILE *file;
  unsigned int total_of_samples, number_of_regions;
  char linha[9000];
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
  //printf("TOTAL OF SAMPLES = %d\n", total_of_samples);
  parameters->total_of_samples = total_of_samples;
  //-----------------------------------------------------------------

  //-----------------------------------------------------------------
  //pega o total de regiões para a leitura
  fgets (linha, sizeof(linha), file);
  token = strtok (linha, "/");
  sscanf (token, "%d", &number_of_regions);
  //printf("(number)REGIONS = %s\n",token);
  parameters->number_of_regions = number_of_regions;
  //-----------------------------------------------------------------

  fclose(file);
}; //FINALIZADO


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
  //-----------------------------------------------------------------

  //-----------------------------------------------------------------
  //pega o total de regiões para a leitura
  fgets (linha, sizeof(linha), file);
  token = strtok (linha, "/");
  sscanf (token, "%d", &number_of_regions);
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
  fclose(file);
}; // FINALIZADO

/* ================================================================================================= */



/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A ANÁLISE ========================== */

void analysis()
{

}; //FAZER


/* ================================================================================================= */



/* ======================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR OS RESULTADOS ======================== */

void results()
{

}; //FAZER

/* ================================================================================================= */
