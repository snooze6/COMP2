
#include "external/model/hash.h"
#include "external/model/list.h"
#include "helpers/reader.h"
#include "input_system/input_system.h"
#include "config.h"
#include "lexycal_analyzer/lexycal_analyzer.h"

int main(int argc, char **argv) {
    printf(COLOR_MAGENTA"D Lexical_Analyzer v0.1\n"COLOR_RESET);
    if( argc == 3 ) {
        hashtable = ht_create(65536);

        char* file = argv[1];
        char* source_path = argv[2];

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
        printf(COLOR_MAGENTA"< Lexycal Analyzer >\n"COLOR_RESET);
        while((a = next_comp())!=NULL){
            if (strstr(a->instance,"\n")){
                printf("%s ------------------------- Componente: \n\'%s\' - %d\n",VTAG , a->instance, a->code);
            } else {
                printf("%s ------------------------- Componente: \'%s\' - %d\n",VTAG , a->instance, a->code);
            }
//        getchar();
//        exit(0);
        }
        printf(COLOR_MAGENTA"</Lexycal Analyzer >\n\n"COLOR_RESET);

        ht_print(hashtable);
        printf("\n");
        ht_print_identifiers(hashtable);

        closeFile();
        ht_free(hashtable);

    } else {
        printf(COLOR_RED ETAG" Two arguments expected.\n");
        printf("    + Usage ./program <definitions.h> <source.d>"COLOR_RESET);
    }

    return 0;
}