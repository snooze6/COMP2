//
// Created by arman on 18/10/2016.
//

#include "reader.h"

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
            if (strstr(line, "#define D_")){
                printf("  %s", line);
            }
        }
        printf("</READING >\n");

        fclose(fp);
        return 0;
    }
}

int load_definitions(char *filename, hashtable_t* table){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    printf("Loading %s\n", filename);

    if (fp == NULL) {
        printf("Exiting... \n");
        return -1;
    } else {
        printf("< LOADING >\n");
        while ((read = getline(&line, &len, fp)) != -1) {
            if (strstr(line, "#define D_")){
                char *tmp;
                strcpy(tmp, line);
                char *ch = strtok(tmp, " ");
                      ch = strtok(NULL, " ");

                // El +2 elimina el D_
                printf("  %s\n", ch+2);
                ht_set(table, ch+2, ch+2);
            }
        }
        printf("</LOADING >\n");

        fclose(fp);
        return 0;
    }
}

int read_file(char *filename){
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
        printf("< READING SOURCE>\n");
        while ((read = getline(&line, &len, fp)) != -1) {
            printf("  %s\n", line);
        }
        printf("</READING SOURCE>\n");

        fclose(fp);
        return 0;
    }
}