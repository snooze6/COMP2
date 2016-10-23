//
// Created by Snooze on 24/10/2016.
//

#include "input_system.h"

FILE *working_file = NULL;

int setFile(char *filename){
    working_file = fopen(filename, "r");
    printf("Reading %s\n", filename);

    if (working_file == NULL) {
        return -1;
    } else {
        return 0;
    }
}

char getChar(){
    if (working_file != NULL) {
        return (char) getc(working_file);
    } else {
        return EOF;
    }
}

char putChar(char c){
    return c;
}

void closeFile(){
    fclose(working_file);
    working_file = NULL;
}