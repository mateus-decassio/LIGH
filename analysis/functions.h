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
int verify_region(int i_begin, int i_end, unsigned int size, divisions *regions);

void analysis(global *parameters, des *description, sample *samples);


/* ================================================================================================= */


/* ======================== FUNÇÕES/PROCEDIMENTOS PARA TRATAR OS RESULTADOS ======================== */
void results();

/* ================================================================================================= */


#endif
