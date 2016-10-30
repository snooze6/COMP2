#ifndef P1_COMP_READER_H
#define P1_COMP_READER_H

#include <stdio.h>
#include "../external/model/hash.h"
#include <memory.h>
#include "../config.h"

int read_definitions(char *filename);
int load_definitions(char *filename, hashtable_t* table);
int read_file(char *filename);


#endif //P1_COMP_READER_H
