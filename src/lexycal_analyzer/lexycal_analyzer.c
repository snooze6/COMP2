//
// Created by Snooze on 24/10/2016.
//

#include "lexycal_analyzer.h"

typedef enum {VIRGIN, OK, ERROR, ENDED, NUMBER, ALFA, COMMENT} status_t;
status_t status = VIRGIN;

char *word = NULL;
int pos = 0;
int commdepth = 0;
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

void printchar(char c){
    if (c=='\n') {
        printf("%s   Char: \'\\n\'\n", VTAG);
    } else if (c=='\r') {
        printf("%s   Char: \'\\r\'\n", VTAG);
    } else {
        printf("%s   Char: \'%c\'\n", VTAG, c);
    }
}

void reset(){
    pos = 0;
    free(word);
    word = NULL;
}

struct item * getinsert(){
    struct item *aux = ht_get(hashtable, word);
    if (aux == NULL) {
        aux = malloc(sizeof(struct item));
        aux->code = 500 + count;
        count++;
        aux->instance = word;
        printf("%s Inserting identifier: \'%s\'\n", VTAG, word);
        ht_set(hashtable, word, aux);
        aux = ht_get(hashtable, word);;
    }
    return aux;
}

char process_comment(char c) {
    if (c == '/'){
        char j = getChar(); char k; char l;
        switch (j){
            case '/':
                printf("%s    Commented: //", VTAG);
                while ((k = getChar()) != '\n'){
                    printf("%c", k);
                    ;
                }
                printf("\n");
                c = getChar();
                break;
            case '*':
                printf("%s    Commented:\n /*", VTAG);
                while ((k = getChar())){
                    if (k == '*'){
                        k = getChar();
                        if (k=='/'){
                            break;
                        }
                    } else {
                        printf("%c", k);
                        ;
                    }
                }
                printf("*/\n");
                c = ' ';
                break;
            case '+':
                commdepth ++;
                printf("%s    Commented:\n/+",VTAG);
                while (commdepth!=0){
                    k = getChar();
                    printf("%c", k);
                    if (k=='/'){
                        l = getChar();
                        printf("%c", l);
                        if (l=='+'){
                            commdepth++;
                        }
                    }
                    if (k=='+'){
                        l = getChar();
                        printf("%c", l);
                        if (l=='/'){
                            commdepth--;
                        }
                    }
                }
                printf("\n");
                c = ' ';
                break;
            default:
                break;
        }
    }
    return c;
}

struct item *next_comp(){
    printf("%s < Componente Léxico >\n", VTAG);
    struct item *out = NULL;
    while ((status!=ERROR && status!=ENDED)){
        char c; c = getChar();

        c = process_comment(c);
        printchar(c);

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
            // Si hay una palabra entonces ese es el componente léxico
            if (word != NULL) {
                // Acabamos la palabra y la ponemos en UPPERCASE
                word[pos] = '\0';
                strupp(word);
                status = ENDED;
                // Devolvemos el caracter al sistema de entrada
                putChar(c);
                printf("%s End word: \'%s\'\n", VTAG, word);

                out = getinsert();
            } else {
                status = VIRGIN;
                if (c != '\r') {
                    // Construir palabra
                    word = malloc(2 * sizeof(char));
                    word[0] = c; word[1] = '\0';

                    if (c != '\n') {
                        printf("%s Ending symbol: \'%s\'\n", VTAG, word);
                    } else {
                        printf("%s Ending symbol: \'%s\'\n", VTAG, "\\n");
                    }

                    out = getinsert();

                    printf("%s </Componente Léxico >\n", VTAG);
                    reset(); return out;
                }
            }
            reset();
        }
    }
    printf("%s </Componente Léxico >\n", VTAG);

    if (status==ERROR){
        return NULL;
    }
    status = VIRGIN;
    return out;

}