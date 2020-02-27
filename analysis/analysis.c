// ./analysis -l HLA-A -d /mnt/hgfs/SHARED/HLA-A.txt -r /mnt/hgfs/SHARED
// valgrind --leak-check=full ./analysis -l HLA-A -d /mnt/hgfs/SHARED/HLA-A.txt -r /mnt/hgfs/SHARED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdbool.h>
#include "data_structs.h"
#include "functions.h"

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s -l <locus[HLA-A/B/C/...]> -d <path_to_file.txt>\n", progname);
  exit(-1);
};


int main (int argc, char *argv[])
{
	int opt, intron_counter;
  char *locus, *archive, *path  = NULL;

  des *description;
  sample *samples;
  global *parameters = (global *) malloc (sizeof(global));
  i_list *intron_list = (i_list *) malloc (sizeof(i_list));
  al_list *allele_list = (al_list *) malloc (sizeof(al_list));




/* ====================== TRATAMENTO DE LINHA DE COMANDO ====================== */
  if ( argc < 7 )
    usage(argv[0]);
  //l:d: - o uso do : significa que l recebe um parâmetro adicional, assim como o d
  while ( (opt = getopt (argc, argv, "l:d:r:")) != -1 )
  {
    switch (opt)
    {
      case 'l':
        locus = optarg;
        break;

      case 'd':
        archive = optarg;
        break;

      case 'r':
        path = optarg;
        break;

      case ':':
        printf("Essa opção precisa de um valor!\n");
        break;

      case '?':
        printf("Opção desconhecida: %c\n", optopt);
        break;

      default:
        usage(argv[0]);
    }
  }
/* ====================== FIM DO TRATAMENTO DE LINHA DE COMANDO ====================== */
  
  
  printf("LOCUS = %s\n", locus);
  printf("PATH TO FILE = %s\n", archive);

  read_parameters(parameters, archive);

  description = allocate_desc(parameters->number_of_regions);
  samples = allocate_samp(parameters->total_of_samples);
  
  if (samples && description)
  {
    read_file(archive, description, samples);
  }
  else
  {
    fprintf(stderr, "Impossível realizar a leitura do arquivo. Houve um problema na alocação da estrutura de dados!");
    exit (-1);
  }

  printf("TOTAL OF SAMPLES = %d\n", parameters->total_of_samples);
  printf("TOTAL OF ALLELES = %d\n", parameters->total_of_alleles);
  printf("\n\n");
  printf("\nNUMBER OF REGIONS (description) = %d\n", parameters->number_of_regions);

  
  //IMPRESSÃO DO CABEÇALHO E DA LISTA DE AMOSTRAS ENCONTRADAS
  impressao_d(description, parameters->number_of_regions);
  //impressao_s(samples, parameters->total_of_samples);



  //ANÁLISE
  initialize_i_list(intron_list);
  intron_counter = analysis_freq_intron(parameters, description, samples, intron_list);
  analysis_freq_allele(parameters, description, samples, allele_list, intron_counter);

  printf("\nTHE LOCUS %s HAS %d INTRONS IN THE DNA SEQUENCE.\n", locus, intron_counter);
  printf("\nNUMBER OF INTRONS FOUNDED (all locus included) = %d\n", intron_list->size);
  printf("\nSAVING LOCATION = %s/RESULTS/%s\n", path, locus);




  //IMPRESSÃO DO RESULTADO
  //impressao_r(intron_list);
  results_many_files(locus, path, intron_list);
  results_one_file(locus, path, intron_list);
  results_statistics(parameters, locus, path, allele_list);
  results_rejected_list(parameters, description, samples, locus, path);
  results_used_table(allele_list, intron_counter, locus, path);
  


  //DESALOCAGEM
  deallocate_desc(description);
  printf("finalizou    deallocate_desc\n");

  deallocate_sample(samples);
  printf("finalizou    deallocate_sample\n");
  
  deallocate_global(parameters);
  printf("finalizou    deallocate_global\n");

  //deallocate_i_list(intron_list);
  //printf("finalizou    deallocate_i_list\n");

  //deallocate_al_list(allele_list);
  //printf("finalizou    deallocate_al_list\n");


return 0;
}