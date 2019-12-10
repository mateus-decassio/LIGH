#ifndef __FUNCTIONS__
#define __FUNCTIONS__

void read_file(char *file_path, des *description, sample *samples);

void insert_description(des *description, unsigned int pos, char *id, int begin, int end);

#endif
