#ifndef __FUNCTIONS__
#define __FUNCTIONS__

/* ======================= FUNÇÕES/PROCEDIMENTOS PARA ALOCAÇÃO / DESALOCAÇÃO ======================= */

sample* allocate_samp(unsigned int size);

void allocate_alleles(sample *samples, unsigned int pos, unsigned int size);

void allocate_region(sample *samples, unsigned int pos, unsigned int al, unsigned int size);

void deallocate_regions(divisions *regions);

void deallocate_alleles(alleles *allele);

void deallocate_sample(sample *samples);

void deallocate_global(global *parameters);

void deallocate_al_list(al_list *L);

void deallocate_ie_list(ie_list *L);


/* ================================================================================================= */


/* ====================== FUNÇÕES/PROCEDIMENTOS PARA IMPRESSÃO DOS RESULTADOS ====================== */

void impressao_s(sample *samples, unsigned int size);
/* ================================================================================================= */


/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A LEITURA ========================== */

void insert_region(sample *samples, unsigned int pos, unsigned int al, unsigned int posic, int begin, int end);

void insert_allele(sample *samples, unsigned int pos, unsigned int al, char *id, char *name, char *sequence, int begining);

void read_parameters(global *parameters, char *file_path);

void read_file(char *file_path, sample *samples, global *parameters);
/* ================================================================================================= */


/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR A ANÁLISE ========================== */
int calculate_sub(int a, int b);

char *extrac_intron(char *source, int stride, int offset);

int verify_region(int i_begin, int i_end, unsigned int size, divisions *regions);

void analysis_freq_intron(global *parameters, sample *samples, ie_list *L);

void analysis_freq_exon(global *parameters, sample *samples, ie_list *L);

void analysis_freq_allele(global *parameters, sample *samples, al_list *L, int intron_counter, int N_REGIONS);

void decrement(al_node *node, int posic);

void remove_samples(global *parameters, sample *samples, int counter);


/* ================================================================================================= */


/* ========================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR AS LISTAS ========================== */
void initialize_ie_list(ie_list *L);

void initialize_al_list(al_list *L);

void initialize_vector_al_list(al_list *L, int intron_counter);

ie_node *create_ie_Node(char *sequence, short int id);

al_node *create_al_Node(char *allele);

void insert_intron(ie_list *L, char *sequence, char *allele, short int id, bool homozygous);

void insert_allele_in_node(al_list *L, char *allele, bool homozygous);

ie_node *search_intron(ie_list *L, char *sequence, short int id);

al_node *search_allele(al_list *L, char *allele);
/* ================================================================================================= */


/* ======================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR OS RESULTADOS ======================== */
void impressao_r(ie_list *L);

void results_many_files_i(char *locus, char *path, ie_list *L);

void results_one_file_i(char *locus, char *path, ie_list *L);

void results_many_files_e(char *locus, char *path, ie_list *L);

void results_one_file_e(char *locus, char *path, ie_list *L);

void results_statistics(global *parameters, char *locus, char *path, al_list *L);

void results_rejected_list(global *parameters, sample *samples, char *locus, char *p, int N_REGIONS);

void results_used_table(al_list *L, int intron_counter, char *locus, char *p);

/* ================================================================================================= */


#endif
