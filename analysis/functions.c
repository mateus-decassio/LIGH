#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "data_structs.h"
#include "functions.h"

#define BUFFERSIZE 512

unsigned int counter_global = 0;

/* ======================= FUNÇÕES/PROCEDIMENTOS PARA ALOCAÇÃO / DESALOCAÇÃO ======================= */

sample* allocate_samp(unsigned int size)
{
  sample *samples = (sample *) malloc (size * sizeof(sample));
  if (!samples)
  {
    fprintf(stderr, "ERRO AO ALOCAR O VETOR DE AMOSTRAS!\n");
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


void deallocate_regions(divisions *regions)
{
  free(regions);
}; //TESTAR


void deallocate_alleles(alleles *allele)
{
  deallocate_regions(allele->regions);
  free(allele);
}; //TESTAR


void deallocate_sample(sample *samples)
{
  deallocate_alleles(samples->allele);
  free(samples);
}; //TESTAR


void deallocate_global(global *parameters)
{
  free(parameters);
}; //TESTAR


void deallocate_al_list(al_list *L)
{
  al_node *aux1, *aux2;
	
  aux1 = L->head;
	while (aux1)
  {
		aux2 = aux1;
		aux1 = aux1->next;

		free (aux2);
		aux2 = NULL;
	}

  L->size = 0;
  free(L->head);
  free(L->tail);
}; //TESTAR


void deallocate_ie_list(ie_list *L)
{
  ie_node *aux1, *aux2;
	
  aux1 = L->head;
	while (aux1)
  {
		aux2 = aux1;
		aux1 = aux1->next;


    deallocate_al_list(aux2->list);
		free (aux2);
		aux2 = NULL;
	}

  L->size = 0;
  free(L->head);
  free(L->tail);
  free(L->point);
}; //TESTAR

/* ================================================================================================= */



/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A LEITURA ========================== */

void insert_region(sample *samples, unsigned int pos, unsigned int al, unsigned int posic, int begin, int end)
{
  samples[pos].allele[al].regions[posic].begin = begin;
  samples[pos].allele[al].regions[posic].end = end;

  //printf("BEGIN = %d, END = %d\n",samples[pos].allele[al].regions[posic].begin, samples[pos].allele[al].regions[posic].end);
}; //FINALIZADO


void insert_allele(sample *samples, unsigned int pos, unsigned int al, char *id, char *name, char *sequence, int begining)
{
  unsigned int size;
  samples[pos].valid = 0;
  samples[pos].pos_begining = begining;

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
  unsigned int total_of_samples;
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
  //printf("token = %s\n", token);
	sscanf (token, "%d", &total_of_samples);
  //printf("TOTAL OF SAMPLES = %d\n", total_of_samples);
  parameters->total_of_samples = total_of_samples;
  
  parameters->total_of_alleles = (2 * total_of_samples);
  //-----------------------------------------------------------------

  fclose(file);
}; //FINALIZADO


void read_file(char *file_path, sample *samples, global *parameters)
{
  FILE *file;
  int begin, end, begining;
  unsigned int counter, total_of_samples, homozygous, i, j, region;
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
  //leitura das sequências
  for (counter = 0; counter < total_of_samples; ++counter)
  {
    fgets (linha, sizeof(linha), file);
    token = strtok (linha, "/");
    sscanf (token, "%d", &homozygous);
    //printf("homozigoto? [1 = SIM][2 = NÃO]: %d\n", homozygous);


    fgets (linha, sizeof(linha), file);
    token = strtok (linha, ",");
    sscanf (token, "%d", &begining);
    

    //aloca a quantidades de alelos para aquela amostra
    allocate_alleles(samples, counter, homozygous);

    for (i = 0; i < homozygous; ++i) //i varia de 0 a 1
    {
      fgets (linha, sizeof(linha), file);
      token = strtok (linha, ",");
      sscanf (token, "%d", &region);
      parameters->N_REGIONS = region;
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

      insert_allele(samples, counter, i, id, allele, sequence, begining);
    }
  }
  fclose(file);
}; // TESTAR

/* ================================================================================================= */



/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A ANÁLISE ========================== */

int calculate_sub(int a, int b)
{
  if ((a > 0 && b > 0) || (a < 0 && b < 0))
    return abs(b-a) + 1;
  else if ((a > 0 && b < 0) || (a < 0 && b > 0))
    return abs(b-a);
}; //FINALIZADO


char *extrac_intron(char *source, int stride, int offset)
{
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  
  //alocar o espaço para receber o vetor
  char *ret = (char *) malloc (offset+1 * sizeof(char));

  strncpy(ret, source+stride-1, offset);
  ret[offset] = '\0';

  return ret;
}; //FINALIZADO


int verify_region(int i_begin, int i_end, unsigned int size, divisions *regions)
{
  unsigned int i;
  int begin, end;
  bool contigous;
  for (i = 0; i < size-1; ++i)
  {
    begin = regions[i].end;
    end = regions[i+1].begin;
    //printf("begin = %d, end = %d\n", begin, end);
    if (end == begin+1)
    {
      contigous = true;
    }
    else
    {
      contigous = false;
      break;
    }
  }

  if (contigous == true)
  {
    if (i_begin >= regions[0].begin && i_end <= regions[size-1].end)
      return 1; //VERDADEIRO, pertence ao intervalo
    else
      return 0; //FALSO, não pertence ao intervalo
  }
  else
  {
    return -1; //FALSO, o intervalo não é contíguo
  }
}; //FINALIZADO, mas pode ocorrer algum erro. Prestar atenção aqui!


void analysis_freq_intron(global *parameters, sample *samples, ie_list *L)
{
  unsigned int i, j;
  int r_begin, r_end, offset;
  char *sequence;
  
  for (i = 0; i < parameters->N_REGIONS; ++i)
  {
    L->point = L->tail;
    for (j = 0; j < parameters->total_of_samples; ++j)
    {
        //printf("AMOSTRA = %s\n", samples[j].id);
        //extrair o intron
        r_begin = samples[j].allele[0].regions[i].begin;
        r_end = samples[j].allele[0].regions[i].end;
        offset = calculate_sub(r_begin, r_end); //contém o valor de caracteres que devem ser copiados para dentro do destino
        //printf("ALELO1: INTRON %d r_begin = %d, r_end = %d, offset = %d\n", i, r_begin, r_end, offset);

        sequence = extrac_intron(samples[j].allele[0].sequence, r_begin, offset);
        //printf("ALELO1: INTRON = %d \nCOMPRIMENTO = %d \nSEQUENCIA = %s\n\n", i, strlen(sequence), sequence);
          
          
        //inserir na lista de introns encontrados
        insert_intron(L, sequence, samples[j].allele[0].name, (short int)i+1, samples[j].homozygous);

        if (samples[j].homozygous == false)
        {
          //extrair o intron
          r_begin = samples[j].allele[1].regions[i].begin;
          r_end = samples[j].allele[1].regions[i].end;
          offset = calculate_sub(r_begin, r_end);
          //printf("ALELO2: INTRON %d r_begin = %d, r_end = %d, offset = %d\n", i, r_begin, r_end, offset);


          sequence = extrac_intron(samples[j].allele[1].sequence, r_begin, offset);
          //printf("ALELO2: INTRON = %d \nCOMPRIMENTO = %d \nSEQUENCIA = %s\n\n", i, strlen(sequence), sequence);
            
          //inserir na lista de introns encontrados
          insert_intron(L, sequence, samples[j].allele[1].name, (short int)i+1, samples[j].homozygous);
        }
        //printf("PARA O ÍNTRON %d, AMOSTRA %s OK!\n", i+1, samples[j].id);
      }
  }
}; //FINALIZADO


void analysis_freq_exon(global *parameters, sample *samples, ie_list *L)
{
  unsigned int i, j;
  int r_begin, r_end, offset;
  char *sequence;
  
  for (i = 0; i < parameters->N_REGIONS; ++i)
  {
    L->point = L->tail;
    for (j = 0; j < parameters->total_of_samples; ++j)
    {
        //extrair o exon
        if (i == 0)
        {
          r_begin = samples[j].allele[0].regions[i].begin + abs(samples[j].pos_begining);
        }
        else
        {
          r_begin = samples[j].allele[0].regions[i].begin;
        }
        r_end = samples[j].allele[0].regions[i].end;
        offset = calculate_sub(r_begin, r_end); //contém o valor de caracteres que devem ser copiados para dentro do destino
        //printf("ALELO1: EXON %d r_begin = %d, r_end = %d, offset = %d\n", i, r_begin, r_end, offset);

        sequence = extrac_intron(samples[j].allele[0].sequence, r_begin, offset);
        //printf("ALELO1: EXON = %d \nCOMPRIMENTO = %d \nSEQUENCIA = %s\n\n", i, strlen(sequence), sequence);
          
          
        //inserir na lista de introns encontrados
        insert_intron(L, sequence, samples[j].allele[0].name, (short int)i+1, samples[j].homozygous);

        if (samples[j].homozygous == false)
        {
          //extrair o exon
          if (i == 0)
          {
            r_begin = samples[j].allele[1].regions[i].begin + abs(samples[j].pos_begining);
          }
          else
          { 
            r_begin = samples[j].allele[1].regions[i].begin;
          }
          r_end = samples[j].allele[1].regions[i].end;
          offset = calculate_sub(r_begin, r_end);
          //printf("ALELO2: EXON %d r_begin = %d, r_end = %d, offset = %d\n", i, r_begin, r_end, offset);


          sequence = extrac_intron(samples[j].allele[1].sequence, r_begin, offset);
          //printf("ALELO2: EXON = %d \nCOMPRIMENTO = %d \nSEQUENCIA = %s\n\n", i, strlen(sequence), sequence);
            
          //inserir na lista de introns encontrados
          insert_intron(L, sequence, samples[j].allele[1].name, (short int)i+1, samples[j].homozygous);
        }
      }
  }
}; //FINALIZADO

/*
void analysis_freq_allele(global *parameters, sample *samples, al_list *L, int intron_counter, int N_REGIONS)
{
  al_node *auxiliar = NULL;
  unsigned int i, j;
  int intron_tag;
  int i_begin, i_end;
  
  for (i = 0; i < parameters->total_of_samples; ++i)
  {
    insert_allele_in_node(L, samples[i].allele[0].name, samples[i].homozygous);

    if (samples[i].homozygous == false)
      insert_allele_in_node(L, samples[i].allele[1].name, samples[i].homozygous);
  }

  //inicializar o vetor de cada elemento da lista de alelos encontrados
  initialize_vector_al_list(L, intron_counter);


  
  //decrementar os vetores
  intron_tag = 0;
  for (i = 0; i < N_REGIONS; ++i)
  {
    if (!strcmp(description[i].id, "Intron"))
    {
      intron_tag ++;
      i_begin = description[i].begin;
      i_end = description[i].end;


      for (j = 0; j < parameters->total_of_samples; ++j)
      {
        if (!verify_region(i_begin, i_end, samples[j].allele[0].size, samples[j].allele[0].regions))
        {
          //procurar na lista o alelo correspondente que não tem informação para esse intron
          auxiliar = search_allele(L, samples[j].allele[0].name);

          //decrementar
          decrement(auxiliar, intron_tag-1);


          if (samples[j].homozygous == true)
            decrement(auxiliar, intron_tag-1);
        }

        if (samples[j].homozygous == false)
        {
          if (!verify_region(i_begin, i_end, samples[j].allele[1].size, samples[j].allele[1].regions))
          {
            //procurar na lista o alelo correspondente que não tem informação para esse intron
            auxiliar = search_allele(L, samples[j].allele[1].name);

            //decrementar
            decrement(auxiliar, intron_tag-1);
          }
        }
      }
    }
  }    
}; //FINALIZADO


void decrement(al_node *node, int posic)
{
  node->alleles_used[posic]--;
}; //FINALIZADO


void remove_samples(global *parameters, sample *samples, int counter)
{
  int i, j, k, i_begin, i_end, size, begin, end;
  bool contigous;


  //VERIFICAR SE É CONTÍGUO
  fprintf(stderr, "LISTA DE AMOSTAS COM SEQUÊNCIAS NÃO CONTÍGUAS:\n\n");
  for (j = 0; j < parameters->total_of_samples; ++j)
  {
    size = samples[j].allele[0].size;
    for (k = 0; k < size-1; ++k)
    {
      begin = samples[j].allele[0].regions[k].end;
      end = samples[j].allele[0].regions[k+1].begin;

      if (end == begin+1)
      {
        contigous = true;
      }
      else
      {
        contigous = false;
        break;
      }
    }

    if (contigous == false)
    {
      samples[j].valid = 1;
      fprintf(stderr, "%s\n", samples[j].id);
      //imprimir na saída de erro
    }
  }

  
  //VERIFICAR SE PERTENCE AO INTERVALO TODAS AS AMOSTRAS
  fprintf(stderr, "LISTA DE AMOSTAS COM SEQUÊNCIAS INCOMPLETAS PARA TODOS OS ÍNTRONS:\n");
  for (i = 0; i < parameters->number_of_regions; ++i)
  {
    if (!strcmp(description[i].id, "Intron"))
    {
      i_begin = description[i].begin;
      i_end = description[i].end;

      for (j = 0; j < parameters->total_of_samples; ++j)
      {
        if (!samples[j].valid) //SE A AMOSTRA FOR VÁLIDA, pesquisar
        {
          
        }
      }
  }
} //TESTAR
*/
/* ================================================================================================= */



/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR AS LISTAS ========================== */

void initialize_ie_list(ie_list *L)
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


void initialize_vector_al_list(al_list *L, int intron_counter)
{
  al_node *auxiliar = L->head;
  int i;
  
  while (auxiliar)
  {
    //alocação
    auxiliar->alleles_used = (int *) malloc (intron_counter * sizeof(int));

    //colocar o contador em todos as posições do vetor, para ser decrementado depois
    for (i = 0; i < intron_counter; ++i)
    {
      auxiliar->alleles_used[i] = auxiliar->counter;
    }

    auxiliar = auxiliar->next;
  }
}; //TESTAR


ie_node *create_ie_Node(char *sequence, short int id)
{ 
	int size;

  ie_node *new = (ie_node *) malloc (sizeof(ie_node));
	if (!new)
  {
		printf("NÃO FOI POSSÍVEL ALOCAR O NOVO NÓ! ERRO NA FUNÇÃO create_ie_Node OU ESPAÇO INSIFICIENTE.\n");
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


void insert_intron(ie_list *L, char *sequence, char *allele, short int id, bool homozygous)
{
  ie_node *auxiliar = NULL;

	if (!L->head)
  {
    ie_node *new = create_ie_Node(sequence, id);
		L->head = new;
    L->tail = new;
    L->point = new;

    insert_allele_in_node(new->list, allele, homozygous);
    L->size++;
    //printf("criou um novo nó %d\n", counter_global++);
	}
  else
  {
    //buscar se nó ja existe
    auxiliar = search_intron(L, sequence, id);

    //se o nó não existe, criar um novo nó e inserir o intron naquele nó
    if (!auxiliar)
    {
      ie_node *new = create_ie_Node(sequence, id);
      L->tail->next = new;
      L->tail = new;
      L->size++;

      //printf("criou um novo nó %d\n", counter_global++);

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


ie_node *search_intron(ie_list *L, char *sequence, short int id)
{
  ie_node *auxiliar;

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


void impressao_r(ie_list *L)
{
  ie_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;

  auxiliar_i = L->head;
  while (auxiliar_i)
  {
    printf("INTRON/EXON = %d \nCOMPRIMENTO = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
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


void results_many_files_i(char *locus, char *p, ie_list *L)
{
  ie_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;
  char id[10];
  char count[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter, count_equal_alleles, count_diff_alleles = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 5, "%s", ".txt");

  strcat(path, results);
  strcat(path, locus);


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
    fprintf(archive, "LISTA DE ALELOS      |      CONTAGEM      |\n");
    
    auxiliar_al = auxiliar_i->list->head;
    count_diff_alleles = 0;
    count_equal_alleles = 0;
    while (auxiliar_al)
    {
      //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
      fprintf(archive, "%*s | %*d %*s\n", -20, auxiliar_al->allele, 11, auxiliar_al->counter, 8,"|");
      //fprintf(archive, "%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
      count_diff_alleles += 1;
      count_equal_alleles += auxiliar_al->counter;

      auxiliar_al = auxiliar_al->next;
    }
    fprintf(archive, "\n--- CONTAGEM FINAL (alelos diferentes) = %d ---", count_diff_alleles);
    fprintf(archive, "\n--- CONTAGEM FINAL (TODOS os alelos)= %d ---\n", count_equal_alleles);
    fclose(archive);

    auxiliar_i = auxiliar_i->next;
  }
}; //FINALIZADO


void results_one_file_i(char *locus, char *p, ie_list *L)
{
  ie_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;
  char id[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter, count_equal_alleles, count_diff_alleles = 0;
  int id_temp = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 5, "%s", ".txt");

  strcat(path, results);
  strcat(path, locus);


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
      counter = 0;
    }
    else
    {
      counter++;
      //printf("FILENAME = %s, tamanho = %lu\n", filename, strlen(filename));
      //printf("INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      //printf("LISTA DE ALELOS|FREQUÊNCIA:\n");
    
      fprintf(archive, "INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      fprintf(archive, "LISTA DE ALELOS      |      CONTAGEM      |\n");
    
      auxiliar_al = auxiliar_i->list->head;
      count_equal_alleles = 0;
      count_diff_alleles = 0;
      while (auxiliar_al)
      {
        //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
        fprintf(archive, "%*s | %*d %*s\n", -20, auxiliar_al->allele, 11, auxiliar_al->counter, 8,"|");
        count_diff_alleles += 1;
        count_equal_alleles += auxiliar_al->counter;
        auxiliar_al = auxiliar_al->next;
      }
    fprintf(archive, "\n--- CONTAGEM FINAL (alelos diferentes) = %d ---", count_diff_alleles);
    fprintf(archive, "\n--- CONTAGEM FINAL (TODOS os alelos)= %d ---\n", count_equal_alleles);
    fprintf(archive, "\n\n--------------------------------------------------------------------------------------------\n\n\n");
    auxiliar_i = auxiliar_i->next;
    }
  }
  fclose(archive);
}; //FINALIZADO


void results_many_files_e(char *locus, char *p, ie_list *L)
{
  ie_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;
  char id[10];
  char count[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter, count_equal_alleles, count_diff_alleles = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 5, "%s", ".txt");

  strcat(path, results);
  strcat(path, locus);


  auxiliar_i = L->head;
  while (auxiliar_i)
  {
    counter++;

    snprintf(folder, strlen(path)+1, "%s", path);
    
    snprintf(intron, 8, "%s", "exon0");
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
      fprintf(stderr, "NÃO FOI POSSÍVEL ABRIR/CRIAR O ARQUIVO! (exons.txt na função results_many_files)\n");
      exit(-1);
    }
    //printf("FILENAME = %s, tamanho = %lu\n", filename, strlen(filename));
    //printf("INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
    //printf("LISTA DE ALELOS|FREQUÊNCIA:\n");
    
    fprintf(archive, "EXON = %d.%d \nCOMPRIMENTO(em pb) = %lu\nSEQUENCIA = %s\n\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
    fprintf(archive, "LISTA DE ALELOS      |      CONTAGEM      |\n");
    
    auxiliar_al = auxiliar_i->list->head;
    count_diff_alleles = 0;
    count_equal_alleles = 0;
    while (auxiliar_al)
    {
      //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
      fprintf(archive, "%*s | %*d %*s\n", -20, auxiliar_al->allele, 11, auxiliar_al->counter, 8,"|");
      //fprintf(archive, "%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
      count_diff_alleles += 1;
      count_equal_alleles += auxiliar_al->counter;

      auxiliar_al = auxiliar_al->next;
    }
    fprintf(archive, "\n--- CONTAGEM FINAL (alelos diferentes) = %d ---", count_diff_alleles);
    fprintf(archive, "\n--- CONTAGEM FINAL (TODOS os alelos)= %d ---\n", count_equal_alleles);
    fclose(archive);

    auxiliar_i = auxiliar_i->next;
  }
}; //FINALIZADO


void results_one_file_e(char *locus, char *p, ie_list *L)
{
  ie_node *auxiliar_i = NULL;
  al_node *auxiliar_al = NULL;
  char id[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter, count_equal_alleles, count_diff_alleles = 0;
  int id_temp = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 5, "%s", ".txt");

  strcat(path, results);
  strcat(path, locus);


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
    
      snprintf(intron, 8, "%s", "exon0");
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
      counter = 0;
    }
    else
    {
      counter++;
      //printf("FILENAME = %s, tamanho = %lu\n", filename, strlen(filename));
      //printf("INTRON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      //printf("LISTA DE ALELOS|FREQUÊNCIA:\n");
    
      fprintf(archive, "EXON = %d.%d \nCOMPRIMENTO(em pb) = %lu \nSEQUENCIA = %s\n\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      fprintf(archive, "LISTA DE ALELOS      |      CONTAGEM      |\n");
    
      auxiliar_al = auxiliar_i->list->head;
      count_equal_alleles = 0;
      count_diff_alleles = 0;
      while (auxiliar_al)
      {
        //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
        fprintf(archive, "%*s | %*d %*s\n", -20, auxiliar_al->allele, 11, auxiliar_al->counter, 8,"|");
        count_diff_alleles += 1;
        count_equal_alleles += auxiliar_al->counter;
        auxiliar_al = auxiliar_al->next;
      }
    fprintf(archive, "\n--- CONTAGEM FINAL (alelos diferentes) = %d ---", count_diff_alleles);
    fprintf(archive, "\n--- CONTAGEM FINAL (TODOS os alelos)= %d ---\n", count_equal_alleles);
    fprintf(archive, "\n\n--------------------------------------------------------------------------------------------\n\n\n");
    auxiliar_i = auxiliar_i->next;
    }
  }
  fclose(archive);
}; //FINALIZADO


void results_statistics(global *parameters, char *locus, char *p, al_list *L)
{
  al_node *auxiliar_al = NULL;
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char txt[BUFFERSIZE];
  double a, b, freq = 0.0;
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
  fprintf(archive, "LISTA DE ALELOS      |      CONTAGEM      |    FREQUÊNCIA  |        %%      |\n");

  auxiliar_al = L->head;
  while (auxiliar_al)
  {
    //printf("%s | %d\n", auxiliar_al->allele, auxiliar_al->counter);
    //printf("divisão entre %d e %u\n", auxiliar_al->counter , parameters->total_of_alleles);
    a = (double)auxiliar_al->counter;
    b = (double)parameters->total_of_alleles;
    
    freq = (a / b);
    fprintf(archive, "%*s | %*d %*s %*.5g %*s %*.5g %*s\n", -20, auxiliar_al->allele, 11, auxiliar_al->counter, 8,"|", 10, freq, 5, "|", 10, freq*100, 4, "|");

    auxiliar_al = auxiliar_al->next;
  }
  fclose(archive);
}; //FINALIZADO


void results_one_file_fastaI(char *locus, char *p, ie_list *L)
{
  ie_node *auxiliar_i = NULL;
  char id[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter, id_temp = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 7, "%s", ".fasta");

  strcat(path, results);
  strcat(path, locus);


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
    
      snprintf(intron, 12, "%s", "seq-intron0");
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
        fprintf(stderr, "Erro na função results_one_file_fastaI\n");
        exit(-1);
      }
      counter = 0;
    }
    else
    {
      counter++;    
      fprintf(archive, ">INTRON %d.%d  %lu bp\n%s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      auxiliar_i = auxiliar_i->next;
    }
  }
  fclose(archive);
}; //FINALIZADO


void results_one_file_fastaE(char *locus, char *p, ie_list *L)
{
  ie_node *auxiliar_i = NULL;
  char id[10];
  char path[BUFFERSIZE];
  char filename[BUFFERSIZE];
  char results[BUFFERSIZE];
  char folder[BUFFERSIZE];
  char txt[BUFFERSIZE];
  char intron[BUFFERSIZE];
  int counter, id_temp = 0;
  FILE *archive;

  snprintf(path, strlen(p)+1, "%s", p);

  snprintf(results, 10, "%s", "/RESULTS/");
  snprintf(txt, 7, "%s", ".fasta");

  strcat(path, results);
  strcat(path, locus);


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
    
      snprintf(intron, 10, "%s", "seq-exon0");
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
        fprintf(stderr, "Erro na função results_one_file_fastaE\n");
        exit(-1);
      }
      counter = 0;
    }
    else
    {
      counter++;    
      fprintf(archive, ">EXON %d.%d  %lu bp\n%s\n", auxiliar_i->id, counter, strlen(auxiliar_i->sequence), auxiliar_i->sequence);
      auxiliar_i = auxiliar_i->next;
    }
  }
  fclose(archive);
}; //FINALIZADO

/* ================================================================================================= */