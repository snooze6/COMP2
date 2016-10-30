#include "config.h"

/**
 * This represents special chars, it'll be insertated at the end of the hash table
 */
char * onechar[] = {
        // Puntuation
        ".",",",
        // Brackets
        "[","]","{","}","(",")",
        // Operators
        "+","-","*","=","!","~","&","|","<",">","%","^"
        // Endings
        " ",";", "\n","\r"," ",
        // Comments
        "/"
};
char * operators[] = {
    // Operators
    "+","-","*","=","!","~","&","|","<",">","%","^","/"
};

int sizeonechar = 26;
int sizeoperators = 13;
bool config_verbose = false;
int config_errors = 0;