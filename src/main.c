
#include "external/model/hash.h"
#include "helpers/reader.h"
#include "input_system/input_system.h"
#include "config.h"

int main(int argc, char **argv) {
    printf("D Lexical_Analyzer v0.1\n");

    hashtable_t *hashtable = ht_create(65536);

    char* file = "C:\\Users\\armando\\workspace\\c\\COMP1\\src\\definitions\\definitions.h";
    char* source_path = "C:\\Users\\armando\\workspace\\c\\COMP1\\regression.d";

    int out = load_definitions(file, hashtable);
    if (out!=0){
        printf("%s Error loading definitions\n", ETAG);
        return -1;
    }

    setFile(source_path); char c;

    while((c = getChar()) != EOF){
        printf("%c", c);
    }
    closeFile();

    return 0;
}