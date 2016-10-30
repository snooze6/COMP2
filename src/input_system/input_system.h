#ifndef P1_COMP_INPUT_SYSTEM_H
#define P1_COMP_INPUT_SYSTEM_H

#include <stdio.h>
#include "../config.h"

int setFile(char *filename);
int getLine();
int getCol();
char getChar();
char putChar(char c);
void closeFile();


#endif //P1_COMP_INPUT_SYSTEM_H
