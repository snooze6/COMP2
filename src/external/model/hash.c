#include "hash.h"

// Create new hash table
hashtable_t *ht_create( int size ) {

    hashtable_t *hashtable = NULL;
    int i;

    if( size < 1 ) return NULL;

    // Allocate the table itself
    if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
        return NULL;
    }

    // Allocate pointers to the head nodes.
    if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
        return NULL;
    }

    // Initilizing nodes
    for( i = 0; i < size; i++ ) {
        hashtable->table[i] = NULL;
    }

    hashtable->size = size;

    return hashtable;
}

// Hash a string for a particular hashtable length
int ht_hash( hashtable_t *hashtable, char *key ) {

    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (int) (hash % hashtable->size);
}

// Creates new value-pair
entry_t *ht_newpair( char *key, struct item *value ) {
    entry_t *newpair;

    if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
        return NULL;
    }

    if( ( newpair->key = strdup( key ) ) == NULL ) {
        return NULL;
    }

    newpair->value = malloc( sizeof( struct item ) );
    newpair->value->code = value->code;
    newpair->value->instance = strdup( value->instance );

    if( newpair->value->instance == NULL ) {
        return NULL;
    }

    newpair->next = NULL;

    return newpair;
}

// Insert a key-value pair into a hash table.
void ht_set( hashtable_t *hashtable, char *key, struct item *value ) {
    int bin = 0;
    entry_t *newpair = NULL;
    entry_t *next = NULL;
    entry_t *last = NULL;

    bin = ht_hash( hashtable, key );

    next = hashtable->table[ bin ];

    while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
        last = next;
        next = next->next;
    }

    // There's already a pair.  Let's replace that string.
    if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {
//        printf("[DEBUG] - Replacing: %20s - %d\n", value->instance, value->code);

        free( next->value );

        next->value = malloc( sizeof( struct item ) );
        next->value->instance = strdup(value->instance);
        next->value->code = value->code;

        // Nope, could't find it.  Time to grow a pair.
    } else {
        newpair = ht_newpair( key, value );

        // We're at the start of the linked list in this bin.
        if( next == hashtable->table[ bin ] ) {
            newpair->next = next;
            hashtable->table[ bin ] = newpair;
//            if (strstr(value->instance, "\n")) {
//                printf("[DEBUG] - Inserting:  %20s - %d - %d\n", "\\n", value->code, bin);
//            } else if (strstr(value->instance, "\r")){
//                printf("[DEBUG] - Inserting:  %20s - %d - %d\n", "\\r", value->code, bin);
//            } else {
//                printf("[DEBUG] - Inserting:  %20s - %d - %d\n", value->instance, value->code, bin);
//            }

            // We're at the end of the linked list in this bin.
        } else if ( next == NULL ) {
            last->next = newpair;
//            printf("[DEBUG] - Adding end: %20s - %d - %d\n", value->instance, value->code, bin);

            // We're in the middle of the list.
        } else  {
            newpair->next = next;
            last->next = newpair;
        }
    }
}

// Retrieve a key-value pair from a hash table.
struct item *ht_get( hashtable_t *hashtable, char *key ) {

    int bin = 0;
    entry_t *pair;

    bin = ht_hash( hashtable, key );

//    printf("[DEBUG] - Getting:    %20s - %d\n", key, bin);

    // Step through the bin, looking for our value.
    pair = hashtable->table[ bin ];
    while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
        pair = pair->next;
    }

    // Did we actually find anything?
    if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
        return NULL;
    } else {
        return pair->value;
    }

}