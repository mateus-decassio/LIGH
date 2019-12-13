#ifndef __FUNCTIONS__
#define __FUNCTIONS__

void read_file(char *file_path, des *description, sample *samples);

void insert_description(des *description, unsigned int pos, char *id, int begin, int end);

void allocate_alleles(sample *samples, unsigned int pos, unsigned int size);

void allocate_region(sample *samples, unsigned int pos, unsigned int al, unsigned int size);

void insert_region(sample *samples, unsigned int pos, unsigned int al, unsigned int posic, int begin, int end);

void insert_allele(sample *samples, unsigned int pos, unsigned int al, char *id, char *name, char *sequence);



#endif
