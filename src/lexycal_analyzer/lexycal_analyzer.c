//
// Created by Snooze on 24/10/2016.
//

#include "lexycal_analyzer.h"

typedef enum {VIRGIN, OK, ERROR, ENDED} status_t;
status_t status = VIRGIN;

char *word = NULL;
int pos = 0;

int isDelimiter(char c) {
    switch (c) {
        // Llaves
        case '[':
        case ']':
        case '{':
        case '}':
        case '(':
        case ')':
        case '<':
        case '>':
        // Finales
        case ';':
        case ' ':
        case EOF:
        // Operadores
        case '+':
        case '-':
        case '*':
        case '=':
        // Miscellanéa
        case '.':
            return 1;
        default:
            return 0;
    }
}

void strupp(char* beg) {
    while (*beg = toupper(*beg)) beg++;
}

struct item *next_comp(){
    printf("%s Next Component Called\n", VTAG);
    while (status!=ERROR) {
        struct item *out = NULL;
        char c;

        c = getChar();
        printf("%s   Char: %c\n", VTAG, c);

        if (!(c == EOF || isDelimiter(c))) {
            switch (status) {
                case VIRGIN:
                    word = malloc(256 * sizeof(char));
                    word[0] = c;
                    status = OK;
                    pos=1;
                    break;
                case OK:
                    word[pos] = c;
                    pos++;
                    break;
                case ERROR:
                    break;
                case ENDED:
                    word[pos] = c;
                    pos++;
                    break;
                default:
                    break;
            }
        } else {
            if (status!=VIRGIN) {
                word[pos] = '\0'; strupp(word);
                pos = 0; status = VIRGIN;
                putChar(c);
                printf("%s Ended word: %s\n", VTAG, word);
                struct item *aux = ht_get(hashtable, word);
                if (aux != NULL)
                    out = aux;
            } else {
                word = malloc(2 * sizeof(char));
                word[0]=c; word[1]='\0';
                struct item *aux = ht_get(hashtable, word);
                if (aux != NULL)
                    out = aux;
            }
            free(word);
            return out;
        }
    }
    if (status==ERROR){
        return NULL;
    }
}