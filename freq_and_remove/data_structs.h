#ifndef __DATA_STRUCTS__
#define __DATA_STRUCTS__

typedef struct
{
    int begin;              //início daquele ID
    int end;                //fim daquele ID
    char *id;               //guarda o ID (UTR, INTRO, EXON)
} des;


typedef struct
{
    int begin;
    int end;
} divisions;


typedef struct
{
    unsigned int size;      //guarda o tamanho das divisões para essa sequência
    char *name;             //guarda o nome do alelo
    char *sequence;         //guarda a sequência do alelo
    divisions *regions;     //[VETOR]: guarda as regiões divisórias da sequência do alelo
    
} __attribute__((packed, aligned(1))) alleles;


typedef struct
{
    int valid;              //0-VÁLIDO   1-INVÁLIDO por sequência não contígua   2 - INVÁLIDO por não ter todos os íntrons
    bool homozygous;
    char *id;               //guarda o identificador da amostra
    alleles *allele;        //guarda o vetor de alelos que essa amostra possui. Esse valor só pode ser
                            //1 (homozigoto) ou 2 (heterozigoto)
} __attribute__((packed, aligned(1))) sample;


typedef struct
{
    unsigned int number_of_regions;
    unsigned int total_of_samples;
    unsigned int total_of_alleles;
} global;


//-------------------------------------------------------------------------------------------------

typedef struct al_node
{
    int counter;            //guarda o contador de vezes que aquele alelo aparece
	struct al_node *next;   //ponteiro para o próximo elemento da lista
    char *allele;           //guarda o nome do alelo no nó
    int *alleles_used;      //vetor que guarda a quantidade de alelos que foram utilizados para cada intron do locus da amostra
} __attribute__((packed, aligned(1))) al_node;

typedef struct al_list
{
    int size;
    struct al_node *head;
    struct al_node *tail;
} __attribute__((packed, aligned(1))) al_list;

//-------------------------------------------------------------------------------------------------

typedef struct i_node
{
	short int id;           //guarda o valor de qual intron aquele nó esta quardando(1,2,3,4,...)
    struct i_node *next;    //ponteiro para o próximo elemento da lista
    char *sequence;         //guarda a sequência recortada do íntron da sequência maior
    al_list *list;          //lista de alelos encontrados para aquela sequência naquele nó 
} __attribute__((packed, aligned(1))) i_node;


typedef struct i_list
{
    int size;
	struct i_node *head;      //cabeça da lista
	struct i_node *tail;      //cauda da lista
    struct i_node *point;     //ponteiro apontando para a cauda parcial (a busca por diferentes regiões de íntrons (1,2,3,...) para comparar o resultado é feita a partir dele)
} __attribute__((packed, aligned(1))) i_list;

#endif