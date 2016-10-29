#include "config.h"

/**
 * This represents special chars, it'll be insertated at the end of the hash table
 */
char * onechar[] = {
        // Puntuation
        ".",",",
        // Brackets
        "[","]","{","}","(",")","<",">",
        // Operators
        "+","-","*","=",
        // Endings
        " ",";", "\n","\r",
        // Comments
        "/"
};

int sizeonechar = 19;