//./analysis -l HLA-A -d /mnt/hgfs/SHARED/TESTE.txt


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "data_structs.h"
#include "functions.h"


static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ -l <locus[HLA-A/B/C/...]> -d <path_to_file.txt> ]\n", progname);
  exit(1);
}


int main (int argc, char *argv[])
{
	int c;
  //unsigned int l,d = DEF_SIZE;
  char l[10], d[30];
  printf("argc %d\n", argc);
  printf("argv %s\n", argv[0]);
  printf("argv %s\n", argv[1]);
  printf("argv %s\n", argv[2]);
  printf("argv %s\n", argv[3]);
  printf("argv %s\n", argv[4]);


/* =============== TRATAMENTO DE LINHA DE COMANDO =============== */
  char *opts = "ld:";
  c = getopt (argc, argv, opts);
  //printf("%d\n",c);

  while ( c != -1 ) {
    printf("ENTROU");
    switch (c)
    {
      case 'l': 
        printf("%s\n", optarg); break;
      case 'd' : printf("%s\n", optarg); break;
      default:   usage(argv[0]);
    }
    c = getopt (argc, argv, opts);
  }
/* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
return 0;

//printf("%d\n", l);
}
