// ./analysis -l HLA-A -d /mnt/hgfs/SHARED/HLA-A.txt -k intron -r /mnt/hgfs/SHARED 2> not_contigous[HLA-A].txt
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
	int opt;
  char *locus, *archive, *path, *type_analysis  = NULL;

  sample *samples;
  global *parameters = (global *) malloc (sizeof(global));
  al_list *allele_list = (al_list *) malloc (sizeof(al_list));




/* ====================== TRATAMENTO DE LINHA DE COMANDO ====================== */
  if ( argc < 9 )
    usage(argv[0]);
  //l:d: - o uso do : significa que l recebe um parâmetro adicional, assim como o d
  while ( (opt = getopt (argc, argv, "l:d:r:k:")) != -1 )
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

      case 'k':
        type_analysis = optarg;
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
  printf("type_analysis = %s\n", type_analysis);

  read_parameters(parameters, archive);

  samples = allocate_samp(parameters->total_of_samples);
  
  if (samples)
  {
    read_file(archive, samples, parameters);
  }
  else
  {
    fprintf(stderr, "Impossível realizar a leitura do arquivo. Houve um problema na alocação da estrutura de dados!");
    exit (-1);
  }


  printf("TOTAL OF SAMPLES = %d\n", parameters->total_of_samples);
  printf("TOTAL OF ALLELES = %d\n", parameters->total_of_alleles);
  printf("\n\n");

  
  //IMPRESSÃO DA LISTA DE AMOSTRAS ENCONTRADAS
  //impressao_s(samples, parameters->total_of_samples);


  
  //ANÁLISE de INTRON
  if (!strcmp(type_analysis, "intron"))
  {
    ie_list *intron_list = (ie_list *) malloc (sizeof(ie_list));
    initialize_ie_list(intron_list);
    analysis_freq_intron(parameters, samples, intron_list);
    //analysis_freq_allele(parameters, description, samples, allele_list, intron_counter);


    printf("\nTHE LOCUS %s HAS %d INTRONS IN THE DNA SEQUENCE.\n", locus, parameters->N_REGIONS);
    printf("\nNUMBER OF INTRONS FOUNDED (all locus included) = %d\n", intron_list->size);
    printf("\nSAVING LOCATION = %s/RESULTS/%s\n", path, locus);

    //IMPRESSÃO DO RESULTADO
    //impressao_r(intron_list);
    
    results_many_files_i(locus, path, intron_list);
    results_one_file_i(locus, path, intron_list);
    results_statistics(parameters, locus, path, allele_list);

  }
  else
  {
    ie_list *exon_list = (ie_list *) malloc (sizeof(ie_list));
    initialize_ie_list(exon_list);
    analysis_freq_exon(parameters, samples, exon_list);


    printf("\nTHE LOCUS %s HAS %d EXONS IN THE DNA SEQUENCE.\n", locus, parameters->N_REGIONS);
    printf("\nNUMBER OF EXONS FOUNDED (all locus included) = %d\n", exon_list->size);
    printf("\nSAVING LOCATION = %s/RESULTS/%s\n", path, locus);

    //IMPRESSÃO DO RESULTADO
    //impressao_r(exon_list);

    results_many_files_e(locus, path, exon_list);
    results_one_file_e(locus, path, exon_list);

  }
  






  deallocate_sample(samples);
  //printf("finalizou    deallocate_sample\n");
  
  deallocate_global(parameters);
  //printf("finalizou    deallocate_global\n");


return 0;
}