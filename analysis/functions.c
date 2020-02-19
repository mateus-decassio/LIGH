#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data_structs.h"
#include "functions.h"

#define BUFFERSIZE 512


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

int calculate_sub(int a, int b)
{
  return abs(b-a);
}; //FINALIZADO


char *extrac_intron(char *source, int stride, int offset)
{
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  
  //alocar o espaço para receber o vetor
  char *ret = (char *) malloc ((offset + 1) * sizeof(char));

  strncpy(ret, source+stride, offset);
  ret[offset] = '\0';

  return ret;
}; //FINALIZADO


int verify_region(int i_begin, int i_end, unsigned int size, divisions *regions)
{
  unsigned int i;
  for (i = 0; i < size; ++i)
  {
    if ((i_begin >= regions[i].begin) && (i_end <= regions[i].end))
      return 1; //VERDADEIRO
  }
  return 0; //FALSO
}; //FINALIZADO, mas pode ocorrer algum erro. prestar atenção


void analysis_freq_intron(global *parameters, des *description, sample *samples, i_list *L)
{
  unsigned int i, j, intron_counter;
  int i_begin, i_end, r_begin, r_end, offset;
  char *sequence;
  
  intron_counter = 0;
  for (i = 0; i < parameters->number_of_regions; ++i)
  {
    if (!strcmp(description[i].id, "Intron"))
    {
      intron_counter ++;
      i_begin = description[i].begin;
      i_end = description[i].end;
      //printf("esse é o intron %d que começa no %d e termina no %d\n", intron, e_begin, i_end);

      //ajustar o point para apontar sempre para o último nó de um intron (1,2,3,4...)
      L->point = L->tail;

      for (j = 0; j < parameters->total_of_samples; ++j)
      {
        if (verify_region(i_begin, i_end, samples[j].allele[0].size, samples[j].allele[0].regions))
        {
          //extrair o intron
          r_begin = calculate_sub(samples[j].allele[0].regions[0].begin, i_begin); //calcula o stride (quantos caracteres devem ser ignorados) para começar a cópia
          r_end = calculate_sub(samples[j].allele[0].regions[0].begin, i_end);
          offset = calculate_sub(r_begin, r_end) + 1; //contém o valor de caracteres que devem ser copiados para dentro do destino

          sequence = extrac_intron(samples[j].allele[0].sequence, r_begin, offset);
          //printf(" INTRON = %d \n COMPRIMENTO = %d \n SEQUENCIA = %s\n\n", intron_counter, strlen(sequence), sequence);
          
          
          //inserir na lista de introns encontrados
          insert_intron(L, sequence, samples[j].allele[0].name, (short int)intron_counter, samples[j].homozygous);

        }

        if (samples[j].homozygous == false)
        {
          if (verify_region(i_begin, i_end, samples[j].allele[1].size, samples[j].allele[1].regions))
        {
          //extrair o intron
          r_begin = calculate_sub(samples[j].allele[1].regions[0].begin, i_begin);
          offset = calculate_sub(samples[j].allele[1].regions[0].begin, i_end);
          offset = calculate_sub(r_begin, r_end) + 1;

          sequence = extrac_intron(samples[j].allele[1].sequence, r_begin, offset);
          //printf(" INTRON = %d \n COMPRIMENTO = %d \n SEQUENCIA = %s\n\n", intron_counter, strlen(sequence), sequence);
          
          //inserir na lista de introns encontrados
          insert_intron(L, sequence, samples[j].allele[1].name, (short int)intron_counter, samples[j].homozygous);

        }
        }
      }
    }
  }
}; //FINALIZADO


void analysis_freq_allele(global *parameters, des *description, sample *samples, al_list *L)
{
  unsigned int i;
  
  for (i = 0; i < parameters->total_of_samples; ++i)
  {
    insert_allele_in_node(L, samples[i].allele[0].name, samples[i].homozygous);

    if (samples[i].homozygous == false)
      insert_allele_in_node(L, samples[i].allele[1].name, samples[i].homozygous);
  }
}; //FAZERRRRRRRRRRRRRRR

/* ================================================================================================= */



/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR AS LISTAS ========================== */

void initialize_i_list(i_list *L)
{
  L->size = 0;
  L->head = NULL;
	L->tail = NULL;
  L->point = NULL; 
}; //FINALIZADO


void initialize_al_list(al_list *L)
{
  L->size = 0;
  L->head = NULL;
	L->tail = NULL; 
}; //FINALIZADO


i_node *create_i_Node(char *sequence, short int id)
{ 
	int size;

  i_node *new = (i_node *) malloc (sizeof(i_node));
	if (!new)
  {
		printf("NÃO FOI POSSÍVEL ALOCAR O NOVO NÓ! ERRO NA FUNÇÃO create_i_Node OU ESPAÇO INSIFICIENTE.\n");
		exit (0);
	}
	new->next = NULL;
  new->id = id;

  new->list = (al_list *) malloc (sizeof(al_list));
  initialize_al_list(new->list);
  
  size = (unsigned int)strlen(sequence);
  new->sequence = (char *) malloc (size+1 * sizeof(char));
  strncpy(new->sequence, sequence, size);
  new->sequence[size] = '\0';
  
	return new;
}; //FINALIZADO


al_node *create_al_Node(char *allele)
{ 
	int size;

  al_node *new = (al_node *) malloc (sizeof(al_node));
	if (!new)
  {
		printf("NÃO FOI POSSÍVEL ALOCAR O NOVO NÓ! ERRO NA FUNÇÃO create_al_Node OU ESPAÇO INSIFICIENTE.\n");
		exit (0);
	}
	new->next = NULL;

  
  size = (unsigned int)strlen(allele);
  new->allele = (char *) malloc (size+1 * sizeof(char));
  strncpy(new->allele, allele, size);
  new->allele[size] = '\0';

  new->counter++;
  
	return new;
}; //FINALIZADO


void insert_intron(i_list *L, char *sequence, char *allele, short int id, bool homozygous)
{
  i_node *auxiliar = NULL;

	if (!L->head)
  {
    i_node *new = create_i_Node(sequence, id);
		L->head = new;
    L->tail = new;
    L->point = new;

    insert_allele_in_node(new->list, allele, homozygous);
    L->size++;
	}
  else
  {
    //buscar se nó ja existe
    auxiliar = search_intron(L, sequence, id);

    //se o nó não existe, criar um novo nó e inserir o intron naquele nó
    if (!auxiliar)
    {
      i_node *new = create_i_Node(sequence, id);
      L->tail->next = new;
      L->tail = new;
      L->size++;

      insert_allele_in_node(new->list, allele, homozygous);
    }
    //se o nó existe, apenas inserir o nome do alelo na lista do i_node apontado pelo auxiliar
    else
    {
      insert_allele_in_node(auxiliar->list, allele, homozygous);
    }
	}
}; //FINALIZADO


void insert_allele_in_node(al_list *L, char *allele, bool homozygous)
{
  al_node *auxiliar = NULL;

	if (!L->head)
  {
    al_node *new = create_al_Node(allele);
		L->head = new;
    L->tail = new;
    L->size++;

    if (homozygous == true)
      new->counter++;
	}
  else
  {
    //buscar se nó ja existe
    auxiliar = search_allele(L, allele);

    //se o nó não existe, criar um novo nó e inserir o alelo naquele nó
    if (!auxiliar)
    {
      al_node *new = create_al_Node(allele);
      L->tail->next = new;
      L->tail = new;

      if (homozygous == true)
        new->counter++;
    }
    //se o nó existe, apenas incremendar o contador daquele alelo
    else
    {
      auxiliar->counter += homozygous == true ?  2 :  1;
      //                                        SIM  NÃO
    }
	}
}; //FINALIZADO


i_node *search_intron(i_list *L, char *sequence, short int id)
{
  i_node *auxiliar;

  auxiliar = L->point;
  while (auxiliar)
  {
    if (auxiliar->id == id)
    {
      if (!strcmp(auxiliar->sequence, sequence)) //se as sequências forem iguais
      {
        return auxiliar;
      }
    }
    auxiliar = auxiliar->next;
  }
  return auxiliar;
}; //FINALIZADO


al_node *search_allele(al_list *L, char *allele)
{
  al_node *auxiliar;

  auxiliar = L->head;
  while (auxiliar)
  {
    if (!strcmp(auxiliar->allele, allele)) //se existir esse alelo na lista, retorna o ponteiro para ele
    {
      return auxiliar;
    }
    auxiliar = auxiliar->next;
  } 
  return auxiliar;
}; //FINALIZADO

/* ================================================================================================= */



/* ======================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR OS RESULTADOS ======================== */

void impressao_r(i_list *L)
{
  i_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;

  auxiliar_i = L->head;
  while (auxiliar_i)
  {
    printf("INTRON = %d \nCOMPRIMENTO = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
    printf("LISTA DE ALELOS E FREQUÊNCIA:\n");
    
    auxiliar_al = auxiliar_i->list->head;
    while (auxiliar_al)
    {
      printf("ALELO: %s\n     FREQUÊNCIA: %d\n", auxiliar_al->allele, auxiliar_al->counter);

      auxiliar_al = auxiliar_al->next;
    }
    printf("\n\n");
    auxiliar_i = auxiliar_i->next;

  }
}; //FINALIZADO


void results_many_files(char *locus, char *p, i_list *L)
{
  i_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;
  char id[10];
  char count[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 5, "%s", ".txt");

  strcat(path, results);
  strcat(path, locus);

  printf("\nSAVING LOCATION = %s\n", path);


  auxiliar_i = L->head;
  while (auxiliar_i)
  {
    counter++;

    snprintf(folder, strlen(path)+1, "%s", path);
    
    snprintf(intron, 8, "%s", "intron0");
    snprintf(id, 10, "%d", (int)auxiliar_i->id);
    strcat(intron, id);


    strcat(folder, "/");
    strcat(folder, intron);
    strcat(folder, "/");
    
    snprintf(filename, strlen(folder)+1, "%s", folder);

    snprintf(count, 10, "%d", counter);

    strcat(filename, count);
    strcat(filename, txt);
    
    archive = fopen(filename, "w");
    if (!archive)
    {
      fprintf(stderr, "NÃO FOI POSSÍVEL ABRIR/CRIAR O ARQUIVO! (introns.txt na função results_many_files)\n");
      exit(-1);
    }
    //printf("FILENAME = %s, tamanho = %lu\n", filename, strlen(filename));
    //printf("INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
    //printf("LISTA DE ALELOS|FREQUÊNCIA:\n");
    
    fprintf(archive, "INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu\nSEQUENCIA = %s\n\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
    fprintf(archive, "LISTA DE ALELOS|FREQUÊNCIA:\n");
    
    auxiliar_al = auxiliar_i->list->head;
    while (auxiliar_al)
    {
      //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
      fprintf(archive, "%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);

      auxiliar_al = auxiliar_al->next;
    }
    fclose(archive);

    auxiliar_i = auxiliar_i->next;
  }
}; //VOLTAR AQUI


void results_one_file(char *locus, char *p, i_list *L)
{
  i_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;
  char id[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter = 0;
  int id_temp = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 5, "%s", ".txt");

  strcat(path, results);
  strcat(path, locus);

  printf("\nSAVING LOCATION = %s\n", path);


  auxiliar_i = L->head;
  while (auxiliar_i)
  {
    if (id_temp != auxiliar_i->id)
    {
      //fechar o arquivo anterior
      if (id_temp)
        fclose(archive);


      id_temp = auxiliar_i->id;
      snprintf(folder, strlen(path)+1, "%s", path);
    
      snprintf(intron, 8, "%s", "intron0");
      snprintf(id, 10, "%d", (int)auxiliar_i->id);
      strcat(intron, id);


      strcat(folder, "/");
      strcat(folder, intron);
    
      snprintf(filename, strlen(folder)+1, "%s", folder);

      strcat(filename, txt);

      //abrir um novo arquivo
      archive = fopen(filename, "w");

      if (!archive)
      {
        fprintf(stderr, "NÃO FOI POSSÍVEL ABRIR/CRIAR O ARQUIVO! (intron0X, na função results_one_file)\n");
        exit(-1);
      }
    }
    else
    {
      counter++;
      //printf("FILENAME = %s, tamanho = %lu\n", filename, strlen(filename));
      //printf("INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      //printf("LISTA DE ALELOS|FREQUÊNCIA:\n");
    
      fprintf(archive, "INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      fprintf(archive, "LISTA DE ALELOS      |      CONTAGEM      |      FREQUÊNCIA(arrumar)      |\n");
    
      auxiliar_al = auxiliar_i->list->head;
      while (auxiliar_al)
      {
        //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
        fprintf(archive, "%*s | %*d %*s  %*d %*s\n", -20, auxiliar_al->allele, 11, auxiliar_al->counter, 8,"|", 11, -1, 8,"|");

        auxiliar_al = auxiliar_al->next;
      }
    fprintf(archive, "\n\n--------------------------------------------------------------------------------------------\n\n\n");
    auxiliar_i = auxiliar_i->next;
    }
  }
  fclose(archive);
}; //VOLTAR AQUI


void results_statistics(global *parameters, des *description, sample *samples, char *locus, char *p, al_list *L)
{
  al_node *auxiliar_al = NULL;
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char txt[BUFFERSIZE];
  unsigned int i, j, intron_counter;
  int i_begin, i_end;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);
  
  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 5, "%s", ".txt");

  strcat(path, results);
  strcat(path, locus);
  strcat(path, "/");


  //IMPRESSÃO DAS ESTATÍSTICAS 
  snprintf(filename, strlen(path)+1, "%s", path);

  strcat(filename, "statistics");
  strcat(filename, txt);


  archive = fopen(filename, "w");
  if (!archive)
  {
    fprintf(stderr, "NÃO FOI POSSÍVEL ABRIR/CRIAR O ARQUIVO! (statistics.txt na função results_statistics)\n");
    exit(-1);
  }
  //printf("FILENAME[1] = %s, tamanho = %lu\n", filename, strlen(filename));
  //printf("INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
  //printf("LISTA DE ALELOS|FREQUÊNCIA:\n");    
    
  fprintf(archive, "ESTATÍSTICA PARA O LOCUS %s \n\n", locus);
  fprintf(archive, "LISTA DE ALELOS      |      CONTAGEM      |      FREQUÊNCIA(arrumar)\n");

  auxiliar_al = L->head;
  while (auxiliar_al)
  {
    //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
    fprintf(archive, "%*s | %*d %*s %*d\n", -20, auxiliar_al->allele, 11, auxiliar_al->counter, 8,"|", 11, -1);

    auxiliar_al = auxiliar_al->next;
  }
  fclose(archive);


  //IMPRESSÃO DE ALELOS NÃO USADOS
  snprintf(filename, strlen(path)+1, "%s", path);
  strcat(filename, "rejected");
  strcat(filename, txt);

  archive = fopen(filename, "w");
  if (!archive)
  {
    fprintf(stderr, "NÃO FOI POSSÍVEL ABRIR/CRIAR O ARQUIVO! (rejected.txt na função results_statistics)\n");
    exit(-1);
  }

  //printf("FILENAME[2] = %s, tamanho = %lu\n", filename, strlen(filename));
  fprintf(archive, "LEVANTAMENTO DE ALELOS NÃO UTILIZADOS PARA O LOCUS %s\n\n", locus);

  intron_counter = 0;
  for (i = 0; i < parameters->number_of_regions; ++i)
  {
    if (!strcmp(description[i].id, "Intron"))
    {
      intron_counter ++;
      i_begin = description[i].begin;
      i_end = description[i].end;
      
      fprintf(archive, "++++++++++++++++++++++ INTRON %u ++++++++++++++++++++++\n\n", intron_counter);
      fprintf(archive, "LISTA DE ALELOS      |            AMOSTRA            |\n");


      for (j = 0; j < parameters->total_of_samples; ++j)
      {
        if (!verify_region(i_begin, i_end, samples[j].allele[0].size, samples[j].allele[0].regions))
        {
          fprintf(archive, "%*s | %*s %*s\n", -20, samples[j].allele[0].name, 22, samples[j].id, 8,"|");
        }

        if (samples[j].homozygous == false)
        {
          if (!verify_region(i_begin, i_end, samples[j].allele[1].size, samples[j].allele[1].regions))
          {
            fprintf(archive, "%*s | %*s %*s\n", -20, samples[j].allele[1].name, 22, samples[j].id, 8,"|");
          }
        }
      }
    fprintf(archive, "\n\n\n\n");
    }
  }
  fclose(archive);
}; //VOLTAR AQUI

/* ================================================================================================= */