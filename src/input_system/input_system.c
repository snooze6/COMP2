#include "input_system.h"

FILE *working_file = NULL;
char c = '\0';
int actual_line = 1;
int actual_col = 0;

// Blocks
char *bA, *bB, *aux;
// Pointers
int forward;

size_t _TAM_MAX_LEXEMA = 255;

/**
 * Set file to read
 * @param filename that we want to read
 * @return 0 if exists and can be opened, -1 otherwise
 */
int setFile(char *filename){
    working_file = fopen(filename, "r");
//    printf("Reading %s\n", filename);

    if (working_file == NULL) {
        return -1;
    } else {
        {
            // Alloc memory
            bA = (char *) malloc(_TAM_MAX_LEXEMA + 1 * sizeof(char)); //reservamos para n chars + EOF
            bB = (char *) malloc(_TAM_MAX_LEXEMA + 1 * sizeof(char)); //reservamos para n chars + EOF
            forward = 0;

            // Load first block
            int num_leidos = (int) fread(bA, sizeof(char), _TAM_MAX_LEXEMA, working_file);
            // Fread did not read EOF
            bA[num_leidos] = EOF; //indicamos final bloque
        }
        return 0;
    }
}

/**
 * Get the line that is being read
 * @return number of line
 */
int getLine(){
    return actual_line;
}

/**
 * Get the column that is being read
 * @return number of column
 */
int getCol(){
    return actual_col;
}

/**
 * Get the char
 * @return The char
 */
char getChar(){
    if (working_file != NULL) {
        if (c != '\0'){
            char j = c;
            c = '\0';
            return j;
        } else {
            char k = bA[forward];

            if (k == EOF) {
                if (forward == (_TAM_MAX_LEXEMA)) {
                    int num_leidos = (int) fread(bA, sizeof (char), _TAM_MAX_LEXEMA, working_file);
                    bA[num_leidos] = EOF;
                    forward = 0;
                    k = bA[forward];

                } else {
                    return k;
                }
            }
            forward++;

            char j = k;
//            char j = (char) getc(working_file);
            if (j=='\n'){
                actual_line++;
                actual_col = 0;
            } else {
                actual_col++;
            }
            return j;
        }
    } else {
        return EOF;
    }
}

/**
 * Return a char to read it later
 * @param a Char that we want to return
 * @return the same char that we pass
 */
char putChar(char a){
    c = a;
    if (config_verbose) {
        if (c == '\n') {
            printf("%s     Returning char \'\\n\'\n", VTAG);
        } else if (c == '\r') {
            printf("%s     Returning char \'\\r\'\n", VTAG);
        } else if (c==EOF){
            printf("%s     Returning char \'EOF\'\n", VTAG);
        } else {
            printf("%s     Returning char \'%c\'\n", VTAG, a);
        }
    }
    return c;
}

/**
 * Close the file; save memory
 */
void closeFile(){
    fclose(working_file);
    working_file = NULL;
}