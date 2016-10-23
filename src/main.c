#include "definitions/definitions.h"
#include "external/model/hash.h"
#include "helpers/reader.h"

void main(int argc, char **argv) {
    printf("Hello World!!\n\n");



    hashtable_t *hashtable = ht_create(65536);

//	ht_set( hashtable, "key1", "inky" );
//	ht_set( hashtable, "key2", "pinky" );
//	ht_set( hashtable, "key3", "blinky" );
//	ht_set( hashtable, "key4", "floyd" );
//
//	printf( "%s\n", ht_get( hashtable, "key1" ) );
//	printf( "%s\n", ht_get( hashtable, "key2" ) );
//	printf( "%s\n", ht_get( hashtable, "key3" ) );
//	printf( "%s\n", ht_get( hashtable, "key4" ) );


    char* file = "C:\\Users\\arman\\workspace\\c\\P1 - Comp\\src\\definitions\\definitions.h";
    char* source = "C:\\Users\\arman\\workspace\\c\\P1 - Comp\\regression.d";

//    int out = read_definitions(file);
//    if (out!=0){
//        printf("Error reading\n");
//    }

    int out = load_definitions(file, hashtable);
    if (out!=0){
        printf("Error loading\n");
    }

    printf("%s\n", ht_get(hashtable, "NEW"));

    out = read_file(source);
    if (out!=0){
        printf("Error reading source\n");
    }

    exit(0);
}