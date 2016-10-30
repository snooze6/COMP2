
#include "external/model/hash.h"
#include "helpers/reader.h"
#include "input_system/input_system.h"
#include "config.h"
#include "lexycal_analyzer/lexycal_analyzer.h"

int main(int argc, char **argv) {
    printf(COLOR_MAGENTA"D Lexical_Analyzer v0.1\n"COLOR_RESET);

    hashtable = ht_create(65536);

//    char* file = "C:\\Users\\armando\\workspace\\c\\COMP1\\src\\definitions\\definitions.h";
//    char* source_path = "C:\\Users\\armando\\workspace\\c\\COMP1\\regression.d";
    char* file = "C:\\Users\\arman\\workspace\\c\\P1 - COMP\\src\\definitions\\definitions.h";
    char* source_path = "C:\\Users\\arman\\workspace\\c\\P1 - Comp\\regression.d";

    int out = load_definitions(file, hashtable);
    if (out!=0){
        printf(COLOR_RED"%s Error loading definitions\n"COLOR_RESET, ETAG);
        return -1;
    }

    setFile(source_path); char c;

//    while((c = getChar()) != EOF){
//        printf("%c", c);
//    }

    struct item * a;
    while((a = next_comp())!=NULL){
        if (strstr(a->instance,"\n")){
            printf("%s ------------------------- Componente: \n\'%s\' - %d\n",VTAG , a->instance, a->code);
        } else {
            printf("%s ------------------------- Componente: \'%s\' - %d\n",VTAG , a->instance, a->code);
        }
//        getchar();
//        exit(0);
    }

    closeFile();

    return 0;
}