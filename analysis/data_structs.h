#ifndef __DATA_STRUCTS__
#define __DATA_STRUCTS__

typedef struct
{
    char *id;               //guarda o ID (UTR, INTRO, EXON)
    int begin;              //início daquele ID
    int end;                //fim daquele ID
} des;


typedef struct
{
    int begin;
    int end;
} divisions;


typedef struct
{
    divisions *regions;     //[VETOR]: guarda as regiões divisórias da sequência do alelo
    unsigned int size;      //guarda o tamanho das divisões para essa sequência
    char *name;             //guarda o nome do alelo
    char *sequence;         //guarda a sequência do alelo
} alleles;


typedef struct
{
    char *id;               //guarda o identificador da amostra
    alleles *allele;        //guarda o vetor de alelos que essa amostra possui. Esse valor só pode ser
                            //1 (homozigoto) ou 2 (heterozigoto)
    bool homozygous;
} sample;


typedef struct
{
    unsigned int number_of_regions;
    unsigned int total_of_samples;
} global;


typedef struct
{
	short int id;           //guarda o valor de qual intron aquele nó esta quardando(1,2,3,4,...)
    char *sequence;         //guarda a sequência recortada do íntron da sequência maior
	struct node *next;      //ponteiro para o próximo elemento da lista
} node;


typedef struct
{
    int size;
	struct node *head;      //cabeça da lista
	struct node *tail;      //cauda da lista
    struct node *point;     //ponteiro apontando para a cauda parcial (a busca por diferentes regiões de íntrons (1,2,3,...) para comparar o resultado é feita a partir dele)
} i_list;



#endif