#ifndef __FUNCTIONS__
#define __FUNCTIONS__

/* ======================= FUNÇÕES/PROCEDIMENTOS PARA ALOCAÇÃO / DESALOCAÇÃO ======================= */
des* allocate_desc(unsigned int size);

sample* allocate_samp(unsigned int size);

void allocate_alleles(sample *samples, unsigned int pos, unsigned int size);

void allocate_region(sample *samples, unsigned int pos, unsigned int al, unsigned int size);
/* ================================================================================================= */


/* ====================== FUNÇÕES/PROCEDIMENTOS PARA IMPRESSÃO DOS RESULTADOS ====================== */
void impressao_d(des *description, unsigned int size);

void impressao_s(sample *samples, unsigned int size);
/* ================================================================================================= */


/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A LEITURA ========================== */
void insert_description(des *description, unsigned int pos, char *id, int begin, int end);

void insert_region(sample *samples, unsigned int pos, unsigned int al, unsigned int posic, int begin, int end);

void insert_allele(sample *samples, unsigned int pos, unsigned int al, char *id, char *name, char *sequence);

void read_parameters(global *parameters, char *file_path);

void read_file(char *file_path, des *description, sample *samples);
/* ================================================================================================= */


/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A ANÁLISE ========================== */
int calculate_sub(int a, int b);

char *extrac_intron(char *source, int stride, int offset);

int verify_region(int i_begin, int i_end, unsigned int size, divisions *regions);

int analysis_freq_intron(global *parameters, des *description, sample *samples, i_list *L);

void analysis_freq_allele(global *parameters, des *description, sample *samples, al_list *L, int intron_counter);

void decrement(al_node *node, int posic);

/* ================================================================================================= */


/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR AS LISTAS ========================== */
void initialize_i_list(i_list *L);

void initialize_al_list(al_list *L);

void initialize_vector_al_list(al_list *L, int intron_counter);

i_node *create_i_Node(char *sequence, short int id);

al_node *create_al_Node(char *allele);

void insert_intron(i_list *L, char *sequence, char *allele, short int id, bool homozygous);

void insert_allele_in_node(al_list *L, char *allele, bool homozygous);

i_node *search_intron(i_list *L, char *sequence, short int id);

al_node *search_allele(al_list *L, char *allele);
/* ================================================================================================= */


/* ======================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR OS RESULTADOS ======================== */
void impressao_r(i_list *L);

void results_many_files(char *locus, char *path, i_list *L);

void results_one_file(char *locus, char *path, i_list *L);

void results_statistics(global *parameters, char *locus, char *path, al_list *L);

void results_rejected_list(global *parameters, des *description, sample *samples, char *locus, char *p);

void results_rejected_table(al_list *L, int intron_counter, char *locus, char *p);

/* ================================================================================================= */


#endif
