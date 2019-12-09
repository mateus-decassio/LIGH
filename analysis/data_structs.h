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
    char *id;           //guarda o identificador da amostra
    
    divisions *div1;    //[VETOR]: guarda as regiões divisórias da sequência do alelo
    char *allele1;      //gaurda o nome do alelo 1
    char *sequence_a1;  //guarda a sequência do alelo 1

    divisions *div2;    //[VETOR]: guarda as regiões divisórias da sequência do alelo
    char *allele2;      //gaurda o nome do alelo 2
    char *sequence_a2;  //guarda a sequência do alelo 2
} sample;




#endif
