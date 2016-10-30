#ifndef P1_COMP_LIST_H
#define P1_COMP_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ol_node{
    char *data;
    struct ol_node *ptr;
} ol_node;

ol_node* ol_insert(ol_node* head, char *num);
void ol_free_list(ol_node *head);

#endif //P1_COMP_LIST_H
