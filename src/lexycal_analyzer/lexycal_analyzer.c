//
// Created by Snooze on 24/10/2016.
//

#include "lexycal_analyzer.h"

typedef enum {VIRGIN, OK, ERROR, ENDED, NUMBER, ALFA} status_t;
status_t status = VIRGIN;

char *word = NULL;
int pos = 0;
int count = 0;

int isDelimiter(char c) {
    for (int i=0; i < (sizeonechar-1) ;i++){
        char d = onechar[i][0];
        if (c==d)
            return 1;
    }
    return 0;
}

void strupp(char* beg) {
    while (*beg = toupper(*beg)) beg++;
}

struct item *next_comp(){
    printf("%s < Componente Léxico >\n", VTAG);
    struct item *out = NULL;
    while ((status!=ERROR && status!=ENDED)){
        char c;

        c = getChar();
        if (c=='\n') {
            printf("%s   Char: \'\\n\'\n", VTAG);
        } else if (c=='\r') {
            printf("%s   Char: \'\\r\'\n", VTAG);
        } else {
            printf("%s   Char: \'%c\'\n", VTAG, c);
        }

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
                default:
                    break;
            }
        } else {
            if (word!=NULL) {
                word[pos] = '\0'; strupp(word);
                pos = 0; status = VIRGIN;
                putChar(c);
                struct item *aux = ht_get(hashtable, word);
                printf("%s End word: \'%s\'\n", VTAG, word);
                if (aux != NULL) {
                    out = aux;
                } else {
                    aux = malloc(sizeof(struct item));
                    aux->code = 500 + count;
                    count++;
                    aux->instance = word;
                    printf("%s Inserting identifier: \'%s\'\n", VTAG, word);
                    ht_set(hashtable, word, aux);
                    out = ht_get(hashtable, word);;
                }
                status = ENDED;
            } else {
                if (c!='\r') {
                    word = malloc(2 * sizeof(char));
                    word[0] = c;
                    word[1] = '\0';
                    printf("%s Ending symbol: \'%s\'\n", VTAG, word);
                    struct item *aux = ht_get(hashtable, word);
                    if (aux != NULL)
                        out = aux;
                    status = VIRGIN;
                    printf("%s </Componente Léxico >\n", VTAG);
                    return out;
                } else {
                    status = VIRGIN;
                }

            }
            free(word);
            word = NULL;
        }
    }
    printf("%s </Componente Léxico >\n", VTAG);

    if (status==ERROR){
        return NULL;
    }
    status = VIRGIN;
    return out;

}