#include <stdbool.h>
#include "lexycal_analyzer.h"

typedef enum {VIRGIN, OK, ERROR, ENDED, NUMBER, ALFA, COMMENT, STRING} status_t;
status_t status = VIRGIN;

// Dynamic word
char *word = NULL;
// Size and position of the word
size_t size = 0, pos = 0;
// Depth of the comment
int commdepth = 0;
// Number of identifiers found
int count = 0, id_start = 500;
// If the string is ' or "
char strini;
// If the number has suffix
bool num_suffix = false;

/**
 * Add a char to a dynamic String
 * @param c Char to add
 * @return The string
 */
char * appendChar(char c) {
    char *tmp = NULL;

    /* Check if we need to expand. */
    if (size <= pos) {
        size += 32;
        tmp = realloc(word, size);
        if (!tmp) {
            free(word);
            word = NULL;
        }
        word = tmp;
    }

    /* Actually store the thing. */
    word[pos++] = c;

    return word;
}

/**
 * Function that returns 1 if the char is a delimiter
 * @param c Char
 * @return 1 if is a delimiter 0 otherwise
 */
int isDelimiter(char c) {
    for (int i=0; i < (sizeonechar) ;i++){
        char d = onechar[i][0];
        if (c==d)
            return 1;
    }
    return 0;
}

/**
 * Function that makes an uppercase string
 * @param beg String that we want to be in uppercase
 */
void strupp(char* beg) {
    while (*beg = toupper(*beg)) beg++;
}

/**
 * Function that prints a char (Got from the input system)
 * @param c
 */
void printchar(char c){
    printf(COLOR_MAGENTA);
    if (c=='\n') {
        printf("%s   Char: \'\\n\'\n", VTAG);
    } else if (c=='\r') {
        printf("%s   Char: \'\\r\'\n", VTAG);
    } else {
        printf("%s   Char: \'%c\'\n", VTAG, c);
    }
    printf(COLOR_RESET);
}

/**
 * Reset the word
 */
void resetWord(){
    pos = 0;
    size = 0;
    free(word);
    word = NULL;
}

/**
 * Insert a word in the hash table if it's not already there
 * @return item inserted or item of the table
 */
struct item * getinsert(){
    struct item *aux = ht_get(hashtable, word);
    if (aux == NULL) {
        aux = malloc(sizeof(struct item));
        aux->code = id_start + count;
        count++;
        aux->instance = word;
        if (status != COMMENT) {
            printf(COLOR_GREEN"%s Inserting identifier: \'%s\'\n"COLOR_RESET, VTAG, word);
        } else {
            printf(COLOR_GREEN"%s Inserting identifier: \n\'%s\'\n"COLOR_RESET, VTAG, word);
        }
        ht_set(hashtable, word, aux);
        aux = ht_get(hashtable, word);;
    }
    return aux;
}

/**
 * Process a comment (Any kind of comment)
 *   If it's a documentation comment then it's a lexycal that we want to insert in the hash table
 * @param c First char
 * @return
 */
char process_comment(char c) {
    if (c == '/'){
        char j = getChar(); char k; char l;
        switch (j){
            case '/':
                /*
                 * One line comment:
                 *  - Skip
                 *  - Return next char
                 *  - Word is null
                 */
                status = COMMENT;
                printf("%s    Commented: //", VTAG);
                while ((k = getChar()) != '\n'){
                    printf("%c", k);
                    ;
                }
                printf("\n");
                c = getChar();
                break;
            case '*':
                status = COMMENT;
                l = getChar();
                if (l!='*') {
                    /*
                     * Normal comment:
                     * - Skip
                     * - Return ' ' (because in D you can do int\/**\/a ant it compiles)
                     * - Word is null
                     */
                    printf("%s    Commented:\n/*%c", VTAG, l);
                    while ((k = getChar())) {
                        if (k == '*') {
                            k = getChar();
                            if (k == '/') {
                                break;
                            }
                        } else {
                            printf("%c", k);;
                        }
                    }
                    printf("*/\n");
                    resetWord();
                    c = ' ';
                } else {
                    /*
                     * Documentation comment:
                     * - Skip
                     * - Return ' ' (because of D)
                     * - Word is the commentary itself
                     */
                    printf("%s    Commented (doc):\n/**", VTAG);
                    appendChar('/'); appendChar('*'); appendChar('*');
                    while ((k = getChar())) {
                        appendChar(k);

                        if (k!='\r'){
                            if (k == '*') {
                                k = getChar();
                                if (k == '/') {
                                    break;
                                }
                            } else {
                                printf("%c", k);;
                            }
                        }

                    }
                    printf("*/\n");
                    appendChar('/');
                    c = ' ';
                }
                break;
            case '+':
                commdepth ++;
                status = COMMENT;
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
                resetWord();
                c = ' ';
                break;
            default:
                break;
        }
    }
    return c;
}

/**
 * Process a string
 * @param c
 * @return
 */
int process_string(char c) {
    if (commdepth != 0) {
        // Escape char
        appendChar(c);
        commdepth = 0;
    } else {
        if (c=='\\'){
            appendChar(c);
            commdepth = 1;
        } else if (c==strini) {
            appendChar(c);
            appendChar('\0');
            printf("%s    String:\n'%s'\n",VTAG, word);
            return 0;
        } else {
            appendChar(c);
        }
    }
    return 1;
}

/**
 * Process a number
 * Float suffix: f or F
 * Real suffix: L
 * Imaginary suffix: i
 * @param c
 * @return
 */
int process_number(char c) {
    int ret = 1;
    if (isDelimiter(c) && c!='.' && !((commdepth==3 && (c=='+' || c=='-')))) {
        ret = 0;
    } else {
        switch (commdepth) {
            case 0:
                // No point
                switch (c) {
                    case '0' ... '9':
                        appendChar(c);
                        break;
                    case '.':
                        appendChar(c);
                        commdepth = 1;
                        break;
                    case 'f':
                    case 'F':
                    case 'L':
                    case 'i':
                        appendChar(c);
                        num_suffix = true;
                        break;
                    case 'e':
                    case 'E':
                        printf(COLOR_RED"%s It's an exponential number\n"COLOR_RESET, VTAG);
                        num_suffix = true;
                        appendChar(c);
                        char l = getChar();
                        if (l == '+' || l == '-'){
                            appendChar(l);
                        } else {
                            putChar(l);
                        }
                        commdepth = 3;
                        break;
                    case '_':
                        break;
                    default:
                        if (isDelimiter(c)) {
                            putChar(c);
                        } else {
                            // Error
                            printf(COLOR_RED"-- Error: Number bad formed --\n"COLOR_RESET);
                        }
                        ret = 0;
                        break;
                }
                break;
            case 1:
                // Point already present
                switch (c) {
                    case '0' ... '9':
                        appendChar(c);
                        break;
                    case '_':
                        break;
                    case 'f':
                    case 'F':
                    case 'L':
                    case 'i':
                        if (num_suffix) {
                            // Error
                            ret = 0;
                        } else {
                            num_suffix = true;
                        }
                        break;
                    case 'e':
                    case 'E':
                        printf(COLOR_RED"%s It's an exponential number\n"COLOR_RESET, VTAG);
                        num_suffix = true;
                        appendChar(c);
                        char l = getChar();
                        if (l == '+' || l == '-'){
                            appendChar(l);
                        } else {
                            putChar(l);
                        }
                        commdepth = 3;
                        break;
                    default:
                        if (isDelimiter(c)) {
                            putChar(c);
                        } else {
                            // Error
                            printf(COLOR_RED"-- Error: Number bad formed --\n"COLOR_RESET);
                        }
                        ret = 0;
                        break;
                }
                break;
            case 2:
                // Hexadecimal
                switch (c) {
                    case '0' ... '9':
                        appendChar(c);
                        break;
                    case 'a' ... 'f':
                        appendChar(toupper(c));
                        break;
                    case 'A' ... 'F':
                        appendChar(c);
                        break;
                    case '_':
                        break;
                    default:
                        if (isDelimiter(c)) {
                            putChar(c);
                        } else {
                            // Error
                            printf(COLOR_RED"-- Error: Hexadecimal number bad formed --\n"COLOR_RESET);
                        }
                        ret = 0;
                        break;
                }
                break;
            case 3:
                // Exponential
                if (isdigit(c)){
                    appendChar(c);
                } else {
                    printf(COLOR_RED"-- Error: Exponential number bad formed --\n"COLOR_RESET);
                    ret = 0;
                }
                break;
            case 4:
                // Binary
                if (c=='1' || c=='0'){
                    appendChar(c);
                } else {
                    printf(COLOR_RED"-- Error: Binary number bad formed --\n"COLOR_RESET);
                    ret = 0;
                }
                break;
            default:
                break;
        }
    }
    if (ret == 0){
        appendChar('\0');
        putChar(c);
        printf(COLOR_RED"%s The number is <%s>\n"COLOR_RESET, VTAG, word);
    }
    return ret;
}

/**
 * Reads from the input system until it forms a Lexical component that is returned
 * @return Lexycal component
 */
struct item *next_comp(){
    printf(COLOR_CYAN"%s < Componente Léxico >\n"COLOR_RESET, VTAG);
    struct item *out = NULL;
    while (status!=ERROR && status!=ENDED){
        char c; c = getChar();

        if (status == VIRGIN) {
            c = process_comment(c);
        }
        printchar(c);

        if (status != COMMENT) {
            // No comment
            if (!(c == EOF || isDelimiter(c))) {
                switch (status) {
                    /*
                     * This is the first char of the word so:
                     *  - If is number then it must be a number
                     *  - If it's not a number then it must be a keyword or a identifier
                     *  - If it's a ' or a " then it's a string
                     */
                    case VIRGIN:
                        appendChar(c);
                        commdepth = 0;
                        if (isdigit(c)){
                            status = NUMBER;
                            char l = getChar();
                            switch (l) {
                                case 'x':
                                case 'X':
                                    num_suffix = true;
                                    appendChar(l); printchar(l);
                                    commdepth = 2;
                                    break;
                                case 'b':
                                case 'B':
                                    appendChar(l); printchar(l);
                                    num_suffix = true;
                                    commdepth = 4;
                                    break;
                                default:
                                    num_suffix = false;
                                    putChar(l);
                                    break;
                            }
                            c = getChar(); printchar(c);
                            while (process_number(c)) {
                                c = getChar();
                                printchar(c);
                            }
                        } else {
                            if (c=='"' || c=='\''){
                                strini = c;
                                status = STRING;
                                while (process_string(c)) {
                                    c = getChar();
                                    printchar(c);
                                }
                            } else {
                                status = ALFA;
                            }
                        }
                        break;
                    case ALFA:
                        appendChar(c);
                        break;
                    default:
                        printf(COLOR_RED"-- Error: Status deprecated --"COLOR_RESET);
                        break;
                }
            } else {
                switch (status) {
                    default:
                        // Lexycal component
                        if (word != NULL) {
                            // Word to uppercase
                            appendChar('\0');
                            strupp(word);
                            // Return char to input system
                            putChar(c);
                            printf("%s End word: \'%s\'\n", VTAG, word);

                            out = getinsert();
                            status = ENDED;
                        } else {
                            if (c != '\r') {
                                if (c != ' ' && c != '\n') {
                                    // Build symbol string
                                    word = malloc(2 * sizeof(char));
                                    word[0] = c;
                                    word[1] = '\0';

                                    printf("%s Ending symbol: \'%s\'\n", VTAG, word);

                                    out = getinsert();
                                    status = ENDED;
                                } else {
                                    continue;
                                }
                            }
                        }
                        break;
                    case NUMBER: case STRING:
                        out = malloc(sizeof(struct item));
                        out->code = 65535;
                        out->instance = strdup(word);
                        status = ENDED;
                        putChar(c);
                        break;
                }
            }
        } else {
            putChar(c);
            // Comment
            if (word != NULL){
                // Documentation comment (Lexical component)
                out = getinsert();
                status = ENDED;
            } else {
                status = VIRGIN;
            }
        }
    }
    printf(COLOR_CYAN"%s </Componente Léxico >\n"COLOR_RESET, VTAG);

    resetWord();
    if (status==ERROR){
        status = VIRGIN;
        return NULL;
    }
    status = VIRGIN;
    return out;

}