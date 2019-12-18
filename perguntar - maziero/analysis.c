//./analysis -l HLA-A -d /mnt/hgfs/SHARED/TESTE.txt
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
  char *locus, *archive  = NULL;

  //ARRUMAR ISSO AQUI
  des *description;
  sample *samples;
  global *parameters = (global *) malloc (sizeof(global));





/* ====================== TRATAMENTO DE LINHA DE COMANDO ====================== */
  if ( argc < 5 )
    usage(argv[0]);
  //l:d: - o uso do : significa que l recebe um parâmetro adicional, assim como o d
  while ( (opt = getopt (argc, argv, "l:d:")) != -1 )
  {
    switch (opt)
    {
      case 'l':
        locus = optarg;
        break;

      case 'd':
        archive = optarg;
        break;

      case ':':
        printf("essa opção precisa de um valor!\n");
        break;

      case '?':
        printf("opção desconhecida: %c\n", optopt);
        break;

      default:
        usage(argv[0]);
    }
  }
/* ====================== FIM DO TRATAMENTO DE LINHA DE COMANDO ====================== */
  printf("LOCUS = %s\n", locus);
  printf("PATH TO FILE = %s\n", archive);


  read_file(parameters, archive, description, samples);
  
  
  printf("\n\n\n\n");
  printf("TOTAL OF SAMPLES = %d\n", parameters->total_of_samples);
  //printf("ID = %s\n", samples[0].id);

  if (samples == NULL)
    printf ("NULL\n");
  else
    printf("ANTES = %p\n", &samples);

  printf("ID = %s\n", samples[0].id);

/*
  analysis();
  results();
*/
return 0;
}