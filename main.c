#include <stdio.h>

#include "definitions/definitions.h"
#include "external/model/hash.h"

int read_definitions(char *filename){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    printf("Reading %s\n", filename);

    if (fp == NULL) {
        printf("Exiting... \n");
        return -1;
    } else {
        printf("< READING >\n");
        while ((read = getline(&line, &len, fp)) != -1) {
            if (strstr(line, "#define")){
                printf("  %s", line);
            }
        }
        printf("</READING >\n");

        fclose(fp);
        return 0;
    }
}

void main(int argc, char **argv) {
    printf("Hello World!!\n\n");



    hashtable_t *hashtable = ht_create(65536);

	ht_set( hashtable, "key1", "inky" );
	ht_set( hashtable, "key2", "pinky" );
	ht_set( hashtable, "key3", "blinky" );
	ht_set( hashtable, "key4", "floyd" );

	printf( "%s\n", ht_get( hashtable, "key1" ) );
	printf( "%s\n", ht_get( hashtable, "key2" ) );
	printf( "%s\n", ht_get( hashtable, "key3" ) );
	printf( "%s\n", ht_get( hashtable, "key4" ) );

//    int out = read_definitions("definitions/definitions.h");
//    int out = read_definitions("definitions\\definitions.h");
    int out = read_definitions("C:\\Users\\arman\\workspace\\c\\P1 - Comp\\definitions\\definitions.h");
    if (out!=0){
        printf("Error\n");
    }

    exit(0);
}