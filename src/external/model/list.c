#include <memory.h>
#include "list.h"

ol_node* ol_insert(ol_node* head, char *num) {
    ol_node *temp, *prev, *next;
    temp = (ol_node*)malloc(sizeof(ol_node));
    temp->data = strdup(num);
    temp->ptr = NULL;
    if(!head){
        head=temp;
    } else{
        prev = NULL;
        next = head;
        while(next && strcmp(next->data, num) <= 0){
            prev = next;
            next = next->ptr;
        }
        if(!next){
            prev->ptr = temp;
        } else{
            if(prev) {
                temp->ptr = prev->ptr;
                prev-> ptr = temp;
            } else {
                temp->ptr = head;
                head = temp;
            }
        }
    }
    return head;
}

void ol_free_list(ol_node *head) {
    ol_node *prev = head;
    ol_node *cur = head;
    while(cur) {
        prev = cur;
        cur = prev->ptr;
        free(prev);
    }
}