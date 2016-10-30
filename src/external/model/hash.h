#ifndef P1_COMP_HASH_H
#define P1_COMP_HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "list.h"

//#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

struct item{
	char* instance;
	int code;
};

struct entry_s {
	char *key;
	struct item *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
    ol_node *keys;
	struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;


// Create a new hashtable.
hashtable_t *ht_create( int size );
// Hash a string for a particular hash table.
int ht_hash( hashtable_t *hashtable, char *key );
// Create a key-value pair.
entry_t *ht_newpair( char *key, struct item *value );
// Insert a key-value pair into a hash table.
void ht_set( hashtable_t *hashtable, char *key, struct item *value );
// Retrieve a key-value pair from a hash table.
struct item *ht_get( hashtable_t *hashtable, char *key );

void ht_print(hashtable_t *hashtable);
void ht_print_identifiers(hashtable_t *hashtable);
void ht_free(hashtable_t *hashtable);

#endif //P1_COMP_HASH_H
