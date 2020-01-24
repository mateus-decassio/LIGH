#ifndef __DATA_STRUCTS__
#define __DATA_STRUCTS__

typedef struct
{
    char *id;           //guarda o ID (UTR, INTRO, EXON)
    int begin;          //início daquele ID
    int end;            //fim daquele ID
} des;


typedef struct
{
    int begin;
    int end;
} divisions;


typedef struct
{
    divisions *regions; //[VETOR]: guarda as regiões divisórias da sequência do alelo
    unsigned int size;  //guarda o tamanho das divisões para essa sequência
    char *name;         //guarda o nome do alelo
    char *sequence;     //guarda a sequência do alelo
} alleles;


typedef struct
{
    char *id;           //guarda o identificador da amostra
    alleles *allele;    //guarda o vetor de alelos que essa amostra possui. Esse valor só pode ser
                        //1 (homozigoto) ou 2 (heterozigoto)
    bool homozygous;
} sample;


typedef struct
{
    unsigned int number_of_regions;
    unsigned int total_of_samples;
} global;



#endif