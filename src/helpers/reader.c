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
    int max;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        return -1;
    } else {
        while ((read = getline(&line, &len, fp)) != -1) {
            if (strstr(line, "#define D_")){
                char* pch = strtok (line," ");
                char* word = strtok (NULL," ")+2;
                char* num = strtok (NULL," ");
                int n = atoi(num);
                max = n;
                num[strlen(num)-2] = '\0';
//                printf ("   - <%s %d>\n",word, n);
                struct item *aux;
                    aux = malloc(sizeof(struct item));
                    aux->code = n;
                    aux->instance = word;
                ht_set(table, word, aux);
            }
        }
        max++;
        struct item *aux;
        aux = malloc(sizeof(struct item));
        aux->code = max;
        aux->instance = " ";
        ht_set(table, " ", aux);

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